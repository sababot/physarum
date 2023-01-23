#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <array>

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
	int mold_number = 60;
	int molds[60][3];
	int mold_targets[60][2];
	int speed = 10;
	int max_count = 10;
	int count = max_count;
public:
	bool OnUserCreate() override
	{
		for (int i = 0; i < 60; i++)
		{
			molds[i][0] = ScreenWidth() / 2;	
			molds[i][1] = ScreenHeight() / 2;	
			molds[i][2] = i * 6;
			molds[i][3] = 0;

			mold_targets[i][0] = ScreenWidth() / 2;
			mold_targets[i][1] = ScreenHeight() / 2;
		}
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Clear({0, 0, 0});
		
		for (int i = 0; i < mold_number - 1; i++)
		{
			FillRect(molds[i][0], molds[i][1], pixel_width, pixel_width, {225, 225, 225});
		}

		if (count == 0){
			for (int i = 0; i < mold_number - 1; i++)
			{
				// MOVE
				if (molds[i][0] == mold_targets[i][0] && molds[i][1] == mold_targets[i][1])
				{
					int rotation = molds[i][2];
					float dx = sin(rotation * (M_PI / 180)) * speed;
						float dy = cos(rotation * (M_PI / 180)) * speed;

					mold_targets[i][0] = molds[i][0] + dx;
					mold_targets[i][1] = molds[i][1] + dy;
				}

				else
				{
					int dx = mold_targets[i][0] - molds[i][0];
					int dy = mold_targets[i][1] - molds[i][1];

					if (dx != 0)
					{
						if (dx < 0)
							molds[i][0] -= 1;	
						else if (dx > 0)
							molds[i][0] += 1;
					}

					if (dy != 0)
					{
						if (dy < 0)
							molds[i][1] -= 1;
						else if (dy > 0)
							molds[i][1] += 1;
					}
				}

				// BOUNDARIES
				if (molds[i][0] <= 1)
				{
					molds[i][2] = rand() % 180;
				}

				else if (molds[i][0] >= ScreenWidth())
				{
					molds[i][2] = rand() % 180 + 180; 
				}
				
				else if (molds[i][1] >= ScreenHeight())
				{
					molds[i][2] = rand() % 180 + 90;
				}

				else if (molds[i][1] <= 1)
				{
					int choose = rand() % 2 + 1;
					
					if (choose == 1)
						molds[i][2] = rand() % 90;
					if (choose == 2)
						molds[i][2] = rand() % 90 + 270;
				}

			}

			count = max_count;
		}

		else
			count -= 1;

		return true;
	}
};

int main()
{
	Physarum simulation;
	if (simulation.Construct(640, 380, 2, 2))
		simulation.Start();
	return 0;
}
