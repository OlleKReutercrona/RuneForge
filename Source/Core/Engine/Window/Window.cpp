#include "stdafx.h"
#include "Window.h"

#include <stdexcept>

void RF::Window::Init(const WindowCreationParams& params)
{
	mWindowTitle = params.title;
	mCustomText = L"";
	mWidth = params.width;
	mHeight = params.height;
	mAspectRatio = static_cast<float>(params.width) / static_cast<float>(params.height);

	// Initialize the window class
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = params.windowProc;
	windowClass.hInstance = params.hInstance;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = mWindowTitle.c_str();
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 2));
	//windowClass.hIcon = icon; // TODO in the future

	RegisterClassEx(&windowClass);

	RECT windowRect = { 0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the window
	mHWND = CreateWindow(
		windowClass.lpszClassName,
		mWindowTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, // No parent window
		nullptr, // No menus (Maybe for editor in future)
		params.hInstance,
		params.engine);

	ShowWindow(mHWND, params.cmdShow);
}

void RF::Window::SetSize(const unsigned int width, const unsigned int height) {
    mWidth = width;
	mHeight = height;

    // TODO: Resize event
}

void RF::Window::SetTitle(const std::wstring& title) {
    mWindowTitle = title;

	ApplyWindowText();
}

void RF::Window::SetCustomText(const std::wstring& text) {
	mCustomText = text;

	ApplyWindowText();
}

const std::wstring RF::Window::Title() const {
	return mWindowTitle + L": " + mCustomText;
}

HWND RF::Window::GetHWND() const {
    return mHWND;
}

void RF::Window::SetFullScreen(const bool isFullScreen) { isFullScreen; }

void RF::Window::ApplyWindowText() {
    SetWindowText(mHWND, Title().c_str());
}
