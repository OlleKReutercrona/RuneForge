#pragma once
namespace RF {
	class Engine;

class WindowsApplication {
public:
	int Run(HINSTANCE hInstance, int cmdShow);

private:
	static LRESULT CALLBACK WindowProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);
};
}
