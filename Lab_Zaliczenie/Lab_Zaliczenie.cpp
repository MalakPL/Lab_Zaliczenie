#include <iostream>
#include <Windows.h>
#include <string>
#include "GameOfLife.h"
#include "ScreenBuffer.h"
#include "Window.h"

#include <io.h>
#include <fcntl.h>

void Update();
void Render();

//Render info
const int FPS = 60;
const int SleepDelta = 1000 / FPS;
const double EpsaledDeltaTime = 1.0 / FPS;
double EpsaledTime = 0;

ScreenBuffer Screen{ 120 , 30 };//120x30 240x67
GameOfLife Game{ 120,22 };

int CursorX = 120 / 2;
int CursorY = 30 / 2;

auto main() -> int
{
	if (_setmode(_fileno(stdout), _O_U8TEXT) == -1)
	{
		throw std::exception{ "Nie mozna ustawic kodowania UTF-8" };
	}

	Window::Init();
	Window::CursorVisible(false);

	Game.RandomGrid();

	while (true)
	{
		Update();
		Render();

		/* Wyświetlamy wyrenderowaną klatkę na konsoli */
		Window::Render(Screen);

		Sleep(SleepDelta);
		EpsaledTime += EpsaledDeltaTime;
	}
}

void Update()
{
	if (Window::isActive())
	{
		if (GetAsyncKeyState(VK_LEFT) == -32767)
		{
			CursorX--;
		}

		if (GetAsyncKeyState(VK_RIGHT) == -32767)
		{
			CursorX++;
		}

		if (GetAsyncKeyState(VK_UP) == -32767)
		{
			CursorY--;
		}

		if (GetAsyncKeyState(VK_DOWN) == -32767)
		{
			CursorY++;
		}

		if (CursorX > Game.Width - 2)
		{
			CursorX = Game.Width - 2;
		}

		if (CursorX < 1)
		{
			CursorX = 1;
		}

		if (CursorY > Game.Height - 2)
		{
			CursorY = Game.Height - 2;
		}

		if (CursorY < 1)
		{
			CursorY = 1;
		}

		if (GetAsyncKeyState(VK_SPACE) == -32767)
		{
			Game.SetState(CursorX, CursorY, !Game.GetState(CursorX, CursorY));
		}

		if (GetAsyncKeyState((int)'P') == -32767)
		{
			Game.isPaused = !Game.isPaused;
		}

		if (GetAsyncKeyState((int)'C') == -32767)
		{
			Game.Clear();
		}
	}

	Game.Update();
}

void Render()
{
	/* Czyścimy klatkę */
	Screen.Clear();

	Game.Render(Screen);

	Screen.SetText(49, Screen.Height - 7, L"Press C to clear", 11);
	Screen.SetText(49, Screen.Height - 6, L"Press R to random", 11);
	Screen.SetText(49, Screen.Height - 5, L"Press P to pause", 11);
	Screen.SetText(49, Screen.Height - 4, L"Press ←↑↓→ to move cursor", 11);
	Screen.SetText(49, Screen.Height - 3, L"Press Space to add object (in pause mode)", 11);
	Screen.SetText(49, Screen.Height - 2, L"Press [ ] to change object", 11);

	Screen.SetText(2, Screen.Height - 7, L" █████╗ ███╗  ██╗ █████╗ ██╗   ██╗███████╗██╗", 10);
	Screen.SetText(2, Screen.Height - 6, L"██╔══██╗████╗ ██║██╔══██╗██║   ██║██╔════╝██║", 10);
	Screen.SetText(2, Screen.Height - 5, L"███████║██╔██╗██║██║  ██║╚██╗ ██╔╝█████╗  ██║", 10);
	Screen.SetText(2, Screen.Height - 4, L"██╔══██║██║╚████║██║  ██║ ╚████╔╝ ██╔══╝  ██║", 10);
	Screen.SetText(2, Screen.Height - 3, L"██║  ██║██║ ╚███║╚█████╔╝  ╚██╔╝  ███████╗██║", 10);
	Screen.SetText(2, Screen.Height - 2, L"╚═╝  ╚═╝╚═╝  ╚══╝ ╚════╝    ╚═╝   ╚══════╝╚═╝", 10);

	Screen.SetRect(0, 0, 120, 22, 10);
	Screen.SetRect(120 - 13, 23, 12, 6, 11);

	Screen.SetText(48, 0, L"╣ Conway's Game of Life ╠", 10);

	if (Game.isPaused)
	{
		Screen.SetText(Game.Width - 7, Game.Height - 2, L"Pause", 12);
	}

	Screen.SetText(CursorX, CursorY, L"+", 13);
}
