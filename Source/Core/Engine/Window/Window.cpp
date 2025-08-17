#include "stdafx.h"
#include "Window.h"

RF::Window::Window(WindowCreationParams params) :
    mWidth(params.width),
    mHeight(params.height),
    mHWND(nullptr),
    mWindowTitle(params.title),
	mAspectRatio(static_cast<float>(params.width) / static_cast<float>(params.height)) {

    // Initialize the window class
    WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = params.windowProc;
    windowClass.hInstance = params.hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = mWindowTitle.c_str();
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    //windowClass.hIcon = icon; // Todo in the future

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
		nullptr, // todo : might use menus in the future
		params.hInstance,
        params.engine);

	// todo check if hwnd is valid

	ShowWindow(mHWND, params.cmdShow);
}

void RF::Window::SetWindowSize(const unsigned int width, const unsigned int height) {
    mWidth = width;
	mHeight = height;
}

void RF::Window::SetTitle(const std::wstring& title) {
    mWindowTitle = title;

	ApplyWindowText();
}

void RF::Window::setCustomText(const std::wstring& text) {
	mCustomText = text;

	ApplyWindowText();
}

const std::wstring RF::Window::GetTitle() const {
	return mWindowTitle + L": " + mCustomText;
}

HWND RF::Window::GetHWND() const {
    return mHWND;
}

void RF::Window::SetFullScreen(const bool isFullScreen) { isFullScreen; }

void RF::Window::ApplyWindowText() {
    std::wstring windowText = mWindowTitle + mCustomText;
    SetWindowText(mHWND, windowText.c_str());
}
