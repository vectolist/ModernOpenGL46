#pragma once

#include "GLConfig.h"
#include <memory>

struct callbacks{
        void* src = nullptr;
        void* dst = nullptr;
    };

class GLWindow
{
public:
    GLWindow() = default;
    ~GLWindow();

    HWND mHwnd;
    HGLRC mRC;
    HDC mDC;
    static std::shared_ptr<GLWindow> g_window;
    bool mIsRunning = true;
    bool mIsActive = false;
    //test
    callbacks cb{};
};

typedef enum : unsigned int {
    NDC_ZeroToOne = 1 << 0,
    LeftHand = 1 << 1,
    CCW = 1 << 2,
    VsyncEnable = 1 << 3
}GLFlag;


GLWindow* GLCreateWindow(int cx, int cy, LPCSTR title, DWORD flag = 0U);
HRESULT GLSwapBuffers(GLWindow* pWindow);
BOOL GLBeginFrame(GLWindow* pWindow);





