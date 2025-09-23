#pragma once
#include "Input/CommonInput.h"
#include "Input.h"

namespace RF {
	namespace input {

		using KeyMask = std::bitset<MAX_KEYS>;

		// A Keybind needs to store 2 bitsets due to key combo orders, i.e: Space + MouseKey is not the same as Mousekey + Space.
		// Reason is the first key needs to be DOWN and the last key PRESSED this frame / tick.
		struct Keybind {
			KeybindHash hash = INVALID_KEYBIND_HASH;
			KeyMask downMask;   // All keys that must be held down (except last key in combo)
			KeyMask pressMask;  // The key that must be newly pressed to trigger

			Keybind() = default;
			Keybind(const KeybindHash keybindHash) : hash(keybindHash) {}
		};

		class InputHandler {
		public:

			InputHandler(Input &input);

			// --- Events --- //

			int RegisterCallbackToEvent(InputEvent id, std::function<bool()> callback);
			bool UnregisterCallback(CallbackID callbackId);

			// --- Keybinds --- //

			void AddKeybind(const std::vector<KeyCode> &keyCombination, InputEvent id, InputLayer layer);
			void RemoveKeybind(KeybindHash hash);

			// --- Input Notify --- //

			void OnKeybindTriggered(KeyCode key);

			// --- Polling --- //

			bool IsActionPressed(InputEvent event) const;
			bool IsActionDown(InputEvent event) const;
			bool IsActionReleased(InputEvent event) const;

			bool IsKeyPressed(KeyCode key) const;
			bool IsKeyDown(KeyCode key) const;
			bool IsKeyReleased(KeyCode key) const;

			// --- Helpers --- //

			bool IsLayerActive(InputLayer layer);
			bool FireEvent(InputEvent id);

			// --- Debug --- //
			void Initialize();


		private:
			Input &mInput;

			InputLayer mActiveLayer = InputLayer::Count;

			// All registered keybinds.
			std::vector<Keybind> mKeyBinds = {};

			// Container to retrieve which keybind hash is bound to the Event (Used for polling)
			std::array<KeybindHash, (int)InputEvent::Count> mActionToKeybindHash = {};

			// Container to retrieve which keybind index is bound to the hash (Used for polling)
			std::unordered_map<KeybindHash, int> mKeybindHashToKeybindIndex = {};

			// Container to retrieve callbacks for a given event (Used to fire events).
			std::unordered_map<InputEvent, std::vector<EventCallback>> mEventCallbacks = {};

			// Each keybind can only have 1 ActionEvent per layer (Used to decide which event to fire).
			std::unordered_map<KeybindHash, std::array<InputEvent, (int)InputLayer::Count>> mKeyhashToLayerEvent = {};

			// Each unique callback ID maps to a specific event (Used for unregistration).
			std::unordered_map<CallbackID, InputEvent> mCallbackIdToEvent = {};

			// TODO, we can store key to Binds on startup
			std::unordered_map<KeyCode, std::vector<int>> mKeyToBind;

			KeybindHash HashKeybind(const std::vector<KeyCode> &keys);
			std::bitset<MAX_KEYS> GenerateNotifyMask(std::vector<Keybind> keybinds);

			bool IsKeybindPressed(const Keybind &keybind) const;
			bool IsKeybindDown(const Keybind &keybind) const;
			bool IsKeybindReleased(const Keybind &keybind) const;
		};
	}
}