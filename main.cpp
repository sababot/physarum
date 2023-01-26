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
	int mold_number = 750;
	int molds[750][5];
	int mold_targets[750][2];
	vector <array<int, 3>> trails[750];
	int speed = 10;
	int max_count = 0;
	int count = max_count;
	bool isPause = false;
public:
	bool OnUserCreate() override
	{
		for (int i = 0; i < mold_number; i++)
		{
			molds[i][0] = ScreenWidth() / 2;	
			molds[i][1] = ScreenHeight() / 2;	
			molds[i][2] = i * 3;
			molds[i][3] = 0;

			mold_targets[i][0] = ScreenWidth() / 2;
			mold_targets[i][1] = ScreenHeight() / 2;
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
				if (count == 0)
				{
					// MOVE //
					if (molds[i][0] == mold_targets[i][0] && molds[i][1] == mold_targets[i][1])
					{
						int rotation = molds[i][2];
						int dx = sin(rotation * (M_PI / 180)) * speed;
						int dy = cos(rotation * (M_PI / 180)) * speed;

						mold_targets[i][0] = molds[i][0] + dx;
						mold_targets[i][1] = molds[i][1] + dy;

						molds[i][3] = dx;
						molds[i][4] = dy;

						molds[i][2] += rand() % 30 - 15;
					}

					else
					{
						int dx = molds[i][3];
						int dy = molds[i][4];
						/*
						int mod_dx = dx;
						int mod_dy = dy;
						int rotation = molds[i][2];

						if (abs(dx) < abs(dy))
							mod_dy = 1;
						else if (abs(dx) > abs(dy))
							mod_dx = 1;

						if ((sin(rotation * (M_PI / 180)) > 0 && mod_dx < 0) || (sin(rotation * (M_PI / 180)) < 0 && mod_dx > 0))
							mod_dx *= -1;

						if ((cos(rotation * (M_PI / 180)) > 0 && mod_dy < 0) || (cos(rotation * (M_PI / 180)) < 0 && mod_dy > 0))
							mod_dy *= -1;
						*/

						molds[i][0] += dx;
						molds[i][1] += dy;

							if (trails[i].size() >= 630)
							{
								for (int j = 0; j < abs(dx); j++)
								{
									trails[i].pop_back();
									trails[i].insert(trails[i].begin(), {molds[i][0] + ((dx / abs(dx)) * j), molds[i][1], j});
								}

								for (int j = 0; j < abs(dy); j++)
								{
									trails[i].pop_back();
									trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1] - ((dy / abs(dy)) * j), j});
								}
							}

							else if (trails[i].size() < 630)
							{
								for (int j = 0; j < abs(dx); j++)
								{
									trails[i].insert(trails[i].begin(), {molds[i][0] + ((dx / abs(dx)) * j), molds[i][1], j});
								}

								for (int j = 0; j < abs(dy); j++)
								{
									trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1] - ((dy / abs(dy)) * j), j});
								}
							}

						//}
						/*
						int dx = mold_targets[i][0] - molds[i][0];
						int dy = mold_targets[i][1] - molds[i][1];

						if (dx != 0)
						{
							if (dx < 0)
								molds[i][0] += dx;
							else if (dx > 0)
								molds[i][0] += dx;
						}

						if (dy != 0)
						{
							if (dy < 0)
								molds[i][1] += dy;
							else if (dy > 0)
								molds[i][1] += dy;
						}
						*/
					}

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
					/*if (trails[i].size() < 200)
					{
						trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1], 250});
					}

					else if (trails[i].size() >= 200)
					{
						trails[i].pop_back();
						trails[i].insert(trails[i].begin(), {molds[i][0], molds[i][1], 250});
					}
*/
					//for (int j = 0; j < trails[i].size(); j++)
					//{
					//	trails[i][j][2] -= 1;
					//}

					count = max_count;
				}

				else
					count -= 1;

				// DRAW
				for (int j = 0; j < trails[i].size(); j++)
				{
					if (trails[i][j][2] < 255)
						trails[i][j][2] += 2;
				}

				for (int j = 0; j < trails[i].size(); j++)
				{
					FillRect(trails[i][j][0], trails[i][j][1], pixel_width, pixel_width, {trails[i][j][2], trails[i][j][2], trails[i][j][2]});
				}

				FillRect(molds[i][0], molds[i][1], pixel_width, pixel_width, {225, 0, 225});

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
