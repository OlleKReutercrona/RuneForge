#include "stdafx.h"
#include "Input/Input.h"

namespace RF {
	namespace input {

		Input::Input() {
			keyCurrent.reset();
			keyPressed.reset();
			keyReleased.reset();
			mouseDeltaX = 0;
			mouseDeltaY = 0;
		}

		bool Input::RegisterDevices(HWND hwnd, bool noLegacy) {
			RAWINPUTDEVICE rid[2];

			// Keyboard
			auto &keyboard = rid[0];
			keyboard.usUsagePage = 0x01;
			keyboard.usUsage = 0x06; // keyboard
			keyboard.dwFlags = RIDEV_INPUTSINK | (noLegacy ? RIDEV_NOLEGACY : 0);
			keyboard.hwndTarget = hwnd;

			// Mouse
			auto &mouse = rid[1];
			mouse.usUsagePage = 0x01;
			mouse.usUsage = 0x02; // mouse
			mouse.dwFlags = RIDEV_INPUTSINK | (noLegacy ? RIDEV_NOLEGACY : 0);
			mouse.hwndTarget = hwnd;

			if (!RegisterRawInputDevices(rid, 2, sizeof(rid[0]))) {
				// registration failed; you may want to Log() instead of MessageBox in a real engine
				MessageBox(hwnd, L"Failed to register raw input devices.", L"Input Error", MB_ICONERROR);
				return false;
			}
			return true;
		}

		void Input::Update() {
			// clear per-frame "pressed" / "released" but keep current state
			keyPressed.reset();
			keyReleased.reset();
			mouseDeltaX = 0;
			mouseDeltaY = 0;
			wheelDelta = 0;
		}

		bool Input::IsKeyDown(KeyCode vkey) const {
			return keyCurrent.test((int)vkey);
		}
		bool Input::IsKeyPressed(KeyCode vkey) const {
			return keyPressed.test((int)vkey);
		}
		bool Input::IsKeyReleased(KeyCode vkey) const {
			return keyReleased.test((int)vkey);
		}

		void Input::SetNotifyFunc(std::function<void(KeyCode)> notifyCallback) {
			mNotifyCallback = notifyCallback;
		}

		void Input::SetNotifyMask(std::bitset<MAX_KEYS> &notifyMask) {
			mNotifyMask = notifyMask;
		}

		void Input::InjectKeyboard(USHORT vkey, USHORT flags) {
			// RAWKEYBOARD.Flags: bit 0 = key make/break? Actually see docs:
			// KB: Flags contains RI_KEY_MAKE / RI_KEY_BREAK etc. Simpler: PK lookup:
			// When Flags & RI_KEY_BREAK != 0 => key up
			constexpr USHORT KEY_BREAK_FLAG = RI_KEY_BREAK; // 1 => key up

			bool released = (flags & KEY_BREAK_FLAG) != 0;
			if (vkey < 256) {
				if (released) {
					// if previously down, mark released
					if (keyCurrent.test(vkey)) {
						keyCurrent.reset(vkey);
						keyReleased.set(vkey);
						keyPressed.reset(vkey); // safety
					}
				} else {
					if (!keyCurrent.test(vkey)) {
						keyCurrent.set(vkey);
						keyPressed.set(vkey);
						keyReleased.reset(vkey);
					}
				}

				if (mNotifyMask.test(vkey)) {
					NotifyKeybindPress((KeyCode)vkey);
				}
			}
		}

		void Input::InjectMouse(const RAWMOUSE &m) {
			// Relative movement
			if (m.usFlags == MOUSE_MOVE_RELATIVE) {
				// lLastX/lLastY are LONG but stored in union; treat as signed
				mouseDeltaX += static_cast<int>(m.lLastX);
				mouseDeltaY += static_cast<int>(m.lLastY);
			} else {
				// Absolute or other (ignore for now)
			}

			// Wheel
			if (m.usButtonFlags & RI_MOUSE_WHEEL) {
				// wheel data in usButtonData (signed short)
				SHORT wheel = static_cast<SHORT>(m.usButtonData);
				wheelDelta += static_cast<int>(wheel); // in WHEEL_DELTA units
			}

			// Using a lambda here to minimize boilerplate.
			auto handleMouseKey = [&](KeyCode code, bool pressed) {
				if (pressed) {
					keyCurrent.set((int)code);
					keyPressed.set((int)code);
					keyReleased.reset((int)code);
				} else {
					keyCurrent.reset((int)code);
					keyReleased.set((int)code);
					keyPressed.reset((int)code);
				}

				if (mNotifyMask.test((int)code)) {
					NotifyKeybindPress(code);
				}
			};

			if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) handleMouseKey(KeyCode::MouseLeft, true);
			if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) handleMouseKey(KeyCode::MouseLeft, false);
			if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) handleMouseKey(KeyCode::MouseRight, true);
			if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) handleMouseKey(KeyCode::MouseRight, false);
			if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) handleMouseKey(KeyCode::MouseMiddle, true);
			if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) handleMouseKey(KeyCode::MouseMiddle, false);
			if (m.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) handleMouseKey(KeyCode::MouseX1, true);
			if (m.usButtonFlags & RI_MOUSE_BUTTON_4_UP) handleMouseKey(KeyCode::MouseX1, false);
			if (m.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) handleMouseKey(KeyCode::MouseX2, true);
			if (m.usButtonFlags & RI_MOUSE_BUTTON_5_UP) handleMouseKey(KeyCode::MouseX2, false);
		}

		void Input::NotifyKeybindPress(KeyCode key) {

			if (mNotifyCallback) { 
				mNotifyCallback(key); 
			}
		}

		void Input::ProcessRawInput(LPARAM lParam) {
			// two-call pattern but try stack buffer first
			UINT size = 0;
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) != 0) {
				// failure reading size
				return;
			}

			BYTE *bufPtr = nullptr;
			std::vector<BYTE> heapBuf; // used only if needed

			if (size <= STACK_BUFFER_SIZE) {
				bufPtr = stackBuffer.data();
			} else {
				try {
					heapBuf.resize(size);
					bufPtr = heapBuf.data();
				} catch (...) {
					return; // allocation failed
				}
			}

			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, bufPtr, &size, sizeof(RAWINPUTHEADER)) != size) {
				return; // failed to read
			}

			RAWINPUT *raw = reinterpret_cast<RAWINPUT *>(bufPtr);
			if (!raw) return;

			if (raw->header.dwType == RIM_TYPEKEYBOARD) {
				const RAWKEYBOARD &kb = raw->data.keyboard;
				// kb.VKey is the virtual key code; kb.Flags contains make/break info
				InjectKeyboard(kb.VKey, kb.Flags);
			} else if (raw->header.dwType == RIM_TYPEMOUSE) {
				const RAWMOUSE &m = raw->data.mouse;
				InjectMouse(m);
			}
		}
	}
}