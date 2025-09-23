#pragma once
#include "Input/KeyCodes.h"
#include "Input/InputEvents.h"

namespace RF {
	namespace input {

		constexpr int MAX_KEYS = 256;

		//using KeyCode = uint16_t; 
		using CallbackID = int;     // Unique ID for a callback function
		using KeybindHash = size_t; // Unique ID for a key combination on device X
		using CallbackFunction = std::function<bool>;

		constexpr CallbackID INVALID_CALLBACK_ID = 0;
		constexpr KeybindHash INVALID_KEYBIND_HASH = ULONG_MAX;

		// Input layers
		enum class InputLayer : uint8_t {
			Gameplay,
			UI,
			Editor,
			Count
		};

		// Device types for input
		enum class InputDevice : uint8_t {
			KeyboardAndMouse,
			Gamepad,
			NotSet
		};

		struct EventCallback {
			EventCallback(int cbid, std::function<bool()> cb) :
				uniqueId(cbid),
				callback(cb) {
			}

			CallbackID uniqueId = INVALID_CALLBACK_ID;
			std::function<bool()> callback = nullptr;
		};

		// --- Enum Conversions --- //

		inline KeyCode StringToKeyCode(const std::string &str) {
			static const std::unordered_map<std::string, KeyCode> map = {
				// Mouse
				{"MouseLeft", KeyCode::MouseLeft},
				{"MouseRight", KeyCode::MouseRight},
				{"MouseMiddle", KeyCode::MouseMiddle},
				{"MouseX1", KeyCode::MouseX1},
				{"MouseX2", KeyCode::MouseX2},

				// Letters
				{"A", KeyCode::A}, {"B", KeyCode::B}, {"C", KeyCode::C}, {"D", KeyCode::D},
				{"E", KeyCode::E}, {"F", KeyCode::F}, {"G", KeyCode::G}, {"H", KeyCode::H},
				{"I", KeyCode::I}, {"J", KeyCode::J}, {"K", KeyCode::K}, {"L", KeyCode::L},
				{"M", KeyCode::M}, {"N", KeyCode::N}, {"O", KeyCode::O}, {"P", KeyCode::P},
				{"Q", KeyCode::Q}, {"R", KeyCode::R}, {"S", KeyCode::S}, {"T", KeyCode::T},
				{"U", KeyCode::U}, {"V", KeyCode::V}, {"W", KeyCode::W}, {"X", KeyCode::X},
				{"Y", KeyCode::Y}, {"Z", KeyCode::Z},

				// Numbers
				{"0", KeyCode::Num0}, {"1", KeyCode::Num1}, {"2", KeyCode::Num2},
				{"3", KeyCode::Num3}, {"4", KeyCode::Num4}, {"5", KeyCode::Num5},
				{"6", KeyCode::Num6}, {"7", KeyCode::Num7}, {"8", KeyCode::Num8},
				{"9", KeyCode::Num9},

				// Function keys
				{"F1", KeyCode::F1}, {"F2", KeyCode::F2}, {"F3", KeyCode::F3}, {"F4", KeyCode::F4},
				{"F5", KeyCode::F5}, {"F6", KeyCode::F6}, {"F7", KeyCode::F7}, {"F8", KeyCode::F8},
				{"F9", KeyCode::F9}, {"F10", KeyCode::F10}, {"F11", KeyCode::F11}, {"F12", KeyCode::F12},

				// Modifiers
				{"LeftCtrl", KeyCode::LeftCtrl}, {"RightCtrl", KeyCode::RightCtrl},
				{"LeftShift", KeyCode::LeftShift}, {"RightShift", KeyCode::RightShift},
				{"LeftAlt", KeyCode::LeftAlt}, {"RightAlt", KeyCode::RightAlt},

				// Special keys
				{"Space", KeyCode::Space}, {"Enter", KeyCode::Enter}, {"Escape", KeyCode::Escape},
				{"Tab", KeyCode::Tab}, {"Backspace", KeyCode::Backspace},
				{"UpArrow", KeyCode::UpArrow}, {"DownArrow", KeyCode::DownArrow},
				{"LeftArrow", KeyCode::LeftArrow}, {"RightArrow", KeyCode::RightArrow},
				{"CapsLock", KeyCode::CapsLock}, {"NumLock", KeyCode::NumLock},
				{"ScrollLock", KeyCode::ScrollLock}, {"PrintScreen", KeyCode::PrintScreen},
				{"Insert", KeyCode::Insert}, {"Delete", KeyCode::Delete},
				{"Home", KeyCode::Home}, {"End", KeyCode::End},
				{"PageUp", KeyCode::PageUp}, {"PageDown", KeyCode::PageDown},
				{"LeftWin", KeyCode::LeftWin}, {"RightWin", KeyCode::RightWin},
				{"Apps", KeyCode::Apps}, {"Sleep", KeyCode::Sleep},

				// Numpad
				{"Numpad0", KeyCode::Numpad0}, {"Numpad1", KeyCode::Numpad1}, {"Numpad2", KeyCode::Numpad2},
				{"Numpad3", KeyCode::Numpad3}, {"Numpad4", KeyCode::Numpad4}, {"Numpad5", KeyCode::Numpad5},
				{"Numpad6", KeyCode::Numpad6}, {"Numpad7", KeyCode::Numpad7}, {"Numpad8", KeyCode::Numpad8},
				{"Numpad9", KeyCode::Numpad9}, {"NumpadMultiply", KeyCode::NumpadMultiply},
				{"NumpadAdd", KeyCode::NumpadAdd}, {"NumpadSeparator", KeyCode::NumpadSeparator},
				{"NumpadSubtract", KeyCode::NumpadSubtract}, {"NumpadDecimal", KeyCode::NumpadDecimal},
				{"NumpadDivide", KeyCode::NumpadDivide}
			};

			auto it = map.find(str);
			return it != map.end() ? it->second : KeyCode::Count;
		}

		inline const char *KeyToString(KeyCode key) {
			switch (key) {
				// Mouse
				case KeyCode::MouseLeft: return "MouseLeft";
				case KeyCode::MouseRight: return "MouseRight";
				case KeyCode::MouseMiddle: return "MouseMiddle";
				case KeyCode::MouseX1: return "MouseX1";
				case KeyCode::MouseX2: return "MouseX2";

					// Letters
				case KeyCode::A: return "A"; case KeyCode::B: return "B"; case KeyCode::C: return "C";
				case KeyCode::D: return "D"; case KeyCode::E: return "E"; case KeyCode::F: return "F";
				case KeyCode::G: return "G"; case KeyCode::H: return "H"; case KeyCode::I: return "I";
				case KeyCode::J: return "J"; case KeyCode::K: return "K"; case KeyCode::L: return "L";
				case KeyCode::M: return "M"; case KeyCode::N: return "N"; case KeyCode::O: return "O";
				case KeyCode::P: return "P"; case KeyCode::Q: return "Q"; case KeyCode::R: return "R";
				case KeyCode::S: return "S"; case KeyCode::T: return "T"; case KeyCode::U: return "U";
				case KeyCode::V: return "V"; case KeyCode::W: return "W"; case KeyCode::X: return "X";
				case KeyCode::Y: return "Y"; case KeyCode::Z: return "Z";

					// Numbers
				case KeyCode::Num0: return "0"; case KeyCode::Num1: return "1"; case KeyCode::Num2: return "2";
				case KeyCode::Num3: return "3"; case KeyCode::Num4: return "4"; case KeyCode::Num5: return "5";
				case KeyCode::Num6: return "6"; case KeyCode::Num7: return "7"; case KeyCode::Num8: return "8";
				case KeyCode::Num9: return "9";

					// Function keys
				case KeyCode::F1: return "F1"; case KeyCode::F2: return "F2"; case KeyCode::F3: return "F3";
				case KeyCode::F4: return "F4"; case KeyCode::F5: return "F5"; case KeyCode::F6: return "F6";
				case KeyCode::F7: return "F7"; case KeyCode::F8: return "F8"; case KeyCode::F9: return "F9";
				case KeyCode::F10: return "F10"; case KeyCode::F11: return "F11"; case KeyCode::F12: return "F12";

					// Modifiers
				case KeyCode::LeftCtrl: return "LeftCtrl"; case KeyCode::RightCtrl: return "RightCtrl";
				case KeyCode::LeftShift: return "LeftShift"; case KeyCode::RightShift: return "RightShift";
				case KeyCode::LeftAlt: return "LeftAlt"; case KeyCode::RightAlt: return "RightAlt";

					// Special keys
				case KeyCode::Space: return "Space"; case KeyCode::Enter: return "Enter";
				case KeyCode::Escape: return "Escape"; case KeyCode::Tab: return "Tab";
				case KeyCode::Backspace: return "Backspace"; case KeyCode::UpArrow: return "UpArrow";
				case KeyCode::DownArrow: return "DownArrow"; case KeyCode::LeftArrow: return "LeftArrow";
				case KeyCode::RightArrow: return "RightArrow"; case KeyCode::CapsLock: return "CapsLock";
				case KeyCode::NumLock: return "NumLock"; case KeyCode::ScrollLock: return "ScrollLock";
				case KeyCode::PrintScreen: return "PrintScreen"; case KeyCode::Insert: return "Insert";
				case KeyCode::Delete: return "Delete"; case KeyCode::Home: return "Home";
				case KeyCode::End: return "End"; case KeyCode::PageUp: return "PageUp";
				case KeyCode::PageDown: return "PageDown"; case KeyCode::LeftWin: return "LeftWin";
				case KeyCode::RightWin: return "RightWin"; case KeyCode::Apps: return "Apps";
				case KeyCode::Sleep: return "Sleep";

					// Numpad
				case KeyCode::Numpad0: return "Numpad0"; case KeyCode::Numpad1: return "Numpad1";
				case KeyCode::Numpad2: return "Numpad2"; case KeyCode::Numpad3: return "Numpad3";
				case KeyCode::Numpad4: return "Numpad4"; case KeyCode::Numpad5: return "Numpad5";
				case KeyCode::Numpad6: return "Numpad6"; case KeyCode::Numpad7: return "Numpad7";
				case KeyCode::Numpad8: return "Numpad8"; case KeyCode::Numpad9: return "Numpad9";
				case KeyCode::NumpadMultiply: return "NumpadMultiply"; case KeyCode::NumpadAdd: return "NumpadAdd";
				case KeyCode::NumpadSeparator: return "NumpadSeparator"; case KeyCode::NumpadSubtract: return "NumpadSubtract";
				case KeyCode::NumpadDecimal: return "NumpadDecimal"; case KeyCode::NumpadDivide: return "NumpadDivide";

				default: return INVALID_KEY_NAME;
			}
		}


		inline GamepadKey StringToGamepadKey(const std::string &str) {
			static const std::unordered_map<std::string, GamepadKey> map = {
				{"A", GamepadKey::A},
				{"B", GamepadKey::B},
				{"X", GamepadKey::X},
				{"Y", GamepadKey::Y},
				{"LB", GamepadKey::LB},
				{"RB", GamepadKey::RB}
			};
			auto it = map.find(str);
			return it != map.end() ? it->second : GamepadKey::Unknown;
		}
		inline const char *KeyToString(GamepadKey key) {

			switch (key) {

				case GamepadKey::A: return "A";
				case GamepadKey::B: return "B";
				case GamepadKey::X: return "X";
				case GamepadKey::Y: return "Y";
				case GamepadKey::LB: return "LB";
				case GamepadKey::RB: return "RB";


				default: return INVALID_KEY_NAME;
			}
		}

	}
}