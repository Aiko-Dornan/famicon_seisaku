#include"itembase.h"
#include"function.h"
#include"enemybase.h"
#include"player.h"

CItemBase::CItemBase(Point pos)
{

	this->pos = pos;
	vec.y = 2.0f;

	ID = ITEM;

	itemid = GetRand(2);

	pri = 10;

	switch (itemid)
	{
	case CItemBase::Upgrade:
		
		item_color = 255;
		break;
	case CItemBase::Change:
		
		item_color = 150;
		break;
	case CItemBase::Bomb:
		
		item_color = 50;
		break;
	default:
		item_color = 0;
		break;
	
	}


}

int CItemBase::Action(vector<unique_ptr<BaseVector>>& base)
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


				ItemGet(base);
				FLAG = false;    // íeÇè¡Ç∑
				break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ


			}


		}
	}
	pos.y += vec.y;


	



	return 0;
}

void CItemBase::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(item_color, 0, 0), true);

	
}

void CItemBase::ItemGet(vector<unique_ptr<BaseVector>>&base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);

	switch (itemid)
	{
	case CItemBase::Upgrade:
		if (p->bullet_num<6)
		{
			p->bullet_num++;
		}
		break;
	case CItemBase::Change:
		p->bullet_num = 1;
		
		break;
	case CItemBase::Bomb:
		p->bomb_num++ ;
		
		break;
	default:
		break;
	}


}