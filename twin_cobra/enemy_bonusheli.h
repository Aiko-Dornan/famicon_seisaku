#pragma once
#include"enemybase.h"

class CBonusHeliEnemy :public CEnemyBase
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CBonusHeliEnemy(float x, float y);
	~CBonusHeliEnemy() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	


};
