#pragma once
#include"objBase.h"

class CEbullet :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル

	//CEbullet(Point pos);
	CEbullet(Point startPos, Point dir);
	~CEbullet() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float drawX{ 0.0f };
	float drawY{ 0.0f };

	int radius{ 4 };

	bool appear{ false };

	float speed = 6.0f;
};