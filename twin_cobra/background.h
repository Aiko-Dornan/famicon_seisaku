#pragma once
#include"objBase.h"

class CBackGround :public BaseVector
{
public:
	CBackGround();

	int Action(vector<unique_ptr<BaseVector>>&);

	void Draw();
	
	//ƒJƒƒ‰À•W
	Point camera{ 0,0 };

	float scrollspeed{ 1.0f };

	int tipNo{ -1 };

};