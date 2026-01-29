//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include"title.h"
#include "function.h"
#include"player.h"
#include"background.h"
#include"testenemy.h"
#include"enemy_heli.h"
#include"enemy_cannon.h"
#include"enemy_bonusheli.h"
#include"enemy_boss.h"
#include <fstream>
#include <sstream>



bool LoadEnemyCSV(const char* filename, vector<EnemySpawnData>& outList)
{
	std::ifstream file(filename);
	if (!file) return false;

	std::string line;

	while (std::getline(file, line))
	{
		// コメント行は無視
		if (line.empty() || line[0] == '#')
			continue;

		std::stringstream ss(line);
		std::string item;

		EnemySpawnData data;

		std::getline(ss, item, ',');
		data.type = std::stoi(item);

		std::getline(ss, item, ',');
		data.x = std::stof(item);

		std::getline(ss, item, ',');
		data.spawnY = std::stof(item);

		data.spawned = false;

		outList.push_back(data);
	}

	return true;
}


//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){

	

	//map = new CMap();//マップマネージャー生成
	//map->LoadMap();//マップデータの読み込み
	//map->Map_Obj_Creation(base);//マップチップオブジェクト生成
	
	base.emplace_back((unique_ptr<BaseVector>)new CBackGround());

	base.emplace_back((unique_ptr<BaseVector>)new CPlayer());

	/*for (int i = 0; i < 10; i++)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTestEnemy(pos.x,pos.y));
	}*/

	// CSV を読み込む
	LoadEnemyCSV("LoadEnemy\\LoadEnemy.csv", SpawnList);

	
}

//更新処理
int CGame::Update(){

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	CBackGround* bg = (CBackGround*)Get_obj(base, BACKGROUND);
	float cameraY = bg->camera.y;
	static float prevPlayerY = p->m_pos.y;
	// ===== 敵スポーン処理 =====
	//for (auto& s : SpawnList)
	//{
	//	if (!s.spawned && p->m_pos.y <= s.spawnY)
	//	{
	//		// 敵を種類に応じて生成
	//		switch (s.type)
	//		{
	//		case 0:
	//			base.emplace_back((unique_ptr<BaseVector>)new CTestEnemy(s.x, s.spawnY));
	//			break;

	//		/*case 1:
	//			base.emplace_back(std::make_unique<CBossEnemy>(s.x, s.spawnY));
	//			break;*/
	//		}

	//		s.spawned = true;
	//	}
	//}



	for (auto& s : SpawnList)
	{
		if (!s.spawned &&
			prevPlayerY > s.spawnY &&
			p->m_pos.y <= s.spawnY+600)
		{
			// 敵を種類に応じて生成
			switch (s.type)
			{
			case 0:
				base.emplace_back((unique_ptr<BaseVector>)new CHeliEnemy(s.x, s.spawnY));
				break;

			case 1:
				//base.emplace_back(std::make_unique<CTestEnemy>(s.x, s.spawnY));
				base.emplace_back((unique_ptr<BaseVector>)new CBonusHeliEnemy(s.x, s.spawnY));
				break;
			case 2:
				base.emplace_back((unique_ptr<BaseVector>)new CCannonEnemy(s.x, s.spawnY));
				break;
			case 3:
				base.emplace_back((unique_ptr<BaseVector>)new CBossEnemy(s.x, s.spawnY));
				break;
			}
			
			s.spawned = true;
		}
	}

	prevPlayerY = p->m_pos.y;

	if (p && p->requestRespawn)
	{
		float respawnY = p->deadY + RESPAWN_BACK_Y;

		// 下限（ステージ最初より戻らない）
		if (respawnY > bg->stageStartY - WINDOW_HEIGHT / 2)
			respawnY = bg->stageStartY-WINDOW_HEIGHT/2;

		// プレイヤー復活
		p->m_pos.y = respawnY;
		p->hp = p->maxhp;
		p->player_state = p->STATE_IDLE;
		p->requestRespawn = false;
		p->bomb_num = 2;
		p->bullet_num = 1;
		p->bullet_id = 0;

		p->arrive_flag = true;
		
		p->anime_flame_t = 0;
		p->anime_flame = 2;
		p->die_anime_flag = false;

		// 背景スクロールも巻き戻す
		bg->camera.y = respawnY;

		// 敵スポーンリセット
		ResetEnemySpawn(respawnY-WINDOW_HEIGHT);

		for (auto it = base.begin(); it != base.end();)
		{
			if ((*it)->ID == ENEMY)
				it = base.erase(it);
			else
				++it;
		}

		for (auto it = base.begin(); it != base.end();)
		{
			if ((*it)->ID == ITEM)
				it = base.erase(it);
			else
				++it;
		}

	}

	if (p && p->isGameOver|| p && p->isGameClear)
	{
		static bool prevSpace = false;
		bool nowSpace = CheckHitKey(KEY_INPUT_TAB);

		// 押した瞬間だけ反応
		if (nowSpace && !prevSpace)
		{
			CManager* m = manager;   // ← 先に保存！
			delete m->scene;
			m->scene = new CTitle(m);
			return 0;
		}

		prevSpace = nowSpace;
	}

	//更新処理
	for (int i = 0; i < base.size(); i++)
		base[i]->Action(base);

	//削除処理
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//オブジェクトのソート処理(クイックソート)
	ObjSort_Quick(base, 0, base.size() - 1);

	//listオブジェクトの更新処理	
	//for (auto i = base.begin(); i != base.end(); i++)
	//	(*i)->Action(base);

	return 0;
}

//描画処理
void CGame::Draw()
{
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	
	for (int i = 0; i < base.size(); i++)
		if(base[i]->FLAG) base[i]->Draw();

	//listオブジェクトの描画
	//for (auto i = base.begin(); i != base.end(); i++)
	//	if ((*i)->FLAG) (*i)->Draw();

	//3D軸の描画
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 0, 100),
	//	0x0000ff
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(100, 0, 0),
	//	0xff0000
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 100, 0),
	//	0x00ff00
	//);
}

CGame::~CGame()
{

}

void CGame::ResetEnemySpawn(float respawnY)
{
	for (auto& s : SpawnList)
	{
		if (s.spawnY <= respawnY)
		{
			s.spawned = false;
		}
	}
}

