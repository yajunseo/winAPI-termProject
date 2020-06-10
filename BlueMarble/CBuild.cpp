#include "CBuild.h"

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
