#include "stdafx.h"
#include <Windows.h>
#include "Core/Platform/WindowsApplication.h"

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, PSTR cmdline, int cmdshow) {
	hInstancePrev;
	cmdline;
	hInstance;
	cmdshow;

	RF::WindowsApplication app;
	return 	app.Run(hInstance, cmdshow);
}
