#pragma once
#include"objBase.h"

class CEnemyBase :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	/*CEnemyBase();
	//~CEnemyBase() {};*/

	/*int Action(vector<unique_ptr<BaseVector>>&);
	//void Draw();*/

	int radius{ 16 };

	int hp{ 10 };

	bool item_drop{ false };
	bool appear{ false };

	enum EnemyID {
		NORMALENEMY,
		BONUSENEMY,
		BOSSENEMY,

	};

	int enemyid{ -1 };

};

