#pragma once

#include "olcPixelGameEngine.h"

class TrailMap
{
public:
	int width = 1440; // width of screen
	int height = 1440; // height of screen
	int trails[1440][1440]; // matrix containing intensity of all pixels

	//void Draw(olc::PixelGameEngine*);
};