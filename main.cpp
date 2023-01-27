#define OLC_PGE_APPLICATION
#include "include/olcPixelGameEngine.h"
#include "include/particle.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>

#include "include/utils.h"

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
	int mold_number = 750;
	//int molds[750][5];
	//int mold_targets[750][2];
	//vector <array<int, 3>> trails[750];
	int speed = 10;
	//int max_count = 0;
	//int count = max_count;
	
	Particle molds[750];

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
		}
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (isPause == false)
		{
			Clear({255, 255, 255});
			/*
			for (int i = 0; i < mold_number - 1; i++)
			{
				for (int j = 0; j < trails[i].size(); j++)
				{
					FillRect(trails[i][j][0], trails[i][j][1], pixel_width, pixel_width, {trails[i][j][2], trails[i][j][2], trails[i][j][2]});
				}

				FillRect(molds[i][0], molds[i][1], pixel_width, pixel_width, {225, 225, 225});
			}
			*/

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
	if (simulation.Construct(2560, 1440, 1, 1))
		simulation.Start();
	return 0;
}
