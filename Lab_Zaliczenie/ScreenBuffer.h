#pragma once
#include <string>

using std::string;

class ScreenBuffer
{
public:
	int Width;
	int Height;
	char* Buffer;

	ScreenBuffer(int Width, int Height)
	{
		this->Width = Width;
		this->Height = Height;

		this->Buffer = new char[Width * Height];
	}

	auto Clear() -> void;
	auto SetPoint(int X, int Y, const char Char) -> void;
	auto SetText(int X, int Y, string Text) -> void;
};

