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
	// todo
}

void Particle::Rotate(olc::PixelGameEngine* pge)
{
	// todo
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
	if (trails.size() >= 550)
	{
		for (int i = 0; i < abs(dx); i++)
		{
			trails.pop_back();
			trails.insert(trails.begin(), {x + ((dx / abs(dx)) * i), y, 255 - (i * 2)});

			if (x + ((dx / abs(dx)) * i) < 1280 && x + ((dx / abs(dx)) * i) > 0 && y > 0 && y < 720)
				trailmap->trails[x + ((dx / abs(dx)) * i)][y] = 255 - (i * 2);
		}

		for (int i = 0; i < abs(dy); i++)
		{
			trails.pop_back();
			trails.insert(trails.begin(), {x, y - ((dy / abs(dy)) * i), 255 - (i * 2)});

			if (x < 1280 && x > 0 && y - ((dy / abs(dy)) * i) > 0 && y - ((dy / abs(dy)) * i) < 720)
				trailmap->trails[x][y - ((dy / abs(dy)) * i)] = 255 - (i * 2);
		}
	}

	/***** IF MAX TRAILS REACHED *****/
	else if (trails.size() < 550)
	{
		for (int i = 0; i < abs(dx); i++)
		{
			trails.insert(trails.begin(), {x + ((dx / abs(dx)) * i), y, 255 - (i * 2)});

			trailmap->trails[x + ((dx / abs(dx)) * i)][y] = 255 - (i * 2);
		}

		for (int i = 0; i < abs(dy); i++)
		{
			trails.insert(trails.begin(), {x, y - ((dy / abs(dy)) * i), 255 - (i * 2)});

			if (x < 1280 && x > 0 && y - ((dy / abs(dy)) * i) > 0 && y - ((dy / abs(dy)) * i) < 720)
				trailmap->trails[x][y - ((dy / abs(dy)) * i)] = 255 - (i * 2);
		}
	}
}

void Particle::Draw(olc::PixelGameEngine* pge)
{
	for (int i = 0; i < trails.size(); i++)
	{
		if (trails[i][2] > 0)
			trails[i][2] -= 2;
	}

	for (int i = 0; i < trails.size(); i++)
	{
		pge->FillRect(trails[i][0], trails[i][1], 1, 1, {trails[i][2], trails[i][2], trails[i][2]});
	}
}