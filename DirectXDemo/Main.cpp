#include "main.h"
#include "DxWindow.h"
std::shared_ptr<DxWindow> g_Window;
//This is the entry point into the program
//initialize everything and start the main loop
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

	MSG msg = { 0 };
	g_Window = std::shared_ptr<DxWindow>(new DxWindow(hInstance, nCmdShow));
	return g_Window->MainLoop();
}