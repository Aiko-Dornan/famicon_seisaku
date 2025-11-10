#pragma once
#include"objBase.h"

class CPlayer :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CPlayer();
	~CPlayer() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	//マップ上の位置
	Point m_pos{ 0,0 };

	int fire_cooldown{ 10 };
	int hp{ 10 };

	int tipNo{ -1 };
};
