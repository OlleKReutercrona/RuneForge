#include "stdafx.h"
#include "Engine.h"
#include "Window/Window.h"
#include "frameData.h"
#include "Util/jsonUtil.h"

#include <nlohmann/json.hpp>

namespace {
	constexpr std::string_view gConfigFilePath = "../engineConfig.json";
}

RF::Engine::Engine(const RF::EngineCreationParams& params) :mInputHandler(mRawInput) {
	RF::WindowCreationParams windowParams;
	windowParams.hInstance = params.hInstance;
	windowParams.cmdShow = params.cmdShow;
	windowParams.engine = this;
	windowParams.windowProc = params.windowProc;

	LoadConfigFile(windowParams);

	mWindow = std::make_unique<RF::Window>();
	mWindow->Init(windowParams);
	mInputHandler.Initialize();
}

void RF::Engine::Update(const FrameData& frameData) { 
	frameData; 

	mInputHandler.Update();
}

void RF::Engine::Render(const FrameData& frameData) { frameData; }

void RF::Engine::Shutdown() {}

void RF::Engine::OnResize(const unsigned int width, const unsigned int height) {
	mWindow->SetSize(width, height);
}

void RF::Engine::LoadConfigFile(RF::WindowCreationParams& windowParams) {
	auto json = RF::Json::Parse(static_cast<std::string>(gConfigFilePath));

	auto windowSettingsJson = RF::Json::TryGet<nlohmann::json>(json, "windowSettings", {});
	if (windowSettingsJson.empty()) {
		return;
	}

	auto windowSizeJson = RF::Json::TryGet<nlohmann::json>(windowSettingsJson, "windowSize", {});
	if (!windowSettingsJson.empty()) {
		windowParams.width = RF::Json::TryGet(windowSizeJson, "width", windowParams.width);
		windowParams.height = RF::Json::TryGet(windowSizeJson, "height", windowParams.height);
	}

	std::string title = RF::Json::TryGet(windowSettingsJson, "title", std::string("RuneForge"));
	windowParams.title = std::wstring(title.begin(), title.end());

	windowParams.isFullScreen = RF::Json::TryGet(windowSettingsJson, "startInFullscreen", false);

	windowParams.isResizable = RF::Json::TryGet(windowSettingsJson, "isResizable", true);
}
