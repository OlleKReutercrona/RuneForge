#include "stdafx.h"
#include "Engine.h"
#include "Window/Window.h"

RF::Engine::Engine() {
}

void RF::Engine::Init(std::shared_ptr<RF::Window> window) {
	mWindow = std::move(window);
}

void RF::Engine::Update(const FrameData& frameData) { frameData; }

void RF::Engine::Render(const FrameData& frameData) { frameData; }

void RF::Engine::Shutdown() {}

const std::wstring RF::Engine::GetTitle() const {
	return mWindow->GetTitle();
}

void RF::Engine::OnResize(const unsigned int width, const unsigned int height) {
	mWindow->SetWindowSize(width, height);
}

void RF::Engine::SetCustomWindowText(const std::wstring& text) {
	mWindow->setCustomText(text);
}
