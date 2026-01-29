//ゲームシーンヘッダ
#pragma once
#include "objBase.h"
#include "CCamera.h"
#include"map.h"

struct EnemySpawnData
{
	int type;         // 敵の種類
	float x;          // 出現X座標
	float spawnY;     // このYに到達したら spawn
	bool spawned;     // すでに出したか？
};

bool LoadEnemyCSV(const char* filename, std::vector<EnemySpawnData>& outList);

class CGame :public CScene
{
private:
public:
	//オブジェクト
	//リスト
	//list<unique_ptr<Base3D>> base3D;//3Dオブジェクト
	//list<unique_ptr<Base>> base;//2Dオブジェクト
	//ベクター
	vector<unique_ptr<BaseVector>> base;

	//コンストラクタ
	CGame(CManager*);

	//デストラクタ
	~CGame();

	int Update();//更新処理
	void Draw();//描画処理

	void ResetEnemySpawn(float respawnY);

	//マップマネージャー
	CMap* map;

	vector<EnemySpawnData> SpawnList;

	const float RESPAWN_BACK_Y = 600.0f;

	//CCamera* camera;//カメラオブジェクト
};