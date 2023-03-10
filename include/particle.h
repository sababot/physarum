#pragma once

#include "olcPixelGameEngine.h"
#include "trailmap.h"

#include <vector>
#include <array>

using namespace std;

class Particle
{
public:
	int x; // particle x position
	int y; // particle y position
	int target_x;
	int target_y;
	bool reach_target = false;
	int rotation; // particle orientation/rotation
	int speed; // particle speed

	int dx; // change in x
	int dy; // change in y

	int sensor_angle;
	int sensor_distance;
	int sensor_size;
	int state; // 1 - no change; 2 - random; 3 - right; 4 - left

	TrailMap* trailmap; // trailmap to store pheremones

	vector <array<int, 3>> trails; // temporary trails to display (aesthetic purpose)

	void Sense(olc::PixelGameEngine*); // sense pheremones and decide state
	void Rotate(olc::PixelGameEngine*); // rotate based on current state
	void Move(olc::PixelGameEngine*); // move particle
	void Deposit(olc::PixelGameEngine*); // deposit pheremones to attract other particles

	void Draw(olc::PixelGameEngine*); // draw particles
};