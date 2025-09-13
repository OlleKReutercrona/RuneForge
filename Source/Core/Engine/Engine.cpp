#include "stdafx.h"
#include "Engine.h"
#include "Window/Window.h"
#include "frameData.h"

RF::Engine::Engine(const RF::EngineCreationParams& params) {
	// TODO: Load some of these from config file
	RF::WindowCreationParams windowParams;
	windowParams.width = 1920;
	windowParams.height = 1080;
	windowParams.title = L"RuneForge";
	windowParams.isFullScreen = false;
	windowParams.isResizable = true;
	windowParams.hInstance = params.hInstance;
	windowParams.cmdShow = params.cmdShow;
	windowParams.engine = this;
	windowParams.windowProc = params.windowProc;

	mWindow = std::make_unique<RF::Window>();
	mWindow->Init(windowParams);
}

void RF::Engine::Update(const FrameData& frameData) { frameData; }

void RF::Engine::Render(const FrameData& frameData) { frameData; }

void RF::Engine::Shutdown() {}

void RF::Engine::OnResize(const unsigned int width, const unsigned int height) {
	mWindow->SetSize(width, height);
}
