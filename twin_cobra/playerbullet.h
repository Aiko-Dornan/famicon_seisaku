#pragma once
#include"objBase.h"

class CPbullet :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	//CPbullet(Point pos);
	CPbullet(float posx, float posy,float ang,int bulletID);
	~CPbullet() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	void ChangeID(int bulletID);

	int radius{ 4 };

	int testid{ 0 };
	
	

	float angle;   // 弾の飛ぶ角度（ラジアン）
	float speed;   // 速度
};

