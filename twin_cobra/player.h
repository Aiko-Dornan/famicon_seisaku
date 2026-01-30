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
	int maxhp{ 10 };
	int bullet_num{ 1 };
	int bomb_num{ 3 };
	int bomb_interval{ 20 };
	bool bomb_flag{ true };
	int anime_flame{ 0 };
	int anime_flame_t{ 0 };
	int bullet_id{ 0 };

	float rad{ 0.0f };

	int tipNo{ -1 };

	bool arrive_flag{ true };
	bool die_anime_flag{ false };

	enum PlayerState {
		STATE_IDLE,
		STATE_FLY,
		STATE_DIE,
	};

	int player_state{ 0 };

	int anime_time{ 5 };
	int re_anime_time{ 5 };

	int total_score{ 0 };

	int RemainLife{ 5 };
	bool requestReturnTitle = false;
	float deadY = 0.0f;
	bool requestRespawn = false;
	bool isGameOver = false;
	bool isGameClear = false;
};
