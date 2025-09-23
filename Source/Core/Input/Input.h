#pragma once
#include "Input/CommonInput.h"
#include "KeyCodes.h"

namespace RF {

    namespace input {

        class Input {
        public:
            friend class InputHandler;

            Input();
            ~Input() = default;

            bool RegisterDevices(HWND hwnd, bool noLegacy = true);

            void ProcessRawInput(LPARAM lParam);

            // Per-frame: call at start of frame (before using pressed/released)
            void Update(); // resets per-frame state (pressed/released, zero mouse delta)

            bool IsKeyDown(KeyCode vkey) const; // currently down
            bool IsKeyPressed(KeyCode vkey) const; // went down this frame
            bool IsKeyReleased(KeyCode vkey) const; // went up this frame

            int GetMouseDeltaX() const { return mouseDeltaX; }
            int GetMouseDeltaY() const { return mouseDeltaY; }
            int GetWheelDelta() const { return wheelDelta; }

            void SetNotifyFunc(std::function<void(KeyCode)> notifyCallback);
            void SetNotifyMask(std::bitset<MAX_KEYS> &notifyMask);

        private:

            // Helpers
            void InjectKeyboard(USHORT vkey, USHORT flags);
            void InjectMouse(const RAWMOUSE &m);

            void NotifyKeybindPress(KeyCode key);

            // Key state
            std::bitset<MAX_KEYS> keyCurrent;   // indexed by virtual-key
            std::bitset<MAX_KEYS> keyPressed;   // pressed this frame
            std::bitset<MAX_KEYS> keyReleased;  // released this frame

            std::bitset<MAX_KEYS> mNotifyMask; // if any key within this bitset is pressed -> Notify InputHandler.
            std::function<void(KeyCode)> mNotifyCallback = nullptr;

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