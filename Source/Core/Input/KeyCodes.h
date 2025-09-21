#pragma once

namespace RF {
    namespace input {

        constexpr const char *INVALID_KEY_NAME = "Unknown";
        constexpr uint32_t INVALID_KEY_CODE = 0xFFFFFFFF;

        // Mouse buttons
        enum class MouseKey : uint32_t {
            Left = 0,
            Right = 1,
            Middle = 2,

            Unknown = INVALID_KEY_CODE
        };

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

        enum class KeyboardKey : uint32_t {
            // Letters
            A = 'A',
            B = 'B', C = 'C', D = 'D', E = 'E', F = 'F',
            G = 'G', H = 'H', I = 'I', J = 'J', K = 'K',
            L = 'L', M = 'M', N = 'N', O = 'O', P = 'P',
            Q = 'Q', R = 'R', S = 'S', T = 'T', U = 'U',
            V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z',

            // Numbers
            Num0 = 0x30, Num1 = 0x31, Num2 = 0x32, Num3 = 0x33,
            Num4 = 0x34, Num5 = 0x35, Num6 = 0x36, Num7 = 0x37,
            Num8 = 0x38, Num9 = 0x39,

            // Function keys
            F1 = 0x70, F2 = 0x71, F3 = 0x72, F4 = 0x73, F5 = 0x74,
            F6 = 0x75, F7 = 0x76, F8 = 0x77, F9 = 0x78, F10 = 0x79,
            F11 = 0x7A, F12 = 0x7B,

            // Modifiers
            LeftCtrl = 0xA2, RightCtrl = 0xA3,
            LeftShift = 0xA0, RightShift = 0xA1,
            LeftAlt = 0xA4, RightAlt = 0xA5,

            // Special keys
            Space = 0x20, Enter = 0x0D, Escape = 0x1B, Tab = 0x09,
            Backspace = 0x08, UpArrow = 0x26, DownArrow = 0x28,
            LeftArrow = 0x25, RightArrow = 0x27, CapsLock = 0x14,
            NumLock = 0x90, ScrollLock = 0x91, PrintScreen = 0x2C,
            Insert = 0x2D, Delete = 0x2E, Home = 0x24, End = 0x23,
            PageUp = 0x21, PageDown = 0x22, LeftWin = 0x5B,
            RightWin = 0x5C, Apps = 0x5D, Sleep = 0x5F,

            // Numpad keys
            Numpad0 = 0x60, Numpad1 = 0x61, Numpad2 = 0x62,
            Numpad3 = 0x63, Numpad4 = 0x64, Numpad5 = 0x65,
            Numpad6 = 0x66, Numpad7 = 0x67, Numpad8 = 0x68,
            Numpad9 = 0x69,
            NumpadMultiply = 0x6A,
            NumpadAdd = 0x6B,
            NumpadSeparator = 0x6C,
            NumpadSubtract = 0x6D,
            NumpadDecimal = 0x6E,
            NumpadDivide = 0x6F,

            Unknown = INVALID_KEY_CODE
        };

    }
}