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


	for (int i = 0; i < 40; i++)
	{
		arr[i][0] = 200;
		arr[i][1] = 400;
		arr[i][2] = 600;
		arr[i][3] = 800;
	}


}

CBuild::~CBuild()
{
}
