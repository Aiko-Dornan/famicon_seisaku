#pragma once
#include"objBase.h"

class CEnemyBase :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	/*CEnemyBase();
	~CEnemyBase() {};*/

	/*int Action(vector<unique_ptr<BaseVector>>&);
	//void Draw();*/

	//void Fire(vector<unique_ptr<BaseVector>>&);
	virtual void Fire(vector<unique_ptr<BaseVector>>& base, Point targetPos);


	void Die(vector<unique_ptr<BaseVector>>&);

	void ItemDrop(vector<unique_ptr<BaseVector>>&,Point pos);

	int radius{ 16 };

	//int hp{ 10 };

	bool item_drop{ false };
	bool appear{ false };

	int fire_cooldown{ 10 };
	int refire_cooldown{ fire_cooldown };

	enum EnemyID {
		NORMALENEMY,
		BONUSENEMY,
		BOSSENEMY,

	};

	int enemyid{ -1 };


};

