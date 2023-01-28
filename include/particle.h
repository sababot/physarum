#pragma once

#include "olcPixelGameEngine.h"
#include "trailmap.h"

#include <vector>
#include <array>

using namespace std;

class Particle
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

	TrailMap* trailmap;

	vector <array<int, 3>> trails;

	void Move(olc::PixelGameEngine*);
	void Draw(olc::PixelGameEngine*);
};