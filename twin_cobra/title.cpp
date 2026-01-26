//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "game.h"
#include "function.h"

#include"background.h"

#include <fstream>
#include <sstream>




//コンストラクタ
CTitle::CTitle(CManager* p) :CScene(p) {

	img = LoadGraph("img\\Title.png");

	//map = new CMap();//マップマネージャー生成
	//map->LoadMap();//マップデータの読み込み
	//map->Map_Obj_Creation(base);//マップチップオブジェクト生成

	//base.emplace_back((unique_ptr<BaseVector>)new CBackGround());



	/*for (int i = 0; i < 10; i++)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CTestEnemy(pos.x,pos.y));
	}*/





}

//更新処理
int CTitle::Update() {


	if (GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_SPACE))
	{
		//シーン管理クラス
		//CManager* manager = new CManager();

		DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = aaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaa");
		//ゲームシーンの生成
		// 今のシーンを削除
		//delete manager->scene;

		//// 同じ manager にゲームシーンをセット
		//manager->scene = new CGame(manager);

		CManager* m = manager; // 先に退避
		delete m->scene;
		m->scene = new CGame(m);
		return 0;
	}




	////更新処理
	//for (int i = 0; i < base.size(); i++)
	//	base[i]->Action(base);

	////削除処理
	//for (auto i = base.begin(); i != base.end();)
	//	(*i)->FLAG ? i++ : i = base.erase(i);

	////オブジェクトのソート処理(クイックソート)
	//ObjSort_Quick(base, 0, base.size() - 1);

	//listオブジェクトの更新処理	
	//for (auto i = base.begin(); i != base.end(); i++)
	//	(*i)->Action(base);

	return 0;
}

//描画処理
void CTitle::Draw()
{
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());

	DrawGraph(0, 0, img, true);

	/*for (int i = 0; i < base.size(); i++)
		if (base[i]->FLAG) base[i]->Draw();*/

		//listオブジェクトの描画
		//for (auto i = base.begin(); i != base.end(); i++)
		//	if ((*i)->FLAG) (*i)->Draw();


}

CTitle::~CTitle()
{

}

