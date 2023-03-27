#pragma once
#include <Windows.h>
#include <string>

class Window
{
public:
	Window(int x, int y, std::string name);
	Window(const Window&) = delete;
	~Window();

private:
	static LRESULT CALLBACK myWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	HWND hwnd;
	int crWidth;
	int crHeight;
};

