#pragma once
#include <d2d1.h>
#include "window.h"

class Graphics
{
public:
	Graphics(const Window &window);
	//Graphics(const Graphics&) = delete;
	~Graphics();
	void Begin(float r, float g, float b);
	void End();

public:
	ID2D1HwndRenderTarget* pRenderTarget = nullptr;
};
