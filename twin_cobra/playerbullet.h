#pragma once
#include"objBase.h"

class CPbullet :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CPbullet(Point pos);
	~CPbullet() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int radius{ 4 };

	bool appear{ false };

	
};

