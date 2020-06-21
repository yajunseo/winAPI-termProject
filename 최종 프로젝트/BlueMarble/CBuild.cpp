#include "CBuild.h"

void CBuild::setRC(int l, int t, int r, int b)
{
	left = l; top = t; right = r; bottom = b;
	float boardWidth = (right - left - 200) / 10;
	float boardHeight = (bottom - top - 200) / 10;

	for (int i = 0; i < 10; i++)
	{
		villaPos[i][0] = right - 140 - boardWidth * (i);
		villaPos[i][1] = bottom - 130;
		buildingPos[i][0] = right - 120 - boardWidth * (i);
		buildingPos[i][1] = bottom - 130;
		HotelPos[i][0] = right - 95 - boardWidth * (i);
		HotelPos[i][1] = bottom - 130;
	}
	for (int i = 10; i < 20; i++)
	{
		villaPos[i][0] = left + 110;
		villaPos[i][1] = bottom - 135 - boardHeight * (i - 10);
		buildingPos[i][0] = left + 110;
		buildingPos[i][1] = bottom - 115 - boardHeight * (i - 10);
		HotelPos[i][0] = left + 110;
		HotelPos[i][1] = bottom - 90 - boardHeight * (i - 10);
	}
	for (int i = 20; i < 30; i++)
	{
		villaPos[i][0] = left + 70 + boardWidth * (i - 20);
		villaPos[i][1] = top + 110;
		buildingPos[i][0] = left + 90 + boardWidth * (i - 20);
		buildingPos[i][1] = top + 110;
		HotelPos[i][0] = left + 115 + boardWidth * (i - 20);
		HotelPos[i][1] = top + 110;
	}
	for (int i = 30; i < 40; i++)
	{
		villaPos[i][0] = right - 133;
		villaPos[i][1] = top + 65 + boardHeight * (i - 30);
		buildingPos[i][0] = right - 133;
		buildingPos[i][1] = top + 85 + boardHeight * (i - 30);
		HotelPos[i][0] = right - 133;
		HotelPos[i][1] = top + 110 + boardHeight * (i - 30);
	}
}

CBuild::CBuild()
{
	for (int i = 0; i < 10; i++)
	{
		if (i != 0 && i != 2 && i != 7)
		{
			arr[i][0] = 600;
			arr[i][1] = 1000;
			arr[i][2] = 1400;
			arr[i][3] = 1800;
		}

		else
		{
			arr[i][0] = 0;
			arr[i][1] = 0;
			arr[i][2] = 0;
			arr[i][3] = 0;
		}
	}

	for (int i = 10; i < 20; i++)
	{
		if (i != 10 && i != 12 && i != 17)
		{
			arr[i][0] = 1400;
			arr[i][1] = 1800;
			arr[i][2] = 2200;
			arr[i][3] = 2600;
		}

		else
		{
			arr[i][0] = 0;
			arr[i][1] = 0;
			arr[i][2] = 0;
			arr[i][3] = 0;
		}
	}

	for (int i = 20; i < 30; i++)
	{
		if (i != 20 && i != 22)
		{
			arr[i][0] = 2200;
			arr[i][1] = 2600;
			arr[i][2] = 3000;
			arr[i][3] = 3400;
		}

		else
		{
			arr[i][0] = 0;
			arr[i][1] = 0;
			arr[i][2] = 0;
			arr[i][3] = 0;
		}
	}

	for (int i = 30; i < 40; i++)
	{
		if (i != 35 && i != 38)
		{
			arr[i][0] = 3000;
			arr[i][1] = 3400;
			arr[i][2] = 3800;
			arr[i][3] = 4200;
		}

		else
		{
			arr[i][0] = 0;
			arr[i][1] = 0;
			arr[i][2] = 0;
			arr[i][3] = 0;
		}
	}
}

CBuild::~CBuild()
{
}
