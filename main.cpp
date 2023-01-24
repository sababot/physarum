#define OLC_PGE_APPLICATION
#include "include/olcPixelGameEngine.h"

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
	int mold_number = 500;
	int molds[500][3];
	int mold_targets[500][2];
	vector <array<int, 3>> trails[500];
	int speed = 100;
	int max_count = 500;
	int count = max_count;
public:
	bool OnUserCreate() override
	{
		for (int i = 0; i < 500; i++)
		{
			molds[i][0] = ScreenWidth() / 2;	
			molds[i][1] = ScreenHeight() / 2;	
			molds[i][2] = i;
			molds[i][3] = 0;

			mold_targets[i][0] = ScreenWidth() / 2;
			mold_targets[i][1] = ScreenHeight() / 2;
		}
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear({0, 0, 0});
		
		for (int i = 0; i < mold_number - 1; i++)
		{
			for (int j = 0; j < trails[i].size(); j++)
			{
				FillRect(trails[i][j][0], trails[i][j][1], pixel_width, pixel_width, {trails[i][j][2], trails[i][j][2], trails[i][j][2]});
			}

			FillRect(molds[i][0], molds[i][1], pixel_width, pixel_width, {225, 225, 225});
		}

		if (count == 0){
			for (int i = 0; i < mold_number - 1; i++)
			{
				// MOVE //
				//if (molds[i][0] == mold_targets[i][0] && molds[i][1] == mold_targets[i][1])
				//{
					int rotation = molds[i][2];
					int dx = sin(rotation * (M_PI / 180)) * speed;
					int dy = cos(rotation * (M_PI / 180)) * speed;

					/*if (dx > dy && dx != 0)
					{
						dy = dy / dx;
						dx = dx / dx;
					}

					else if (dy > dx && dy != 0)
					{
						dx = dx / dy;
						dy = dy / dy;
					}

					else if (dx == dy)
					{
						dx = dx / dx;
						dy = dy / dy;
					}
*/
					//mold_targets[i][0] = molds[i][0] + dx;
					//mold_targets[i][1] = molds[i][1] + dy;
					molds[i][0] += dx;
					molds[i][1] += dy;
				/*}

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
*/
				// BOUNDARIES //
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

				// TRAILS //
				if (trails[i].size() < 110)
				{
					trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1], 250});
				}

				else if (trails[i].size() >= 110)
				{
					trails[i].pop_back();
					trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1], 250});
				}

				for (int j = 0; j < trails[i].size(); j++)
				{
					trails[i][j][2] -= 2;
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
	if (simulation.Construct(640, 360, 2, 2))
		simulation.Start();
	return 0;
}
