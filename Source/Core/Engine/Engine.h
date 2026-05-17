#pragma once
#include "Graphics/IRenderer.h"

namespace RF {
    struct FrameData;
	struct WindowCreationParams;
    class Window;

    struct EngineCreationParams {
        WNDPROC windowProc = nullptr;
        int cmdShow = 0;
        HINSTANCE hInstance = nullptr;
	};

    enum class GraphicsAPI {
        DirectX11,
        DirectX12,
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
		void LoadConfigFile(RF::WindowCreationParams& windowParams);

        std::unique_ptr<Window> mWindow;
		std::unique_ptr<IRenderer> mRenderer;
		GraphicsAPI mGraphicsAPI = GraphicsAPI::DirectX11;

        std::wstring mAssetsPath;
    };
}
