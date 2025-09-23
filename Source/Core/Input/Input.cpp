#include "stdafx.h"
#include "Input/Input.h"

namespace RF {
	namespace input {

		Input::Input() {
			keyCurrent.reset();
			keyPressed.reset();
			keyReleased.reset();
			mouseCurrent.reset();
			mousePressed.reset();
			mouseReleased.reset();
			mouseDeltaX = mouseDeltaY = wheelDelta = 0;
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
			mousePressed.reset();
			mouseReleased.reset();
			mouseDeltaX = 0;
			mouseDeltaY = 0;
			wheelDelta = 0;
		}

		bool Input::IsKeyDown(KeyCode vkey) const {
			if (vkey >= 256) return false;
			return keyCurrent.test(vkey);
		}
		bool Input::IsKeyPressed(KeyCode vkey) const {
			if (vkey >= 256) return false;
			return keyPressed.test(vkey);
		}
		bool Input::IsKeyReleased(KeyCode vkey) const {
			if (vkey >= 256) return false;
			return keyReleased.test(vkey);
		}

		bool Input::IsMouseButtonDown(int buttonIdx) const {
			if (buttonIdx < 0 || buttonIdx >= 8) return false;
			return mouseCurrent.test(buttonIdx);
		}
		bool Input::IsMouseButtonPressed(int buttonIdx) const {
			if (buttonIdx < 0 || buttonIdx >= 8) return false;
			return mousePressed.test(buttonIdx);
		}
		bool Input::IsMouseButtonReleased(int buttonIdx) const {
			if (buttonIdx < 0 || buttonIdx >= 8) return false;
			return mouseReleased.test(buttonIdx);
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

			// Buttons
			// usButtonFlags can be combination of RI_MOUSE_* values
			if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
				if (!mouseCurrent.test(0)) {
					mouseCurrent.set(0);
					mousePressed.set(0);
					mouseReleased.reset(0);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {
				if (mouseCurrent.test(0)) {
					mouseCurrent.reset(0);
					mouseReleased.set(0);
					mousePressed.reset(0);
				}
			}

			if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
				if (!mouseCurrent.test(1)) {
					mouseCurrent.set(1);
					mousePressed.set(1);
					mouseReleased.reset(1);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) {
				if (mouseCurrent.test(1)) {
					mouseCurrent.reset(1);
					mouseReleased.set(1);
					mousePressed.reset(1);
				}
			}

			if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
				if (!mouseCurrent.test(2)) {
					mouseCurrent.set(2);
					mousePressed.set(2);
					mouseReleased.reset(2);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) {
				if (mouseCurrent.test(2)) {
					mouseCurrent.reset(2);
					mouseReleased.set(2);
					mousePressed.reset(2);
				}
			}

			// X buttons
			if (m.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) {
				if (!mouseCurrent.test(3)) {
					mouseCurrent.set(3);
					mousePressed.set(3);
					mouseReleased.reset(3);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_BUTTON_4_UP) {
				if (mouseCurrent.test(3)) {
					mouseCurrent.reset(3);
					mouseReleased.set(3);
					mousePressed.reset(3);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) {
				if (!mouseCurrent.test(4)) {
					mouseCurrent.set(4);
					mousePressed.set(4);
					mouseReleased.reset(4);
				}
			}
			if (m.usButtonFlags & RI_MOUSE_BUTTON_5_UP) {
				if (mouseCurrent.test(4)) {
					mouseCurrent.reset(4);
					mouseReleased.set(4);
					mousePressed.reset(4);
				}
			}

			// Wheel
			if (m.usButtonFlags & RI_MOUSE_WHEEL) {
				// wheel data in usButtonData (signed short)
				SHORT wheel = static_cast<SHORT>(m.usButtonData);
				wheelDelta += static_cast<int>(wheel); // in WHEEL_DELTA units
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