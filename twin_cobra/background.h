#pragma once
#include"objBase.h"



class CBackGround :public BaseVector
{
public:
	CBackGround();

	int Action(vector<unique_ptr<BaseVector>>&);

	void Draw();
	
	//ÉJÉÅÉâç¿ïW
	Point camera{ 0,0 };

	float scrollspeed{ 0.5f };
	bool stopScroll{ false };

	int tipNo{ -1 };

	

};

extern CBackGround* g_BackGround;