#pragma once
#include "Lsys.h"
#include "GFX2D.h"



class Game : protected Lsys, protected GFX2D
{
protected:
	int Maze_alpha = 90;

	void MouseX(UINT button, UINT state, int x, int y);

	void Maze(int depth);


	void DrawMaze();

	void TextureLoader();
};

