#include "../include/particle.h"
#include "../include/trailmap.h"
#include "../include/olcPixelGameEngine.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>

void Particle::Sense(olc::PixelGameEngine* pge)
{
	bool right = false;
	bool left = false;

	// SENSE
	if ((x < pge->ScreenWidth() - sensor_distance) && (x > sensor_distance && y < pge->ScreenHeight() - sensor_distance && y > sensor_distance))
	if (trailmap->trails[(int)(x + (cos((rotation + sensor_angle) * (M_PI / 180)) * sensor_distance))][(int)(y + (sin((rotation + sensor_angle) * (M_PI / 180)) * sensor_distance))] > 100)
		right = true;

	else if (trailmap->trails[(int)(x + (cos((rotation - sensor_angle) * (M_PI / 180)) * sensor_distance))][(int)(y + (sin((rotation - sensor_angle) * (M_PI / 180)) * sensor_distance))] > 100)
		left = true;

	else
	{
		left = false; 
		right = false;
	}

	// DECIDE STATE
	if (!right && !left)
		state = 1;

	else if (right && left)
		state = 2;

	else if (!right && left)
		state = 3;

	else if (right && !left)
		state = 4;
}

void Particle::Rotate(olc::PixelGameEngine* pge)
{
	// if state = 1; do nothing

	if (state == 2)
	{
		rotation += rand() % 60 - 30;
	}

	else if (state == 3)
	{
		rotation += 25;
	}

	else if (state == 4)
	{
		rotation -= 25;
	}
}

void Particle::Move(olc::PixelGameEngine* pge)
{
	/***** MOVE *****/
	dx = sin(rotation * (M_PI / 180)) * speed;
	dy = cos(rotation * (M_PI / 180)) * speed;

	x += dx;
	y += dy;

	/***** BOUNDARIES *****/
	if (x <= 1)
	{
		rotation = rand() % 180;
	}

	else if (x >= pge->ScreenWidth())
	{
		rotation = rand() % 180 + 180;
	}
					
	else if (y >= pge->ScreenHeight())
	{
		rotation = rand() % 180 + 90;
	}

	else if (y <= 1)
	{
		int choose = rand() % 2 + 1;
						
		if (choose == 1)
			rotation = rand() % 90;
		if (choose == 2)
			rotation = rand() % 90 + 270;
	}
}

void Particle::Deposit(olc::PixelGameEngine* pge)
{
	/***** IF MAX TRAILS NOT REACHED *****/
	for (int i = 0; i < abs(dx); i++)
	{
		if (x + ((dx / abs(dx)) * i) < pge->ScreenWidth() && x + ((dx / abs(dx)) * i) > 0 && y > 0 && y < pge->ScreenHeight())
			trailmap->trails[x + ((dx / abs(dx)) * i)][y] = 255 - (i * 2);
	}

	for (int i = 0; i < abs(dy); i++)
	{
		if (x < pge->ScreenWidth() && x > 0 && y - ((dy / abs(dy)) * i) > 0 && y - ((dy / abs(dy)) * i) < pge->ScreenHeight())
			trailmap->trails[x][y - ((dy / abs(dy)) * i)] = 255 - (i * 2);
	}
}

void Particle::Draw(olc::PixelGameEngine* pge)
{
	//
}