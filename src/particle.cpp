#include "../include/particle.h"
#include "../include/olcPixelGameEngine.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>

void Particle::Move(olc::PixelGameEngine* pge)
{
	// MOVE
	if (x == target_x && y == target_y)
	{
		dx = sin(rotation * (M_PI / 180)) * speed;
		dy = cos(rotation * (M_PI / 180)) * speed;

		target_x = x + dx;
		target_y = y + dy;

		rotation += rand() % 60 - 30;
	}

	else
	{
		x += dx;
		y += dy;

		if (trails.size() >= 550)
		{
			for (int i = 0; i < abs(dx); i++)
			{
				trails.pop_back();
				trails.insert(trails.begin(), {x + ((dx / abs(dx)) * i), y, (i * 2)});
			}

			for (int i = 0; i < abs(dy); i++)
			{
				trails.pop_back();
				trails.insert(trails.begin(), {x, y - ((dy / abs(dy)) * i), (i * 2)});
			}
		}

		else if (trails.size() < 550)
		{
			for (int i = 0; i < abs(dx); i++)
			{
				trails.insert(trails.begin(), {x + ((dx / abs(dx)) * i), y, (i * 2)});
			}

			for (int i = 0; i < abs(dy); i++)
			{
				trails.insert(trails.begin(), {x, y - ((dy / abs(dy)) * i), (i * 2)});
			}
		}
	}

	// BOUNDARIES
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

void Particle::Draw(olc::PixelGameEngine* pge)
{
	for (int i = 0; i < trails.size(); i++)
	{
		if (trails[i][2] < 255)
			trails[i][2] += 2;
	}

	for (int i = 0; i < trails.size(); i++)
	{
		pge->FillRect(trails[i][0], trails[i][1], 1, 1, {trails[i][2], 255, trails[i][2]});
	}

	pge->FillRect(x, y, 1, 1, {255, 255, 255});
}