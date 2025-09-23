#pragma once
#include "Input/KeyCodes.h"
#include "Input/InputEvents.h"

namespace RF {
	namespace input {

		using KeyCode = uint16_t; 
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
            Keyboard,
            Mouse,
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

        inline KeyboardKey StringToKeyboardKey(const std::string &str) {
            static const std::unordered_map<std::string, KeyboardKey> map = {
                // Letters
                {"A", KeyboardKey::A}, {"B", KeyboardKey::B}, {"C", KeyboardKey::C}, {"D", KeyboardKey::D},
                {"E", KeyboardKey::E}, {"F", KeyboardKey::F}, {"G", KeyboardKey::G}, {"H", KeyboardKey::H},
                {"I", KeyboardKey::I}, {"J", KeyboardKey::J}, {"K", KeyboardKey::K}, {"L", KeyboardKey::L},
                {"M", KeyboardKey::M}, {"N", KeyboardKey::N}, {"O", KeyboardKey::O}, {"P", KeyboardKey::P},
                {"Q", KeyboardKey::Q}, {"R", KeyboardKey::R}, {"S", KeyboardKey::S}, {"T", KeyboardKey::T},
                {"U", KeyboardKey::U}, {"V", KeyboardKey::V}, {"W", KeyboardKey::W}, {"X", KeyboardKey::X},
                {"Y", KeyboardKey::Y}, {"Z", KeyboardKey::Z},

                // Numbers
                {"0", KeyboardKey::Num0}, {"1", KeyboardKey::Num1}, {"2", KeyboardKey::Num2},
                {"3", KeyboardKey::Num3}, {"4", KeyboardKey::Num4}, {"5", KeyboardKey::Num5},
                {"6", KeyboardKey::Num6}, {"7", KeyboardKey::Num7}, {"8", KeyboardKey::Num8},
                {"9", KeyboardKey::Num9},

                // Function keys
                {"F1", KeyboardKey::F1}, {"F2", KeyboardKey::F2}, {"F3", KeyboardKey::F3}, {"F4", KeyboardKey::F4},
                {"F5", KeyboardKey::F5}, {"F6", KeyboardKey::F6}, {"F7", KeyboardKey::F7}, {"F8", KeyboardKey::F8},
                {"F9", KeyboardKey::F9}, {"F10", KeyboardKey::F10}, {"F11", KeyboardKey::F11}, {"F12", KeyboardKey::F12},

                // Modifiers
                {"LeftCtrl", KeyboardKey::LeftCtrl}, {"RightCtrl", KeyboardKey::RightCtrl},
                {"LeftShift", KeyboardKey::LeftShift}, {"RightShift", KeyboardKey::RightShift},
                {"LeftAlt", KeyboardKey::LeftAlt}, {"RightAlt", KeyboardKey::RightAlt},

                // Special keys
                {"Space", KeyboardKey::Space}, {"Enter", KeyboardKey::Enter}, {"Escape", KeyboardKey::Escape},
                {"Tab", KeyboardKey::Tab}, {"Backspace", KeyboardKey::Backspace},
                {"UpArrow", KeyboardKey::UpArrow}, {"DownArrow", KeyboardKey::DownArrow},
                {"LeftArrow", KeyboardKey::LeftArrow}, {"RightArrow", KeyboardKey::RightArrow},
                {"CapsLock", KeyboardKey::CapsLock}, {"NumLock", KeyboardKey::NumLock},
                {"ScrollLock", KeyboardKey::ScrollLock}, {"PrintScreen", KeyboardKey::PrintScreen},
                {"Insert", KeyboardKey::Insert}, {"Delete", KeyboardKey::Delete},
                {"Home", KeyboardKey::Home}, {"End", KeyboardKey::End},
                {"PageUp", KeyboardKey::PageUp}, {"PageDown", KeyboardKey::PageDown},
                {"LeftWin", KeyboardKey::LeftWin}, {"RightWin", KeyboardKey::RightWin},
                {"Apps", KeyboardKey::Apps}, {"Sleep", KeyboardKey::Sleep},

                // Numpad
                {"Numpad0", KeyboardKey::Numpad0}, {"Numpad1", KeyboardKey::Numpad1}, {"Numpad2", KeyboardKey::Numpad2},
                {"Numpad3", KeyboardKey::Numpad3}, {"Numpad4", KeyboardKey::Numpad4}, {"Numpad5", KeyboardKey::Numpad5},
                {"Numpad6", KeyboardKey::Numpad6}, {"Numpad7", KeyboardKey::Numpad7}, {"Numpad8", KeyboardKey::Numpad8},
                {"Numpad9", KeyboardKey::Numpad9}, {"NumpadMultiply", KeyboardKey::NumpadMultiply},
                {"NumpadAdd", KeyboardKey::NumpadAdd}, {"NumpadSeparator", KeyboardKey::NumpadSeparator},
                {"NumpadSubtract", KeyboardKey::NumpadSubtract}, {"NumpadDecimal", KeyboardKey::NumpadDecimal},
                {"NumpadDivide", KeyboardKey::NumpadDivide}
            };

            auto it = map.find(str);
            return it != map.end() ? it->second : KeyboardKey::Unknown;
        }
        inline const char *KeyToString(KeyboardKey key) {
            switch (key) {
                case KeyboardKey::A: return "A"; case KeyboardKey::B: return "B";
                case KeyboardKey::C: return "C"; case KeyboardKey::D: return "D";
                case KeyboardKey::E: return "E"; case KeyboardKey::F: return "F";
                case KeyboardKey::G: return "G"; case KeyboardKey::H: return "H";
                case KeyboardKey::I: return "I"; case KeyboardKey::J: return "J";
                case KeyboardKey::K: return "K"; case KeyboardKey::L: return "L";
                case KeyboardKey::M: return "M"; case KeyboardKey::N: return "N";
                case KeyboardKey::O: return "O"; case KeyboardKey::P: return "P";
                case KeyboardKey::Q: return "Q"; case KeyboardKey::R: return "R";
                case KeyboardKey::S: return "S"; case KeyboardKey::T: return "T";
                case KeyboardKey::U: return "U"; case KeyboardKey::V: return "V";
                case KeyboardKey::W: return "W"; case KeyboardKey::X: return "X";
                case KeyboardKey::Y: return "Y"; case KeyboardKey::Z: return "Z";
                case KeyboardKey::Num0: return "0"; case KeyboardKey::Num1: return "1";
                case KeyboardKey::Num2: return "2"; case KeyboardKey::Num3: return "3";
                case KeyboardKey::Num4: return "4"; case KeyboardKey::Num5: return "5";
                case KeyboardKey::Num6: return "6"; case KeyboardKey::Num7: return "7";
                case KeyboardKey::Num8: return "8"; case KeyboardKey::Num9: return "9";
                case KeyboardKey::F1: return "F1"; case KeyboardKey::F2: return "F2";
                case KeyboardKey::F3: return "F3"; case KeyboardKey::F4: return "F4";
                case KeyboardKey::F5: return "F5"; case KeyboardKey::F6: return "F6";
                case KeyboardKey::F7: return "F7"; case KeyboardKey::F8: return "F8";
                case KeyboardKey::F9: return "F9"; case KeyboardKey::F10: return "F10";
                case KeyboardKey::F11: return "F11"; case KeyboardKey::F12: return "F12";
                case KeyboardKey::LeftCtrl: return "LeftCtrl"; case KeyboardKey::RightCtrl: return "RightCtrl";
                case KeyboardKey::LeftShift: return "LeftShift"; case KeyboardKey::RightShift: return "RightShift";
                case KeyboardKey::LeftAlt: return "LeftAlt"; case KeyboardKey::RightAlt: return "RightAlt";
                case KeyboardKey::Space: return "Space"; case KeyboardKey::Enter: return "Enter";
                case KeyboardKey::Escape: return "Escape"; case KeyboardKey::Tab: return "Tab";
                case KeyboardKey::Backspace: return "Backspace"; case KeyboardKey::UpArrow: return "UpArrow";
                case KeyboardKey::DownArrow: return "DownArrow"; case KeyboardKey::LeftArrow: return "LeftArrow";
                case KeyboardKey::RightArrow: return "RightArrow"; case KeyboardKey::CapsLock: return "CapsLock";
                case KeyboardKey::NumLock: return "NumLock"; case KeyboardKey::ScrollLock: return "ScrollLock";
                case KeyboardKey::PrintScreen: return "PrintScreen"; case KeyboardKey::Insert: return "Insert";
                case KeyboardKey::Delete: return "Delete"; case KeyboardKey::Home: return "Home";
                case KeyboardKey::End: return "End"; case KeyboardKey::PageUp: return "PageUp";
                case KeyboardKey::PageDown: return "PageDown"; case KeyboardKey::LeftWin: return "LeftWin";
                case KeyboardKey::RightWin: return "RightWin"; case KeyboardKey::Apps: return "Apps";
                case KeyboardKey::Sleep: return "Sleep"; case KeyboardKey::Numpad0: return "Numpad0";
                case KeyboardKey::Numpad1: return "Numpad1"; case KeyboardKey::Numpad2: return "Numpad2";
                case KeyboardKey::Numpad3: return "Numpad3"; case KeyboardKey::Numpad4: return "Numpad4";
                case KeyboardKey::Numpad5: return "Numpad5"; case KeyboardKey::Numpad6: return "Numpad6";
                case KeyboardKey::Numpad7: return "Numpad7"; case KeyboardKey::Numpad8: return "Numpad8";
                case KeyboardKey::Numpad9: return "Numpad9"; case KeyboardKey::NumpadMultiply: return "NumpadMultiply";
                case KeyboardKey::NumpadAdd: return "NumpadAdd"; case KeyboardKey::NumpadSeparator: return "NumpadSeparator";
                case KeyboardKey::NumpadSubtract: return "NumpadSubtract";
                case KeyboardKey::NumpadDecimal: return "NumpadDecimal";
                case KeyboardKey::NumpadDivide: return "NumpadDivide";

                default: return INVALID_KEY_NAME;
            }
        }

		inline MouseKey StringToMouseKey(const std::string &str) {
			static const std::unordered_map<std::string, MouseKey> map = {
				{"Left", MouseKey::Left},
				{"Right", MouseKey::Right},
				{"Middle", MouseKey::Middle},
			};
			auto it = map.find(str);
			return it != map.end() ? it->second : MouseKey::Unknown;
		}
        inline const char *KeyToString(MouseKey key) {

            switch (key) {

				case MouseKey::Left: return "Left";
				case MouseKey::Right: return "Right";
				case MouseKey::Middle: return "Middle";

                default: return INVALID_KEY_NAME;
            }
        }

        inline GamepadKey StringToGamepadKey(const std::string &str) {
            static const std::unordered_map<std::string, GamepadKey> map = {
                {"A", GamepadKey::A}, {"B", GamepadKey::B},
				{"X", GamepadKey::X}, {"Y", GamepadKey::Y},
				{"LB", GamepadKey::LB}, {"RB", GamepadKey::RB}
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