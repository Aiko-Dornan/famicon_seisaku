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

	void Fire(vector<unique_ptr<BaseVector>>&);

	//マップ上の位置
	Point m_pos{ 0,0 };

	int fire_cooldown{ 10 };
	//int hp{ 10 };
	int bullet_num{ 1 };
	int bomb_num{ 2 };
	int bomb_interval{ 20 };
	bool bomb_flag{ true };

	int tipNo{ -1 };
};
