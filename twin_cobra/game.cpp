//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"
#include"player.h"
#include"background.h"
#include"testenemy.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){

	

	//map = new CMap();//マップマネージャー生成
	//map->LoadMap();//マップデータの読み込み
	//map->Map_Obj_Creation(base);//マップチップオブジェクト生成

	base.emplace_back((unique_ptr<BaseVector>)new CBackGround());

	base.emplace_back((unique_ptr<BaseVector>)new CPlayer());

	for (int i = 0; i < 10; i++)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTestEnemy());
	}

	

	
}

//更新処理
int CGame::Update(){
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
