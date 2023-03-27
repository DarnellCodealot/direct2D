#include "graphics.h"
#include "window.h"
#include "sprite.h"
#include <chrono>
#include <thread>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

#define DELTA_TIME 1000/60

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")


int main() {
    //FreeConsole();

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Find Him");
    Graphics gfx(window);
    ID2D1SolidColorBrush* testerColor;
    gfx.pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.0f), &testerColor);

    MSG msg{};
    msg.message = WM_NULL;
    auto next_frame = std::chrono::steady_clock::now();
    while (true) {
        //limiting the fps
        next_frame += std::chrono::milliseconds(DELTA_TIME);

        //taking care of window messages
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                break;
            }
        }

        //drawing
        gfx.Begin(0,0,0);

        gfx.End();

        std::this_thread::sleep_until(next_frame);
    }
    return msg.wParam;
}