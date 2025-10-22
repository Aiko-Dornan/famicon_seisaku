#pragma once
#include"objBase.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>

class CMap {
public:
	CMap();
	~CMap() { DeleteGraph(img); };

	//マップチップの画像
	int img;
	//マップデータ
	int map[197][12]{ 0 };
	//ステージデータ読み込み
	void LoadMap();
	//マップ生成
	void Map_Obj_Creation(vector<unique_ptr<BaseVector>>&);

};
