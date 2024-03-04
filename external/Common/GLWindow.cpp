#include "GLWindow.h"
#include <functional>

std::shared_ptr<GLWindow> GLWindow::g_window =nullptr;

std::function<void()> draw = nullptr;

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

GLWindow* GLCreateWindow(int cx, int cy, LPCSTR title, DWORD flag)
{
    GLWindow::g_window = std::make_shared<GLWindow>();

    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "GLWindow";
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;

    if(!RegisterClassExA(&wc)){
        return nullptr;
    }

    int x = (GetSystemMetrics(SM_CXSCREEN) - cx) /2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - cy) /2;

    DWORD style = WS_OVERLAPPEDWINDOW;

    GLWindow* window = GLWindow::g_window.get();

    window->mHwnd = CreateWindowExA(
        NULL, wc.lpszClassName, title, style, 
        x,y,cx,cy,nullptr, (HMENU)0, wc.hInstance, window
    );

    auto console = GetConsoleWindow();
    MoveWindow(console, 0,0, 
        GetSystemMetrics(SM_CXSCREEN) / 3,
        GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYCAPTION) - 10, TRUE);

    window->mRC = GL::CreateGLContext(window->mHwnd);
    window->mDC = GetDC(window->mHwnd);

    //GL FLAGS
    if(flag & CCW){
        printf("[Draw Order Right Hand : CCW]\n");
    }else{
        printf("[Draw Order Left Hand : CW]\n");
    }
    if(flag & VsyncEnable){
        printf("[Vsync : On]\n");
    }else{
        printf("[Vsync : Off]\n");
    }

    ShowWindow(window->mHwnd, TRUE);

 
    return window;
}

HRESULT GLSwapBuffers(GLWindow *pWindow)
{
    if(!pWindow) return E_INVALIDARG;
    if(!SwapBuffers(pWindow->mDC)) return GetLastError();
    return S_OK;
}

BOOL GLBeginFrame(GLWindow* pWindow){
	MSG msg{};
	if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
        pWindow->mIsActive = false;
		if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE){
			PostQuitMessage(0);
			pWindow->mIsRunning = false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    else{
        pWindow->mIsActive = true;
    }
	return pWindow->mIsRunning;
}

GLWindow::~GLWindow()
{
    GL::ReleaseContext(mHwnd, mRC, mDC);
    DestroyWindow(mHwnd);
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    GLWindow* window = (GLWindow*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    if(msg == WM_NCCREATE){
        window = (GLWindow*)((LPCREATESTRUCT)lp)->lpCreateParams;
        window->mHwnd = hwnd;
        SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)window);
    }
    if(msg == WM_CLOSE){
        //TODO : replace it to callback func
        if(window){
            printf("window alive\n");
            window->mIsRunning = false;
            PostQuitMessage(0);
        }
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}
