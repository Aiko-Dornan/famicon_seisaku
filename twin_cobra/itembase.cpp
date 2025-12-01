#include"itembase.h"
#include"function.h"
#include"enemybase.h"
#include"player.h"
#include"playerbullet.h"
#include"background.h"

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
		
		item_color_r = 255;
		break;
	case CItemBase::Change:
		
		//item_color_r = 255;
		color_type = GetRand(3);
		break;
	case CItemBase::Bomb:
		
		item_color_r = 50;
		break;
	default:
		item_color_r = 0;
		break;
	
	}


}

int CItemBase::Action(vector<unique_ptr<BaseVector>>& base)
{
	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	/*CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);

	if (!appear)
	{


		pos = eb->pos;

		

		appear = true;
	}*/

	if (color_change_time>0)
	{
		color_change_time--;
	}
	else
	{
		color_change_time = 50;

		if (color_type<3)
		{
			color_type++;
		}
		else
		{
			color_type = 0;
		}

	}

	if (itemid==Change)
	{
		switch (color_type)
		{
		case 0:
			item_color_r = 255;
			item_color_g = 0;
			item_color_b = 0;
			break;
		case 1:
			item_color_r = 0;
			item_color_g = 255;
			item_color_b = 0;
			break;
		case 2:
			item_color_r = 0;
			item_color_g = 0;
			item_color_b = 0;
			break;
		case 3:
			item_color_r = 255;
			item_color_g = 255;
			item_color_b = 0;
			break;

		default:
			break;
		}


	}

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (pos.y < p->pos.y - WINDOW_HEIGHT)
	{
		FLAG = false;
	}

	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == PLAYER)
		{
			if (HitCheck_box((*i)->pos.x, (*i)->pos.y, drawX, drawY, p->ImgWidth, p->ImgHeight, radius, radius))
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
	DrawCircle(drawX, drawY, radius, GetColor(item_color_r, item_color_g, item_color_b), true);

	
}

void CItemBase::ItemGet(vector<unique_ptr<BaseVector>>&base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	

	switch (itemid)
	{
	case CItemBase::Upgrade:
		if (p->bullet_num<10)
		{
			p->bullet_num++;
		}
		break;
	case CItemBase::Change:
		if (p->bullet_id==color_type)
		{
			if (p->bullet_num < 10)
			{
				p->bullet_num++;
			}
		}
		else
		{
			for (auto i = base.begin(); i != base.end(); i++)
			{
				if ((*i)->ID==PBULLET)
				{
					(*i)->FLAG = false;
				}

			}

			p->bullet_num = 1;
			p->bullet_id = color_type;
		}
		
		break;
	case CItemBase::Bomb:
		p->bomb_num++ ;
		
		break;
	default:
		break;
	}


}