#pragma once
#include <string>
#include "ScreenBuffer.h"

using std::string;

class GameOfLife
{
private:
	bool* Grid;
	bool* TempGrid;
	int Width;
	int Height;

public:
	GameOfLife(int Width, int Height);

	auto RandomGrid() -> void;
	auto GetState(int X, int Y) -> bool;
	auto SetState(int X, int Y, bool State) -> void;
	auto Update() -> void;
	auto Render(ScreenBuffer&) -> void;
};

