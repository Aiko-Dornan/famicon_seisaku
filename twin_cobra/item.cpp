#include"item.h"
#include"function.h"
#include"enemybase.h"
#include"player.h"

CItem::CItem(Point pos)
{

	this->pos = pos;
	vec.y = 2.0f;

	ID = ITEM;


	pri = 10;


}

int CItem::Action(vector<unique_ptr<BaseVector>>& base)
{
	/*CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);

	if (!appear)
	{


		pos = eb->pos;

		

		appear = true;
	}*/

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (pos.y < p->pos.y - WINDOW_HEIGHT)
	{
		FLAG = false;
	}

	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == PLAYER)
		{
			if (HitCheck_box((*i)->pos.x, (*i)->pos.y, pos.x, pos.y, p->ImgWidth, p->ImgHeight, radius, radius))
			{


				//p->hp -= 1;  // Å© HPÇå∏ÇÁÇ∑ÅI
				FLAG = false;    // íeÇè¡Ç∑
				break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ


			}


		}
	}
	pos.y += vec.y;


	



	return 0;
}

void CItem::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 0, 0), true);

	
}

void CItem::ItemGet()
{

}