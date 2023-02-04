#include "../include/trailmap.h"

#include "../include/olcPixelGameEngine.h"

void TrailMap::Update(olc::PixelGameEngine* pge)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (trails[i][j] != NULL && trails[i][j] > 2)
			{
				pge->FillRect(i, j, 1, 1, {trails[i][j], trails[i][j], trails[i][j]});
				trails[i][j] -= 2;
			}
		}
	}
}