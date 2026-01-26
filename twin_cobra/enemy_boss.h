#pragma once
#include"enemybase.h"

class CBossEnemy :public CEnemyBase
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CBossEnemy(float x, float y);
	~CBossEnemy() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();




};
