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

	void Animetion(vector<unique_ptr<BaseVector>>&);

	int radius{ 16 };

	//int hp{ 10 };
	float drawX{ 0.0f };
	float drawY{ 0.0f };
	bool item_drop{ false };
	bool appear{ false };

	int fire_cooldown{ 10 };
	int refire_cooldown{ fire_cooldown };

	enum class EnemyState
	{
		Approach, // 最初は直進
		Chase,     // プレイヤー追尾
	};

	enum EnemySitu
	{
		IDLE,
		MOVERL,
		MOVEUD,
		DAMEGED,
		DIE,
	};

	enum EnemyID {
		NORMALENEMY,
		BONUSENEMY,
		BOSSENEMY,

	};

	int enemyid{ -1 };

	EnemyState state{ 0 };
	float switchDistance{ 0.0f };

	int move_down_time{ 20 };

	int situation{ 0 };
	int vault_situation{ 0 };

	int anime_flame{ 0 };
	int anime_flame_t{ 0 };

	int anime_time{ 5 };
	int re_anime_time{ 5 };

	bool arrive_flag{ true };
	bool die_anime_flag{ false };

};

