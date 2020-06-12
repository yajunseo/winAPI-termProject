#pragma once

class CBuild
{
	int arr[40][4];
	int villaPos[40][2];
	int buildingPos[40][2];
	int HotelPos[40][2];
	int right, top, left, bottom;
public:
	int getPrice(int i, int j) { return arr[i][j]; };
	void setRC(int l, int t, int r, int b);

	int getVillaX(int i) { return villaPos[i][0]; };
	int getVillaY(int i) { return villaPos[i][1]; };
	int getBuildingX(int i) { return buildingPos[i][0]; };
	int getBuildingY(int i) { return buildingPos[i][1]; };
	int getHotelX(int i) { return HotelPos[i][0]; };
	int getHotelY(int i) { return HotelPos[i][1]; };

	CBuild();
	~CBuild();
};
