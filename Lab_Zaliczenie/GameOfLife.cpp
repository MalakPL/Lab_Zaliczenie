#include "GameOfLife.h"
#include <Windows.h>

GameOfLife::GameOfLife(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;
	this->Grid = new bool[Width * Height];
	this->TempGrid = new bool[Width * Height];

	memset(Grid, false, Width * Height);
	memset(TempGrid, false, Width * Height);
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

auto GameOfLife::Update() -> void {
	if (GetAsyncKeyState((int)'R') == -32767)
	{
		RandomGrid();
	}

	memset(TempGrid, false, Width * Height);

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

			if (!GetState(X, Y) && (aliveNeighbours == 3))
				TempGrid[Y * Width + X] = true;
			else if (GetState(X, Y) && (aliveNeighbours == 2 || aliveNeighbours == 3))
				TempGrid[Y * Width + X] = true;
			else if (GetState(X, Y))
				TempGrid[Y * Width + X] = false;
		}
	}

	memcpy(Grid, TempGrid, Width * Height);
}

auto GameOfLife::Render(ScreenBuffer& ScreenBuffer) -> void
{
	for (int X = 1; X < Width - 1; X++)
	{
		for (int Y = 1; Y < Height - 1; Y++)
		{
			if (GetState(X, Y))
			{
				ScreenBuffer.SetPoint(X, Y, '*');
			}
		}
	}
}