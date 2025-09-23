#pragma once

namespace RF {
	namespace input {

		constexpr const char *INVALID_KEY_NAME = "Unknown";
		constexpr uint32_t INVALID_KEY_CODE = 0xFFFFFFFF;

		// Gamepad buttons (example: Xbox-style)
		enum class GamepadKey : uint32_t {
			A = 0,
			B = 1,
			X = 2,
			Y = 3,
			LB = 4,
			RB = 5,

			Unknown = INVALID_KEY_CODE
		};

        enum class KeyCode : uint32_t {
            // Mouse buttons
            MouseLeft = 0,
            MouseRight = 1,
            MouseMiddle = 2,
            MouseX1 = 3,
            MouseX2 = 4,

            // Letters
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,

            // Numbers
            Num0 = 48,
            Num1 = 49,
            Num2 = 50,
            Num3 = 51,
            Num4 = 52,
            Num5 = 53,
            Num6 = 54,
            Num7 = 55,
            Num8 = 56,
            Num9 = 57,

            // Function keys
            F1 = 112,
            F2 = 113,
            F3 = 114,
            F4 = 115,
            F5 = 116,
            F6 = 117,
            F7 = 118,
            F8 = 119,
            F9 = 120,
            F10 = 121,
            F11 = 122,
            F12 = 123,

            // Modifiers
            LeftCtrl = 162,
            RightCtrl = 163,
            LeftShift = 160,
            RightShift = 161,
            LeftAlt = 164,
            RightAlt = 165,

            // Special keys
            Space = 32,
            Enter = 13,
            Escape = 27,
            Tab = 9,
            Backspace = 8,
            UpArrow = 38,
            DownArrow = 40,
            LeftArrow = 37,
            RightArrow = 39,
            CapsLock = 20,
            NumLock = 144,
            ScrollLock = 145,
            PrintScreen = 44,
            Insert = 45,
            Delete = 46,
            Home = 36,
            End = 35,
            PageUp = 33,
            PageDown = 34,
            LeftWin = 91,
            RightWin = 92,
            Apps = 93,
            Sleep = 95,

            // Numpad keys
            Numpad0 = 96,
            Numpad1 = 97,
            Numpad2 = 98,
            Numpad3 = 99,
            Numpad4 = 100,
            Numpad5 = 101,
            Numpad6 = 102,
            Numpad7 = 103,
            Numpad8 = 104,
            Numpad9 = 105,
            NumpadMultiply = 106,
            NumpadAdd = 107,
            NumpadSeparator = 108,
            NumpadSubtract = 109,
            NumpadDecimal = 110,
            NumpadDivide = 111,

            Count = INVALID_KEY_CODE
        };

	}
}