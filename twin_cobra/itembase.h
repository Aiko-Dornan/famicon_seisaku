#pragma once
#include"objBase.h"

class CItemBase :public BaseVector
{
public:
	//位置、チップナンバー、イメージハンドル
	/*CBlock(Point, int, int);*/
	//CPlayer(Point, int, int);
	CItemBase(Point pos);
	~CItemBase() {};

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();



	void ItemGet(vector<unique_ptr<BaseVector>>&);

	int radius{ 10 };

	bool appear{ false };

	enum ItemID {
		Upgrade,
		Change,
		Bomb,

	};

	int itemid{ -1 };

	int item_color_r{ 0 };
	int item_color_g{ 0 };
	int item_color_b{ 0 };

	int color_change_time{ 50 };
	int color_type{ 0 };


};
