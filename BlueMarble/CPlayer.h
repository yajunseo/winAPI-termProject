#pragma once
class CPlayer
{
	int position;

	int money;


public:
	CPlayer();
	~CPlayer();

	int getPosition() { return position; };
	void setPosition(int pos) { position = pos; };
	int getMoney() { return money; };
};

