#include "graphics.h"

Graphics::Graphics(const Window &window) {
    ID2D1Factory* pDirect2dFactory = nullptr;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory);
    RECT rc;
    GetClientRect(window.hwnd, &rc);
    D2D1_SIZE_U CRsize = D2D1::SizeU( //stands for client region size
        rc.right - rc.left,
        rc.bottom - rc.top
    );
    pDirect2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(window.hwnd, CRsize), &pRenderTarget);
    pDirect2dFactory->Release();
}

Graphics::~Graphics() {
    pRenderTarget->Release();
}

void Graphics::Begin(float r, float g, float b) {
    pRenderTarget->BeginDraw();
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pRenderTarget->Clear(D2D1::ColorF(r,g,b));
}

void Graphics::End(){
    pRenderTarget->EndDraw();
}
