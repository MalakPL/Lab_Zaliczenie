#include "GameOfLife.h"
#include <Windows.h>
#include "Window.h"

GameOfLife::GameOfLife(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;
	this->Size = Width * Height;
	this->Grid = new bool[Size];
	this->TempGrid = new bool[Size];

	Clear();
}

auto GameOfLife::RandomGrid() -> void {
	for (int X = 1; X < Width - 1; X++)
	{
		for (int Y = 1; Y < Height - 1; Y++)
		{
			SetState(X, Y, (rand() % 4) == 2);
		}
	}
}

auto GameOfLife::GetState(int X, int Y) -> bool {
	return Grid[Y * Width + X];
}

auto GameOfLife::SetState(int X, int Y, bool State) -> void {
	Grid[Y * Width + X] = State;
}

/* Logika */
auto GameOfLife::Update() -> void 
{
	if (isPaused) { return; }

	if (Window::isActive())
	{
		if (GetAsyncKeyState((int)'R') == -32767)
		{
			RandomGrid();
		}
	}

	/* Czyszczenie tymczsowego grida */
	memset(TempGrid, false, Size);

	for (int X = 1; X < Width - 1; X++)
	{
		for (int Y = 1; Y < Height - 1; Y++)
		{
			int aliveNeighbours = 0;

			for (int X1 = -1; X1 <= 1; X1++)
			{
				for (int Y1 = -1; Y1 <= 1; Y1++)
				{
					aliveNeighbours += GetState(X + X1, Y + Y1);
				}
			}

			aliveNeighbours -= GetState(X, Y);

			/* https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie */

			if (!GetState(X, Y) && (aliveNeighbours == 3))
				TempGrid[Y * Width + X] = true;
			else if (GetState(X, Y) && (aliveNeighbours == 2 || aliveNeighbours == 3))
				TempGrid[Y * Width + X] = true;
			else if (GetState(X, Y))
				TempGrid[Y * Width + X] = false;
		}
	}

	/* Czyszczenie grida */
	memcpy(Grid, TempGrid, Size);
}

auto GameOfLife::Render(ScreenBuffer& ScreenBuffer) -> void
{
	for (int X = 1; X < Width - 1; X++)
	{
		for (int Y = 1; Y < Height - 1; Y++)
		{
			if (GetState(X, Y))
			{
				CHAR_INFO Char;
				Char.Char.UnicodeChar = '*';
				Char.Attributes = isPaused ? 8 : 15;

				ScreenBuffer.SetPoint(X, Y, Char);
			}
		}
	}
}

auto GameOfLife::Clear() -> void {
	memset(Grid, false, Size);
	memset(TempGrid, false, Size);
}