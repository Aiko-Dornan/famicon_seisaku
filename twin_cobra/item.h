#pragma once
#include"objBase.h"

class CItem :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CItem(Point pos);
	~CItem() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	void ItemGet();

	int radius{ 10 };

	bool appear{ false };


};
