#pragma once
namespace RF {
    // Might move to its own file later for include ease
    struct FrameData {
        float deltaTime = 0.0f;
        float totalTime = 0.0f;
	};

    class Window;

    class Engine {
    public:
        Engine();
        ~Engine() = default;
		Engine(const Engine&) = delete;
		void operator=(const Engine&) = delete;

        void Init(std::shared_ptr<RF::Window> window);

		void Update(const FrameData& frameData);
        void Render(const FrameData& frameData);

		void Shutdown();

        void OnResize(const unsigned int width, const unsigned int height);

    private:

        std::shared_ptr<Window> mWindow;

        std::wstring mAssetsPath;
    };
}