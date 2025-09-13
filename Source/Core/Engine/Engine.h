#pragma once


namespace RF {
    struct FrameData;
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

    private:

        std::unique_ptr<Window> mWindow;

        std::wstring mAssetsPath;
    };
}