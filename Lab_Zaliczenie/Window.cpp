#include "Window.h"

/* Klasa okna konsoli */

HANDLE Window::Handle = nullptr;
auto Window::Init(const wchar_t* Title) -> void
{
	SetConsoleTitleW(Title);

	Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleActiveScreenBuffer(Handle);
}

auto Window::SetSize(int W, int H) -> void
{

}

auto Window::CursorVisible(bool Visible) -> void
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(Handle, &cursorInfo);
	cursorInfo.bVisible = Visible;
	SetConsoleCursorInfo(Handle, &cursorInfo);
}

auto Window::Render(ScreenBuffer& Screen) -> void
{
	SMALL_RECT srcWriteRect;
	srcWriteRect.Top = 0;
	srcWriteRect.Left = 0;
	srcWriteRect.Bottom = Screen.Height;
	srcWriteRect.Right = Screen.Width;

	WriteConsoleOutputW(Handle, Screen.Buffer, { (short)Screen.Width, (short)Screen.Height }, { 0, 0 }, &srcWriteRect);
}

auto Window::isActive() -> bool
{
	return GetConsoleWindow() == GetForegroundWindow();
}