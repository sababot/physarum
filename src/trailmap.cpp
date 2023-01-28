#include "../include/trailmap.h"

#include "../include/olcPixelGameEngine.h"

/*
void TrailMap::Draw(olc::PixelGameEngine* pge)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (trails[i][j] != NULL && trails[i][j] != 0)
				pge->FillRect(i, j, 1, 1, {trails[i][j], trails[i][j], trails[i][j]});
			if (i != 0 && j != 0 && i != pge->ScreenWidth() && j != pge->ScreenHeight())
			{
				for (int f = 0; f < 8; f++)
				{
					trails[i][j] = (
						(trails[i + 1][j]) + (trails[i - 1][j]) + 
						(trails[i][j + 1]) + (trails[i][j - 1]) + 
						(trails[i + 1][j + 1]) + (trails[i + 1][j - 1]) + 
						(trails[i - 1][j + 1]) + (trails[i - 1][j - 1])
						) / 8;
				}
			}
		}
	}
}
*/