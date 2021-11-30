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

/* Parametry renderowania */
const int FPS = 60;
const int SleepDelta = 1000 / FPS;
const double EpsaledDeltaTime = 1.0 / FPS;
double EpsaledTime = 0;

ScreenBuffer Screen{ 120 , 30 };
GameOfLife Game{ 120, 22 };

int CursorX = 120 / 2;
int CursorY = 22 / 2;

auto main() -> int
{
	if (_setmode(_fileno(stdout), _O_U8TEXT) == -1)
	{
		throw std::exception{ "Nie mozna ustawic kodowania UTF-8" };
	}

	Window::Init(L"ANOVEI - Game Of Life");
	Window::CursorVisible(false);

	Game.RandomGrid();

	while (true)
	{
		Update();
		Render();

		/* Wyświetlamy wyrenderowaną klatkę na konsoli */
		Window::Render(Screen);

		/* Kontroler max FPS */
		Sleep(SleepDelta);
		EpsaledTime += EpsaledDeltaTime;
	}
}

/* Logika */
void Update()
{
	/* Nasłuchujemy klawiszy przy aktywnym oknie konsoli */
	if (Window::isActive())
	{
		/* Klawisz do resetowania sceny */
		if (GetAsyncKeyState((int)'C') == -32767)
		{
			Game.Clear();
		}

		/* Klawisz do pauzowania sceny */
		if (GetAsyncKeyState((int)'P') == -32767)
		{
			Game.isPaused = !Game.isPaused;
		}

		if (Game.isPaused)
		{
			/* Zmiana punktu na scenie */
			if (GetAsyncKeyState(VK_SPACE) == -32767)
			{
				Game.SetState(CursorX, CursorY, !Game.GetState(CursorX, CursorY));
			}

			/* Klawisz do poruszania kursorem */
			if (GetAsyncKeyState(VK_LEFT) == -32767)
			{
				CursorX--;
			}

			/* Klawisz do poruszania kursorem */
			if (GetAsyncKeyState(VK_RIGHT) == -32767)
			{
				CursorX++;
			}

			/* Klawisz do poruszania kursorem */
			if (GetAsyncKeyState(VK_UP) == -32767)
			{
				CursorY--;
			}

			/* Klawisz do poruszania kursorem */
			if (GetAsyncKeyState(VK_DOWN) == -32767)
			{
				CursorY++;
			}

			/* Bezpieczna strefa kursora */
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
		}
	}

	Game.Update();
}

/* Rysowanie */
void Render()
{
	/* Czyścimy klatkę */
	Screen.Clear();

	/* Renderujemy Game Of Life */
	Game.Render(Screen);

	/* Renderujemy GUI */
	Screen.SetText(2, Screen.Height - 7, L"Press C to clear", 10);
	Screen.SetText(2, Screen.Height - 6, L"Press R to random", Game.isPaused ? 8 : 10);
	Screen.SetText(2, Screen.Height - 5, L"Press P to pause", 10);
	Screen.SetText(2, Screen.Height - 4, L"Press ←↑↓→ to move cursor (in pause mode)", Game.isPaused ? 10 : 8);
	Screen.SetText(2, Screen.Height - 3, L"Press Space to add object (in pause mode)", Game.isPaused ? 10 : 8);
	Screen.SetText(2, Screen.Height - 2, L"Author: Karol Szmajda", 4);


	Screen.SetText(54, Screen.Height - 7, L" █████╗ ███╗  ██╗ █████╗ ██╗   ██╗███████╗██╗   ██████╗ ██╗     ", 10);
	Screen.SetText(54, Screen.Height - 6, L"██╔══██╗████╗ ██║██╔══██╗██║   ██║██╔════╝██║   ██╔══██╗██║     ", 10);
	Screen.SetText(54, Screen.Height - 5, L"███████║██╔██╗██║██║  ██║╚██╗ ██╔╝█████╗  ██║   ██████╔╝██║     ", 10);
	Screen.SetText(54, Screen.Height - 4, L"██╔══██║██║╚████║██║  ██║ ╚████╔╝ ██╔══╝  ██║   ██╔═══╝ ██║     ", 10);
	Screen.SetText(54, Screen.Height - 3, L"██║  ██║██║ ╚███║╚█████╔╝  ╚██╔╝  ███████╗██║██╗██║     ███████╗", 10);
	Screen.SetText(54, Screen.Height - 2, L"╚═╝  ╚═╝╚═╝  ╚══╝ ╚════╝    ╚═╝   ╚══════╝╚═╝╚═╝╚═╝     ╚══════╝", 10);

	Screen.SetRect(0, 0, 120, 22, 10);
	Screen.SetText(45, 0, L"╣ Conway's Game of Life ╠", 10);

	if (Game.isPaused)
	{
		Screen.SetText(Game.Width - 32, Game.Height - 2, L"Game paused, press P to resume", 1 + (int)(EpsaledTime * 12) % 15); /* Tęczowy efekt */
		Screen.SetPoint(CursorX, CursorY, 80);
	}
}
