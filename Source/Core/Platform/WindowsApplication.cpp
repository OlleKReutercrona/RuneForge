#include "stdafx.h"
#include "WindowsApplication.h"
#include "Engine/Engine.h"
#include "Engine/Window/Window.h"
#include "Engine/frameData.h"

int RF::WindowsApplication::Run(HINSTANCE hInstance, int cmdShow) {

	RF::EngineCreationParams engineParams;
	engineParams.windowProc = WindowProc;
	engineParams.cmdShow = cmdShow;
	engineParams.hInstance = hInstance;

	RF::Engine engine(engineParams);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {

		// Process queued messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		RF::FrameData frameData;
		frameData.deltaTime = 0.016f; // Simulated delta time TODO replace with actual time calculation
		frameData.totalTime += frameData.deltaTime;
		engine.Update(frameData);
		engine.Render(frameData);
	}

	engine.Shutdown();

	return static_cast<char>(msg.wParam);
}

LRESULT RF::WindowsApplication::WindowProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam) {

	RF::Engine* engine = reinterpret_cast<RF::Engine*>(GetWindowLongPtr(hWND, GWLP_USERDATA));

	switch (message) {
	case WM_CREATE: {
		// Saves the engine* passed from window constructor
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWND, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		return 0;
	}
	case WM_DESTROY: {

		PostQuitMessage(0);
		return 0;
	}
	case WM_SIZE:
	{
		engine->OnResize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	}

	return DefWindowProc(hWND, message, wParam, lParam);
}