#pragma once
#include "main.h"
#include "DxRenderer.h"
//This is the main window wrapper class
//It creates a window and has a main loop
class DxWindow
{
public:
	DxWindow(HINSTANCE hInstance, int nCmdShow);
	~DxWindow();

	HINSTANCE                           g_hInst = nullptr;
	HWND                                g_hWnd = nullptr;

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	int MainLoop();
	
};

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

