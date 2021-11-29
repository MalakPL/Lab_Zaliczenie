#include "ScreenBuffer.h"
#include <Windows.h>

auto ScreenBuffer::Clear() -> void 
{
	memset(Buffer, 0, Width * Height * sizeof(CHAR_INFO));
}

auto ScreenBuffer::SetPoint(int X, int Y, const CHAR_INFO Char) -> void
{
	*(Buffer + (Y * Width) + X) = Char;
}

auto ScreenBuffer::SetText(int X, int Y, wstring Text, WORD Attribute) -> void
{
	for (int i = 0; i < Text.length(); i++)
	{
		CHAR_INFO Char{};
		Char.Char.UnicodeChar = Text[i];
		Char.Attributes = Attribute;

		*(Buffer + (Y * Width) + X + i) = Char;
	}
}

auto ScreenBuffer::SetRect(int X, int Y, int W, int H, WORD Attribute) -> void
{
	for (int i = 0; i < W; i++)
	{
		CHAR_INFO Char{};
		Char.Char.UnicodeChar = L'═';
		Char.Attributes = Attribute;

		*(Buffer + (Y * Width) + X + i) = Char;
		*(Buffer + ((Y+ H -1) * Width) + X + i) = Char;
	}

	for (int i = 0; i < H; i++)
	{
		CHAR_INFO Char{};
		Char.Char.UnicodeChar = L'║';
		Char.Attributes = Attribute;

		*(Buffer + ((Y + i) * Width) + X) = Char;
		*(Buffer + ((Y + i) * Width) + X + W - 1) = Char;
	}

	CHAR_INFO Char{};
	Char.Char.UnicodeChar = L'╔';
	Char.Attributes = Attribute;

	*(Buffer + (Y * Width) + X) = Char;

	Char.Char.UnicodeChar = L'╗';
	Char.Attributes = Attribute;

	*(Buffer + (Y * Width) + X + W - 1) = Char;

	Char.Char.UnicodeChar = L'╝';
	Char.Attributes = Attribute;

	*(Buffer + ((Y+H-1) * Width) + X + W - 1) = Char;

	Char.Char.UnicodeChar = L'╚';
	Char.Attributes = Attribute;

	*(Buffer + ((Y + H - 1) * Width) + X) = Char;


}