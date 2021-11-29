#include <iostream>
#include <Windows.h>
#include <string>
#include "GameOfLife.h"
#include "ScreenBuffer.h"

void Update();
void Render();

//Render info
const int ScreenWidth = 120, ScreenHeight = 30; //120x30 240x67
const int GridWidth = 120, GridHeight = 26; //120x30 240x67
const int FPS = 30;
const int SleepDelta = 1000 / FPS;
const double EpsaledDeltaTime = 1.0 / FPS;
double EpsaledTime = 0;

ScreenBuffer Screen{ ScreenWidth , ScreenHeight };
GameOfLife Game{ GridWidth,GridHeight };

auto main() -> int
{
	SetConsoleTitle(L"ANOVEI");

	//ScreenBuffer
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//Disable cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);
	SetConsoleActiveScreenBuffer(console);

	Game.RandomGrid();

	DWORD bytesWritten = 0;

	while (true)
	{
		Update();
		Render();

		WriteConsoleOutputCharacterA(console, Screen.Buffer, ScreenWidth * ScreenHeight, { 0, 0 }, &bytesWritten);
		Sleep(SleepDelta);
		EpsaledTime += EpsaledDeltaTime;
	}
}

void Update()
{
	Game.Update();
}

void Render()
{
	Screen.Clear();
	Game.Render(Screen);

	Screen.SetText(0, ScreenHeight - 4, "+-----------------------+-------------------+");
	Screen.SetText(0, ScreenHeight - 3, "| Conway's Game of Life | Press R to random |");
	Screen.SetText(0, ScreenHeight - 2, "| Author: Karol Szmajda |                   |");
	Screen.SetText(0, ScreenHeight - 1, "+-----------------------+-------------------+");
}
