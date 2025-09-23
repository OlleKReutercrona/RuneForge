#include "stdafx.h"
#include "InputHandler.h"

#define DEBUG_TEST_INPUT

namespace RF {
	namespace input {

#ifdef DEBUG_TEST_INPUT
		bool on_player_jump() {
			return true;
		}
#endif

		InputHandler::InputHandler(Input &input) : mInput(input) {}

		void InputHandler::Initialize() {

#ifdef DEBUG_TEST_INPUT
			mActiveLayer = InputLayer::Gameplay;

			// This will be added through parsing the Keybind Config later.
			std::vector<InputKey> keys;
			keys.emplace_back(KeyboardKey::Space);
			keys.emplace_back(MouseKey::Left);
			AddKeybind(keys, InputEvent::Player_Jump, InputLayer::Gameplay);

			// Anything can register a callback function to a event.
			RegisterCallbackToEvent(InputEvent::Player_Jump, on_player_jump);
#endif 
		}

		// --- Events --- //

		CallbackID InputHandler::RegisterCallbackToEvent(InputEvent event, std::function<bool()> callback) {


			static CallbackID uniqueCallbackID = 0;

			if (!callback || event == InputEvent::Count) {
				return INVALID_CALLBACK_ID;
			}

			// Done this way as 0 is reserved for (INVALID_CALLBACK_ID)
			CallbackID newId = ++uniqueCallbackID;

			// Add callback for when this event is triggered.
			mEventCallbacks[event].emplace_back(EventCallback(newId, callback));

			// Store where this callback is located (to speed up unregistration).
			mCallbackIdToEvent[newId] = event;

			return newId;
		}
		bool InputHandler::UnregisterCallback(CallbackID callbackId) {
			auto it = mCallbackIdToEvent.find(callbackId);
			if (it == mCallbackIdToEvent.end()) { return false; } // no callback associated with the Id.

			InputEvent event = mCallbackIdToEvent.at(callbackId);

			auto callbackIt = mEventCallbacks.find(event);
			if (callbackIt == mEventCallbacks.end()) { return false; } // found no entry for callbacks on this event.

			std::vector<EventCallback> &callbacks = callbackIt->second;

			// Find the callback with 'callbackId' and erase it
			for (int i = 0; i < callbacks.size(); i++) {
				EventCallback &cb = callbacks[i];

				if (cb.uniqueId == callbackId) {
					callbacks.erase(callbacks.begin() + i); // OK to erase as long as we break.
					break;
				}
			}

			// Remove the lookup entry.
			mCallbackIdToEvent.erase(it);

			return true;
		}

		// --- Keybinds --- //

		void InputHandler::AddKeybind(const std::vector<InputKey> &keyCombination, InputEvent eventId, InputLayer layer) {
			if (keyCombination.empty()) return;

			KeybindHash hash = HashKeybind(keyCombination);

			// Store the keybind if it’s new
			auto it = std::find_if(mKeyBinds.begin(), mKeyBinds.end(), [&](const Keybind &kb) { return kb.hash == hash; });
			bool newKeybind = it == mKeyBinds.end();

			if (newKeybind) {

				mKeyBinds.emplace_back(Keybind(hash, keyCombination));

				mKeybindHashToKeybindIndex[hash] = (int)(mKeyBinds.size() - 1); // Map the 'hash' to the actual Keybind index.
				mActionToKeybindHash[(int)eventId] = hash; // Map the Event on 'layer' to 'hash'
				mKeyhashToLayerEvent[hash][(int)layer] = eventId;				// Map the 'hash' on 'layer' to 'event'

			} else {

				// TODO -> Ensure we do not overrite anything here!
				mActionToKeybindHash[(int)eventId] = hash; // Map the Event on 'layer' to 'hash'

				// TODO -> Ensure we do not overrite anything here!
				mKeyhashToLayerEvent[hash][(int)layer] = eventId;			// Map the 'hash' on 'layer' to 'event'
			}
		}
		void InputHandler::RemoveKeybind(KeybindHash hash) {

			// Removes all the events associated with this keybind.
			mKeyhashToLayerEvent.erase(hash);

			// Removes the Keybind.
			auto it = mKeybindHashToKeybindIndex.find(hash);
			if (it != mKeybindHashToKeybindIndex.end()) {
				int index = mKeybindHashToKeybindIndex.at(hash);
				mKeyBinds.erase(mKeyBinds.begin() + index);
			}

			// Removes the hash for index lookup.
			mKeybindHashToKeybindIndex.erase(hash);
		}

		// --- Updates --- //

		void InputHandler::Update() {

			if (mActiveLayer == InputLayer::Count) {
				return; // Cannot process callbacks without valid layer.
			}

			// Go through all keybinds.
			for (Keybind &bind : mKeyBinds) {

				bool pressed = IsKeybindPressed(bind.keys);

				// Update binding state.
				UpdateKeybindState(bind, pressed);

				// Skip is not pressed (for now, might want to support OnRelease etc later).
				if (!pressed) { continue; }

				auto it = mKeyhashToLayerEvent.find(bind.hash);
				if (it == mKeyhashToLayerEvent.end()) { continue; }

				const InputEvent boundEvent = it->second[(int)mActiveLayer];
				FireEvent(boundEvent);
			}
		}
		void InputHandler::UpdateKeybindState(Keybind &bind, bool pressed) {

			switch (bind.state) {
				case KeybindState::Idle:
				{
					if (pressed) {
						bind.state = KeybindState::Pressed;
					}
				} break;
				case KeybindState::Pressed:
				{
					bind.state = pressed ? KeybindState::Down : KeybindState::Released;
				} break;
				case KeybindState::Down:
				{
					if (!pressed) {
						bind.state = KeybindState::Released;
					}
				} break;
				case KeybindState::Released:
				{
					bind.state = pressed ? KeybindState::Pressed : KeybindState::Idle;
				} break;
			}
		}

		// --- Polling --- //

		bool InputHandler::IsActionPressed(InputEvent event) const {

			if (mActiveLayer == InputLayer::Count) return false; // Cannot poll if not on active layer.
			const KeybindHash &hash = mActionToKeybindHash[(int)event];

			// Check if there's a keybind for the Action
			if (mKeybindHashToKeybindIndex.find(hash) == mKeybindHashToKeybindIndex.end()) { return false; }

			int keybindIndex = mKeybindHashToKeybindIndex.at(hash);
			const Keybind &bind = mKeyBinds[keybindIndex];

			return bind.state == KeybindState::Pressed;
		}
		bool InputHandler::IsActionReleased(InputEvent id) const {
			const KeybindHash &hash = mActionToKeybindHash[(int)id];

			// Check if there's a keybind for the Action
			if (mKeybindHashToKeybindIndex.find(hash) == mKeybindHashToKeybindIndex.end()) { return false; }

			int keybindIndex = mKeybindHashToKeybindIndex.at(hash);
			const Keybind &bind = mKeyBinds[keybindIndex];

			return bind.state == KeybindState::Released;
		}
		bool InputHandler::IsActionDown(InputEvent id) const {
			const KeybindHash &hash = mActionToKeybindHash[(int)id];

			// Check if there's a keybind for the Action
			if (mKeybindHashToKeybindIndex.find(hash) == mKeybindHashToKeybindIndex.end()) { return false; }

			int keybindIndex = mKeybindHashToKeybindIndex.at(hash);
			const Keybind &bind = mKeyBinds[keybindIndex];

			return bind.state == KeybindState::Down;
		}

		// --- Helpers --- //

		bool InputHandler::IsLayerActive(InputLayer layer) {
			return mActiveLayer == layer;
		}
		bool InputHandler::FireEvent(InputEvent event) {

			if (event == InputEvent::Count) { return false; }
			if (mEventCallbacks.find(event) == mEventCallbacks.end()) { return false; }

			for (EventCallback &cb : mEventCallbacks[event]) {
				if (!cb.callback) { continue; } // Failsafe
				cb.callback();
			}

			return true;
		}

		// --- Private helper functions --- //

		bool InputHandler::IsInputKeyPressed(const InputKey &key) const {
			switch (key.device) {
				case InputDevice::Keyboard: return mInput.IsKeyPressed(static_cast<KeyCode>(key.code));
				case InputDevice::Mouse:    return mInput.IsMouseButtonPressed(key.code);
				case InputDevice::Gamepad:  /* TODO: gamepad */ return false;
				default: return false;
			}
		}
		bool InputHandler::IsInputKeyDown(const InputKey &key) const {
			switch (key.device) {
				case InputDevice::Keyboard: return mInput.IsKeyDown(static_cast<KeyCode>(key.code));
				case InputDevice::Mouse:    return mInput.IsMouseButtonDown(key.code);
				case InputDevice::Gamepad:  /* TODO: gamepad */ return false;
				default: return false;
			}
		}
		bool InputHandler::IsInputKeyReleased(const InputKey &key) const {
			switch (key.device) {
				case InputDevice::Keyboard: return mInput.IsKeyReleased(static_cast<KeyCode>(key.code));
				case InputDevice::Mouse:    return mInput.IsMouseButtonReleased(key.code);
				case InputDevice::Gamepad:  /* TODO: gamepad */ return false;
				default: return false;
			}
		}

		bool InputHandler::IsKeybindPressed(const std::vector<InputKey> &keys) const {
			if (keys.empty()) return false;

			for (size_t i = 0; i + 1 < keys.size(); ++i) {
				if (!IsInputKeyDown(keys[i])) return false;
			}
			return IsInputKeyPressed(keys.back());
		}
		bool InputHandler::IsKeybindDown(const std::vector<InputKey> &keys) const {
			for (const auto &b : keys) {
				if (!IsInputKeyDown(b)) return false;
			}
			return true;
		}
		bool InputHandler::IsKeybindReleased(const std::vector<InputKey> &keys) const {
			if (keys.empty()) return false;
			return IsInputKeyReleased(keys.back());
		}

		KeybindHash InputHandler::HashKeybind(const std::vector<InputKey> &combo) {
			std::hash<int> h;
			KeybindHash result = INVALID_KEYBIND_HASH;
			for (const auto &key : combo) {
				// Mix device + code into the hash
				result ^= (h((int)key.device) ^ (h(key.code) << 1)) + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
			}
			return result;
		}
	}
}