//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
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

