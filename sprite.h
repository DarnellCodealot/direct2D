#pragma once
#include <wincodec.h>
#include <d2d1.h>
#include "graphics.h"

class Sprite {
public:
	Sprite(const wchar_t* name, const Graphics& gfx, float x = 0.0f, float y = 0.0f);
	void Draw();
	void Draw(int nx, int ny);
	void DrawPart(int startx, int endx);
	~Sprite();

public:
	float GetWidth() const;
	float GetHeight() const;

public:
	ID2D1Bitmap* pBmp;
	const Graphics& gfx;
	float x;
	float y;
};
