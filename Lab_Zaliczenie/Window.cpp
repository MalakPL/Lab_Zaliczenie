#include "Window.h"

HANDLE Window::Handle = nullptr;
auto Window::Init() -> void
{
	SetConsoleTitleW(L"ANOVEI");

	Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	/*SMALL_RECT windowSize = {0, 0, 299, 49};
	SetConsoleWindowInfo(Handle, TRUE, &windowSize);

	COORD c = { 300, 50 };
	SetConsoleScreenBufferSize(Handle, c);

	/*PCOORD a = new COORD();
	a->X = 123;
	a->Y = 123;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, a);*/


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