#pragma once
#include"enemybase.h"

class CHeliEnemy :public CEnemyBase
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CHeliEnemy(float x, float y);
	~CHeliEnemy() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();




};
