#pragma once
#include "sprite.h"

Sprite::Sprite(const wchar_t* name, const Graphics& gfx, float x, float y): gfx(gfx), x(x), y(y) {
    IWICImagingFactory* pWicFactory = NULL;
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pWicFrame = NULL;
    IWICFormatConverter* pFormatConverter = NULL;

    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, ((LPVOID*)&pWicFactory));
    pWicFactory->CreateDecoderFromFilename(
        name,                            // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );
    pDecoder->GetFrame(0, &pWicFrame);
    pWicFactory->CreateFormatConverter(&pFormatConverter);

    pFormatConverter->Initialize(pWicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

    gfx.pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBmp);

    if (pWicFactory) pWicFactory->Release();
    if (pDecoder) pDecoder->Release();
    if (pWicFrame) pWicFrame->Release();
    if (pFormatConverter) pFormatConverter->Release();
}

float Sprite::GetHeight() const {
    return pBmp->GetSize().height;
}

float Sprite::GetWidth() const {
    return pBmp->GetSize().width;
}

void Sprite::Draw() {
    gfx.pRenderTarget->DrawBitmap(pBmp, D2D1::RectF(x, y, x + this->GetWidth(), y + this->GetHeight()), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, pBmp->GetSize().width, pBmp->GetSize().height));
}

void Sprite::Draw(int nx, int ny) {
    gfx.pRenderTarget->DrawBitmap(pBmp, D2D1::RectF(nx, ny, nx + this->GetWidth(), ny + this->GetHeight()), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, pBmp->GetSize().width, pBmp->GetSize().height));
}

void Sprite::DrawPart(int startx, int endx) {
    gfx.pRenderTarget->DrawBitmap(pBmp, D2D1::RectF(x, y, x + endx - startx, y + this->GetHeight()), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(startx, 0.0f, endx, pBmp->GetSize().height));
}

Sprite::~Sprite() {
    if (pBmp) pBmp->Release();
}
