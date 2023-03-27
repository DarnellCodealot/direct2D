#include "window.h"

Window::Window(int x, int y, std::string name)
{
    auto hInstance = GetModuleHandle(NULL);
    WNDCLASSEXA ds = {
        sizeof(WNDCLASSEXA),
        CS_OWNDC,
        myWndProc,
        0,
        0,
        hInstance,
        NULL,
        NULL,
        NULL,
        NULL,
        "winclass",
        NULL
    };
    RegisterClassExA(&ds);
    RECT acr;
    acr.left = 0;
    acr.right = x;
    acr.top = 0;
    acr.bottom = y;
    AdjustWindowRect(&acr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, NULL);
    hwnd = CreateWindowA("winclass", name.c_str(), WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 100, 100, acr.right-acr.left, acr.bottom-acr.top, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOW);
    RECT cr;
    GetClientRect(hwnd, &cr);
    this->crWidth = cr.right;
    this->crHeight = cr.bottom;
}

Window::~Window()
{
    DestroyWindow(hwnd);
    UnregisterClassA("winclass", GetModuleHandle(NULL));
}

LRESULT CALLBACK Window::myWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}
