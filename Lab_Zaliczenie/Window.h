#pragma once
#include <Windows.h>
#include "ScreenBuffer.h"

class Window
{
public:
	static HANDLE Handle;

	static auto Init(const wchar_t* Title) -> void;

	static auto CursorVisible(bool) -> void;
	static auto Render(ScreenBuffer&) -> void;
	static auto isActive() -> bool;
	static auto SetSize(int W, int H) -> void;
};

