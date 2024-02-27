#include <iostream>
#include <GLExtension.h>
//#include <GL/wglew.h>

#include <windows.h>

LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);


int main(int args, char* argv[]){
    WNDCLASSEX  wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // ACTIVATES RELOAD ON REDRAW
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle(nullptr);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = 0;
	wndclass.lpszClassName = "Wnd++";

	RegisterClassEx(&wndclass);
    

	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int clientWidth = 800;
	int clientHeight = 600;

	RECT windowRect;
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setrect
	SetRect(&windowRect, (ScreenWidth / 2) - (clientWidth / 2),
		(ScreenHeight / 2) - (clientHeight / 2),
		(ScreenWidth / 2) + (clientWidth / 2),
		(ScreenHeight / 2) + (clientHeight / 2));


	// https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
	DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);

	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrectex
	AdjustWindowRectEx(&windowRect, style, FALSE, 0);
	const wchar_t windowName[] = L"OpenGL Window";

	//DWORD secondaryStyle = (WS_EX_ACCEPTFILES);

	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	HWND hwnd = CreateWindowEx(0, wndclass.lpszClassName, wndclass.lpszClassName, style, windowRect.left, windowRect.top, windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, NULL, NULL, wndclass.hInstance, 0);
	HDC hdc = GetDC(hwnd);

	



    return 0;
};

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	return DefWindowProc(hwnd, msg, wp, lp);
}