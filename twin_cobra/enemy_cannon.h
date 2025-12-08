#pragma once
#include"enemybase.h"

class CCannonEnemy :public CEnemyBase
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CCannonEnemy(float x, float y);
	~CCannonEnemy() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();




};
