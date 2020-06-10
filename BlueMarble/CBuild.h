#pragma once
class CBuild
{
	int arr[40][4];
public:
	int getPrice(int i, int j) { return arr[i][j]; };
	CBuild();
	~CBuild();
};

