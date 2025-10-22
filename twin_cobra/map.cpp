#pragma once
#include"map.h"
#include"block.h"

//特定文字で分割する関数

vector<string> split(string& input, char delimiter)
{
	istringstream stream(input);
	string field;
	vector<string>re;
	while (getline(stream, field, delimiter))
	{
		re.push_back(field);
	}
	return re;
}

//コンストラクタ
CMap::CMap()
{
	img = LoadGraph("LoadMap\\NES - Twin Cobra - Maps - Stage 01v5.png");

	//マップ配列の初期化
	for (int y = 0; y < 197; y++)
	{

		for (int x = 0; x < 12; x++)
		{
			map[y][x] = -1;
		}

	}

	/*for (int y = 197; y >0; y--)
	{

		for (int x = 0; x <12; x++)
		{
			map[y][x] = -1;
		}

	}*/

}

//マップデータ読み込み
void CMap::LoadMap()
{
	ifstream fp("LoadMap\\twin_stage1v2.txt");//マップデータファイルの読み込み
	string str;//処理用の文字列

	if (!fp.fail())//マップファイルの読み込みチェック
	{
		//ステージデータの読み込み
		for (int y = 0; y < 197; y++)
		{
			getline(fp, str);//ファイルから1行読み込み
			vector<string>strv = split(str, ',');//読み込んだ行から'，’を抜く

			for (int x = 0; x < 12; x++)
			{

				map[y][x] = stoi(strv.at(x));//int型にしてmapデータ配列に登録


			}

		}

		//for (int y = 197; y >0; y--)
		//{
		//	getline(fp, str);//ファイルから1行読み込み
		//	vector<string>strv = split(str, ',');//読み込んだ行から'，’を抜く

		//	for (int x = 0; x<12; x++)
		//	{

		//		map[y][x] = stoi(strv.at(x));//int型にしてmapデータ配列に登録


		//	}

		//}

		fp.close();//ファイルを閉じる

	}

}

//マップ生成
void CMap::Map_Obj_Creation(vector<unique_ptr<BaseVector>>& base)
{
	for (int y = 0; y < 197; y++)
	{

		for (int x = 0; x < 12; x++)
		{
			Point p{ x * 96,y * 96 };//マップチップサイズ32*32
			base.emplace_back((unique_ptr<BaseVector>)new CBlock(p, map[y][x], img));
			DrawFormatString(x * 32, y * 32, GetColor(255, 255, 255), "%d", map[y][x]);

		}

	}

	//for (int y = 197; y >0; y--)
	//{

	//	for (int x = 0; x <12; x++)
	//	{
	//		Point p{ x * 96,y * 96 };//マップチップサイズ32*32
	//		base.emplace_back((unique_ptr<BaseVector>)new CBlock(p, map[y][x], img));
	//		DrawFormatString(x * 32, y * 32, GetColor(255, 255, 255), "%d", map[y][x]);

	//	}

	//}

}