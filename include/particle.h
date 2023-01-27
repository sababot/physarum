#pragma once

#include "olcPixelGameEngine.h"

#include <vector>
#include <array>

using namespace std;

class Particle : public olc::PixelGameEngine
{
public:
	int x;
	int y;
	int rotation;
	int speed;

	int dx;
	int dy;
	int target_x;
	int target_y;

	vector <array<int, 3>> trails;

	void Move(olc::PixelGameEngine* pge);
	void Draw(olc::PixelGameEngine* pge);
};