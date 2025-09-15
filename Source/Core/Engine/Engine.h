#pragma once
#include "Input/Input.h"

namespace RF {
    struct FrameData;
	struct WindowCreationParams;
    class Window;

    struct EngineCreationParams {
        WNDPROC windowProc = nullptr;
        int cmdShow = 0;
        HINSTANCE hInstance = nullptr;
	};

    class Engine {
    public:
        Engine() = delete;
        Engine(const EngineCreationParams& params);
        ~Engine() = default;
		Engine(const Engine&) = delete;
		void operator=(const Engine&) = delete;

		void Update(const FrameData& frameData);
        void Render(const FrameData& frameData);

		void Shutdown();

        void OnResize(const unsigned int width, const unsigned int height);

        Input &GetInput() { return mInput; }

    private:
		void LoadConfigFile(RF::WindowCreationParams& windowParams);

        std::unique_ptr<Window> mWindow;

        std::wstring mAssetsPath;

        Input mInput;
    };
}