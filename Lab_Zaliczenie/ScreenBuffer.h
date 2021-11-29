#pragma once
#include <string>
#include <Windows.h>

using std::wstring;

class ScreenBuffer
{
public:
	int Width;
	int Height;
	CHAR_INFO* Buffer = nullptr;

	ScreenBuffer(int Width, int Height)
	{
		this->Width = Width;
		this->Height = Height;

		this->Buffer = new CHAR_INFO[Width * Height];
	}

	auto Clear() -> void;
	auto SetPoint(int X, int Y, const CHAR_INFO Char) -> void;
	auto SetText(int X, int Y, wstring Text, WORD Attribute) -> void;
	auto SetRect(int X, int Y, int W, int H, WORD Attribute) -> void;

	bool a[6][12];
};

