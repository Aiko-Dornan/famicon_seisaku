#pragma once
#include"enemybase.h"

class CTestEnemy :public CEnemyBase
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CTestEnemy(float x,float y);
	~CTestEnemy() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	


};

