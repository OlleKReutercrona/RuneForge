#pragma once
#include "Input/CommonInput.h"
#include "Input.h"

namespace RF {
	namespace input {

		enum class KeybindState {
			Idle,
			Pressed,
			Down,
			Released,
		};

		struct InputKey {
			InputDevice device = InputDevice::NotSet;
			uint32_t code;

			InputKey(KeyboardKey k) : device(InputDevice::Keyboard), code(static_cast<uint32_t>(k)) {}
			InputKey(MouseKey m) : device(InputDevice::Mouse), code(static_cast<uint32_t>(m)) {}
			InputKey(GamepadKey g) : device(InputDevice::Gamepad), code(static_cast<uint32_t>(g)) {}
		};

		struct Keybind {
			KeybindHash hash = INVALID_KEYBIND_HASH;
			std::vector<InputKey> keys = {};
			KeybindState state = KeybindState::Idle;

			Keybind() = default;
			Keybind(const KeybindHash keybindHash, const std::vector<InputKey> &keys) : keys(keys), hash(keybindHash) {}
		};

		class InputHandler {
		public:

			InputHandler(Input &input);

			// --- Events --- //

			int RegisterCallbackToEvent(InputEvent id, std::function<bool()> callback);
			bool UnregisterCallback(CallbackID callbackId);

			// --- Keybinds --- //

			void AddKeybind(const std::vector<InputKey> &keyCombination, InputEvent id, InputLayer layer);
			void RemoveKeybind(KeybindHash hash);

			// --- Updates --- //

			void Update();
			void UpdateKeybindState(Keybind &bind, bool pressed);

			// --- Polling --- //

			bool IsActionPressed(InputEvent id) const;
			bool IsActionReleased(InputEvent id) const;
			bool IsActionDown(InputEvent id) const;

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
			std::unordered_map<char, std::vector<int>> keyToBind;

			KeybindHash HashKeybind(const std::vector<InputKey> &combo);

			bool IsInputKeyReleased(const InputKey &key) const;
			bool IsInputKeyDown(const InputKey &key) const;
			bool IsInputKeyPressed(const InputKey &key) const;

			bool IsKeybindPressed(const std::vector<InputKey> &keys) const;
			bool IsKeybindDown(const std::vector<InputKey> &keys) const;
			bool IsKeybindReleased(const std::vector<InputKey> &keys) const;
		};
	}
}