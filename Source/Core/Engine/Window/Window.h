#pragma once
namespace RF {
	class Engine;

	struct WindowCreationParams {
		unsigned int width = 1920;
		unsigned int height = 1080;
		std::wstring title = L"RuneForge";
		bool isFullScreen = false;
		bool isResizable = true;

		HINSTANCE hInstance = nullptr;
		int	cmdShow = 0;
		RF::Engine* engine = nullptr;
		WNDPROC windowProc = nullptr;
	};

	class Window {
	public:
		Window() = default;
		Window(const Window&) = delete;
		void operator=(const Window&) = delete;

		void Init(const WindowCreationParams& params);
		void SetSize(const unsigned int width, const unsigned int height); // TODO - Vector2ui
		//const RF::V2ui Size() const; // TODO - Vector2ui

		void SetTitle(const std::wstring& title);
		void SetCustomText(const std::wstring& text);
		const std::wstring Title() const;

		HWND GetHWND() const;

		void SetFullScreen(const bool isFullScreen);
	private:
		void ApplyWindowText();

		std::wstring mWindowTitle = {};
		std::wstring mCustomText = {};
		unsigned int mWidth = {};
		unsigned int mHeight = {};
		float mAspectRatio = {};
		HWND mHWND = {};
	};
}
