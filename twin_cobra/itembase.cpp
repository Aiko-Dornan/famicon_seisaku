#include"itembase.h"
#include"function.h"
#include"enemybase.h"
#include"player.h"
#include"playerbullet.h"
#include"background.h"
#include"playerbullet.h"

CItemBase::CItemBase(Point pos)
{
	img = LoadGraph("img\\Item.png");

	ImgWidth = 18;
	ImgHeight = 18;

	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	this->pos = pos;
	vec.y = 2.0f;

	ID = ITEM;

	itemid = GetRand(2);

	pri = 10;

	switch (itemid)
	{
	case CItemBase::Upgrade:
		
		anime_flame=1;
		break;
	case CItemBase::Change:
		
		//item_color_r = 255;
		color_type = GetRand(3);
		break;
	case CItemBase::Bomb:
		
		anime_flame = 0;
		break;
	default:
		item_color_r = 0;
		break;
	
	}


}

int CItemBase::Action(vector<unique_ptr<BaseVector>>& base)
{
	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

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
			anime_flame = 2;
			break;
		case 1:
			anime_flame = 3;
			break;
		case 2:
			anime_flame = 4;
			break;
		case 3:
			anime_flame = 5;
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
			if (HitCheck_box((*i)->pos.x, (*i)->pos.y, drawX, drawY, p->ImgWidth, p->ImgHeight, ImgWidth, ImgHeight))
			{


				ItemGet(base);
				FLAG = false;    // íeÇè¡Ç∑
				break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ


			}


		}
	}
	pos.x += vec.x;
	pos.y += vec.y;


	if (random_time<0)
	{
		RandomMove();
	}
	else
	{
		random_time--;
	}
	



	return 0;
}

void CItemBase::Draw()
{
	//DrawCircle(drawX, drawY, radius, GetColor(item_color_r, item_color_g, item_color_b), true);
	DrawRectGraph(
		drawX, drawY,
		CutX, CutY,
		ImgWidth, ImgHeight,
		img, true
	);
	
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
		if(p->bomb_num<7)
		p->bomb_num++ ;
		
		break;
	default:
		break;
	}


}

void CItemBase::RandomMove()
{
	random_move = GetRand(3);

	switch (random_move)
	{
	case 0:
		vec.x = 1.0f;
		vec.y = 0.0f;
		break;
	case 1:
		vec.x = -1.0f;
		vec.y = 0.0f;
		break;
	case 2:
		vec.x = 0.0f;
		vec.y = 1.0f;
		break;
	case 3:
		vec.x = 0.0f;
		vec.y = -1.0f;
		
		break;
	default:
		break;
	}

	random_time = GetRand(40);

}