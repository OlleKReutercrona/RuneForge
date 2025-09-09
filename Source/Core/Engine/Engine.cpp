#include "stdafx.h"
#include "Engine.h"
#include "Window/Window.h"
#include "frameData.h"

RF::Engine::Engine(const RF::EngineCreationParams& params) {
	RF::WindowCreationParams windowParams;
	windowParams.hInstance = params.hInstance;
	windowParams.cmdShow = params.cmdShow;
	windowParams.engine = this;
	windowParams.windowProc = params.windowProc;

	LoadConfigFile(windowParams);

	mWindow = std::make_unique<RF::Window>();
	mWindow->Init(windowParams);
}

void RF::Engine::Update(const FrameData& frameData) { frameData; }

void RF::Engine::Render(const FrameData& frameData) { frameData; }

void RF::Engine::Shutdown() {}

void RF::Engine::OnResize(const unsigned int width, const unsigned int height) {
	mWindow->SetSize(width, height);
}

void RF::Engine::LoadConfigFile(RF::WindowCreationParams& windowParams) {
	std::ifstream file("../config.json");
	nlohmann::json json;
	if (!file.good()) {
		file.close();
		return;
	}

	json = nlohmann::json::parse(file);

	if (json.contains("windowSettings")) {
		auto windowSettings = json["windowSettings"];

		if (windowSettings.contains("windowSize")) {
			auto windowSize = windowSettings["windowSize"];
			if (windowSize.contains("width")) {
				windowParams.width = windowSize["width"].get<unsigned int>();
			}
			if (windowSize.contains("height")) {
				windowParams.height = windowSize["height"].get<unsigned int>();
			}
		}

		if (windowSettings.contains("title")) {
			auto title = windowSettings["title"].get<std::string>();
			windowParams.title = std::wstring(title.begin(), title.end());
		}

		if (windowSettings.contains("startInFullscreen")) {
			windowParams.isFullScreen = windowSettings["startInFullscreen"].get<bool>();
		}

		if (windowSettings.contains("isResizable")) {
			windowParams.isResizable = windowSettings["isResizable"].get<bool>();
		}
		// TODO: Implement later when vector4 and clear color is needed
		//if (windowSettings.contains("clearColor")) {
		//	Vector4 clearColor;
		//	clearColor.x = windowSettings["clearColor"]["r"].get<float>();
		//	clearColor.y = windowSettings["clearColor"]["g"].get<float>();
		//	clearColor.z = windowSettings["clearColor"]["b"].get<float>();
		//	clearColor.w = windowSettings["clearColor"]["a"].get<float>();
		//}
	}

}
