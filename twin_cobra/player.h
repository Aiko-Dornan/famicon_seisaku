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

	int tipNo{ -1 };
};
