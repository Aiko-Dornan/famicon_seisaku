#pragma once
#include"objBase.h"

class CBomb :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	//CPbullet(Point pos);
	CBomb(Point pos);
	~CBomb() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int radius{ 5 };
	bool explosive_flag{ false };
	
	void Explosion(vector<unique_ptr<BaseVector>>&);


};

