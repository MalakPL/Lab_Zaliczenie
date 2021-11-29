#include "ScreenBuffer.h"
#include <Windows.h>

auto ScreenBuffer::Clear() -> void 
{
	memset(Buffer, 32, Width * Height);
}

auto ScreenBuffer::SetPoint(int X, int Y, const char Char) -> void
{
	*(Buffer + (Y * Width) + X) = Char;
}

auto ScreenBuffer::SetText(int X, int Y, string Text) -> void
{
	for (int i = 0; i < Text.length(); i++)
	{
		*(Buffer + (Y * Width) + X + i) = Text[i];
	}
}