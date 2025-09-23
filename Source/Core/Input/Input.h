#pragma once
#include "Input/CommonInput.h"
#include "KeyCodes.h"

namespace RF {

    namespace input {

        class Input {
        public:
            Input();
            ~Input() = default;

            bool RegisterDevices(HWND hwnd, bool noLegacy = true);

            void ProcessRawInput(LPARAM lParam);

            // Per-frame: call at start of frame (before using pressed/released)
            void Update(); // resets per-frame state (pressed/released, zero mouse delta)

            bool IsKeyDown(KeyCode vkey) const; // currently down
            bool IsKeyPressed(KeyCode vkey) const; // went down this frame
            bool IsKeyReleased(KeyCode vkey) const; // went up this frame

            bool IsMouseButtonDown(int buttonIdx) const; // 0=left,1=right,2=middle
            bool IsMouseButtonPressed(int buttonIdx) const;
            bool IsMouseButtonReleased(int buttonIdx) const;

            int GetMouseDeltaX() const { return mouseDeltaX; }
            int GetMouseDeltaY() const { return mouseDeltaY; }
            int GetWheelDelta() const { return wheelDelta; }

        private:
            // Helpers
            void InjectKeyboard(USHORT vkey, USHORT flags);
            void InjectMouse(const RAWMOUSE &m);

            // Key state
            std::bitset<256> keyCurrent;   // indexed by virtual-key
            std::bitset<256> keyPressed;   // pressed this frame
            std::bitset<256> keyReleased;  // released this frame

            // Mouse state
            std::bitset<8> mouseCurrent;
            std::bitset<8> mousePressed;
            std::bitset<8> mouseReleased;

            int mouseDeltaX = 0;
            int mouseDeltaY = 0;
            int wheelDelta = 0; // accumulated wheel (WHEEL_DELTA units)

            // Micro-optimization: small stack buffer we reuse to avoid allocation every event.
            // Many RAWINPUT packets are <= 1024 bytes; if bigger we fallback to vector allocation.
            static constexpr UINT STACK_BUFFER_SIZE = 2048;
            std::array<BYTE, STACK_BUFFER_SIZE> stackBuffer = {};
        };
    }
}