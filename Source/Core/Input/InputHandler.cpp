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
			std::vector<KeyCode> keys;
			//keys.emplace_back(KeyCode::Space);
			keys.emplace_back(KeyCode::Space);
			keys.emplace_back(KeyCode::MouseLeft);
			AddKeybind(keys, InputEvent::Player_Jump, InputLayer::Gameplay);

			// Anything can register a callback function to a event.
			RegisterCallbackToEvent(InputEvent::Player_Jump, on_player_jump);
#endif 

			// OBS: This has to be done after we parsed keybinds
			// AND: When we rebind keybinds.

			std::bitset<MAX_KEYS> notifyMask = GenerateNotifyMask(mKeyBinds);

			mInput.SetNotifyMask(notifyMask);
			mInput.SetNotifyFunc([this](KeyCode key) {
				this->OnKeybindTriggered(key);
			});
		}

		// --- Keybinds --- //

		void InputHandler::AddKeybind(const std::vector<KeyCode> &keyCombination, InputEvent eventId, InputLayer layer) {
			if (keyCombination.empty()) return;

			// Generate hash for this combination
			KeybindHash hash = HashKeybind(keyCombination);

			// Check if keybind already exists
			auto it = std::find_if(mKeyBinds.begin(), mKeyBinds.end(), [&](const Keybind &kb) { return kb.hash == hash; });
			bool notFound = it == mKeyBinds.end();

			if (notFound) {

				// Convert keyCombination into a KeyMask
				Keybind &newKeybind = mKeyBinds.emplace_back(hash);
				int keybindIndex = static_cast<int>(mKeyBinds.size() - 1);

				// All keys except the last are "held down"
				for (size_t i = 0; i + 1 < keyCombination.size(); ++i) {
					newKeybind.downMask.set(static_cast<size_t>(keyCombination[i]));
				}

				// The last key is the "press" key
				newKeybind.pressMask.set(static_cast<size_t>(keyCombination.back()));

				// Map the keybind to each keycode.
				for (const KeyCode &keycode : keyCombination) {
					mKeyToBind[keycode].emplace_back(keybindIndex);
				}

				// Map hash to index
				mKeybindHashToKeybindIndex[hash] = static_cast<int>(mKeyBinds.size() - 1);

				// Map event to hash
				mActionToKeybindHash[(int)eventId] = hash;

				// Map hash + layer to event
				mKeyhashToLayerEvent[hash][static_cast<int>(layer)] = eventId;
			} else {
				// If keybind exists, just update the layer/event mapping
				mActionToKeybindHash[(int)eventId] = hash;
				mKeyhashToLayerEvent[hash][static_cast<int>(layer)] = eventId;
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

		// --- Input Notify --- //

		void InputHandler::OnKeybindTriggered(KeyCode key) {

			if (mKeyToBind.find(key) == mKeyToBind.end()) { return; }

			for (int keybindIndex: mKeyToBind.at(key)) {

				const Keybind &keybind = mKeyBinds[keybindIndex];

				if (!IsKeybindPressed(keybind)) { continue; }

				auto it = mKeyhashToLayerEvent.find(keybind.hash);
				if (it == mKeyhashToLayerEvent.end()) { continue; }

				const InputEvent boundEvent = it->second[(int)mActiveLayer];
				FireEvent(boundEvent);
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

			return IsKeybindPressed(bind);
		}
		bool InputHandler::IsActionDown(InputEvent event) const {
			const KeybindHash &hash = mActionToKeybindHash[(int)id];

			// Check if there's a keybind for the Action
			if (mKeybindHashToKeybindIndex.find(hash) == mKeybindHashToKeybindIndex.end()) { return false; }

			int keybindIndex = mKeybindHashToKeybindIndex.at(hash);
			const Keybind &bind = mKeyBinds[keybindIndex];

			return IsKeybindDown(bind);
		}
		bool InputHandler::IsActionReleased(InputEvent event) const {
			const KeybindHash &hash = mActionToKeybindHash[(int)id];

			// Check if there's a keybind for the Action
			if (mKeybindHashToKeybindIndex.find(hash) == mKeybindHashToKeybindIndex.end()) { return false; }

			int keybindIndex = mKeybindHashToKeybindIndex.at(hash);
			const Keybind &bind = mKeyBinds[keybindIndex];

			return IsKeybindReleased(bind);
		}

		bool InputHandler::IsKeyPressed(KeyCode key) const {
			return mInput.IsKeyPressed(key);
		}
		bool InputHandler::IsKeyDown(KeyCode key) const {
			return mInput.IsKeyDown(key);
		}
		bool InputHandler::IsKeyReleased(KeyCode key) const {
			return mInput.IsKeyReleased(key);
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
				// TODO: Handle return value!
			}

			return true;
		}

		// --- Private helper functions --- //

		bool InputHandler::IsKeybindPressed(const Keybind &keybind) const {
			return ((keybind.downMask & mInput.keyCurrent) == keybind.downMask) &&
				((keybind.pressMask & mInput.keyPressed) == keybind.pressMask);
		}

		bool InputHandler::IsKeybindDown(const Keybind &keybind) const {
			KeyMask combinedMask = keybind.downMask | keybind.pressMask;
			return (combinedMask & mInput.keyCurrent) == combinedMask;
		}

		bool InputHandler::IsKeybindReleased(const Keybind &keybind) const {
			return (keybind.pressMask & mInput.keyReleased) == keybind.pressMask;
		}

		std::bitset<MAX_KEYS> InputHandler::GenerateNotifyMask(std::vector<Keybind> keybinds) {

			std::bitset<MAX_KEYS> result;

			for (const Keybind &bind : keybinds) {
				result |= bind.downMask;
				result |= bind.pressMask;
			}

			return result;
		}

		KeybindHash InputHandler::HashKeybind(const std::vector<KeyCode> &keys) {
			std::hash<int> h;
			KeybindHash result = INVALID_KEYBIND_HASH;

			for (const auto &key : keys) {
				// Mix the KeyCode value into the hash
				result ^= h(static_cast<int>(key)) + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
			}

			return result;
		}

	}
}