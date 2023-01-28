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
	int pixel_width = 1;
	int mold_number = 250;
	//int molds[750][5];
	//int mold_targets[750][2];
	//vector <array<int, 3>> trails[750];
	int speed = 10;
	//int max_count = 0;
	//int count = max_count;
	
	TrailMap trailmap;

	Particle molds[250];

	bool isPause = false;
public:
	bool OnUserCreate() override
	{
		for (int i = 0; i < mold_number; i++)
		{
			molds[i].x = ScreenWidth() / 2;	
			molds[i].y = ScreenHeight() / 2;	
			molds[i].rotation = i * 3;

			molds[i].speed = speed;

			molds[i].target_x = ScreenWidth() / 2;
			molds[i].target_y = ScreenHeight() / 2;

			molds[i].trailmap = &trailmap;
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (isPause == false)
		{
			Clear({0, 0, 0});

			for (int i = 0; i < mold_number - 1; i++)
			{	
				molds[i].Move(this);
				molds[i].Draw(this);
			}
		}

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
	if (simulation.Construct(1280, 720, 1, 1))
		simulation.Start();
	return 0;
}
