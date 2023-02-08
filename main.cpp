#define OLC_PGE_APPLICATION
#include "include/olcPixelGameEngine.h"

#include "include/particle.h"
#include "include/trailmap.h"
#include "include/utils.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

class Physarum : public olc::PixelGameEngine
{
public:
	Physarum()
	{
		sAppName = "Physarum Mold Simulation";
	}
public:
	// GLOBAL VARIABLES
	int pixel_width = 1;
	int mold_number = 120;
	int speed = 10;
	
	TrailMap trailmap;
	Particle molds[120];

	bool isPause = false;
public:
	bool OnUserCreate() override
	{
		// SPAWN ALL PARTICLES
		for (int i = 0; i < mold_number; i++)
		{
			molds[i].x = ScreenWidth() / 2;
			molds[i].y = ScreenHeight() / 2;
			molds[i].rotation = i * 3;

			molds[i].speed = speed;
			molds[i].state = 1;

			molds[i].trailmap = &trailmap;

			molds[i].sensor_distance = 10;
			molds[i].sensor_angle = 45;
			molds[i].sensor_size = 4;
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// IF UNPAUSED
		if (isPause == false)
		{
			// CLEAR SCREEN EVERY FRAME
			Clear({0, 0, 0});

			// UPDATE PARTICLES
			for (int i = 0; i < mold_number - 1; i++)
			{	
				//molds[i].Sense(this);
				molds[i].Rotate(this);
				molds[i].Move(this);
				molds[i].Deposit(this);
				//molds[i].Draw(this);
			}

			// UPDATE TRAILMAP
			trailmap.Update(this);
		}

		// PAUSE SIMULATION
		if (GetKey(olc::Key::SPACE).bPressed)
		{
			if (isPause == false)
				isPause = true;
			else if (isPause == true)
				isPause = false;
		}

		return true;
	}
};

int main()
{
	Physarum simulation;
	if (simulation.Construct(1440, 1440, 2, 2))
		simulation.Start();
	return 0;
}
