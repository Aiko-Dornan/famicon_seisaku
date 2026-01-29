#include"bomb.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"
#include"background.h"

CBomb::CBomb(Point pos)
{
	

	this->pos = pos;
	



	vec.y -= 8.0f;

	ID = ITEM;


	pri = 10;


}

int CBomb::Action(vector<unique_ptr<BaseVector>>& base)
{
	//CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	/*CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);*/

	

	Explosion(base);

	


	



	return 0;
}

void CBomb::Explosion(vector<unique_ptr<BaseVector>>& base)
{
	
	

	if (explosive_flag)
	{
		for (auto i = base.begin(); i != base.end(); i++)
		{
			float drawX = (*i)->pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
			float drawY = (*i)->pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

			if ((*i)->ID == ENEMY)
			{
				if (HitCheck_box(drawX, drawY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
				{
					//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
					//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
					(*i)->hp -= 10;  // © HP‚ðŒ¸‚ç‚·I
				}
			}

			if ((*i)->ID == EBULLET)
			{
				if (HitCheck_box(drawX, drawY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
				{
					//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
					//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
					(*i)->FLAG=false;  // © HP‚ðŒ¸‚ç‚·I
				}
			}

		}
		FLAG = false;    // ”š’e‚ðÁ‚·
	}
	else
	{
		radius += 30;

		if (radius>WINDOW_HEIGHT)
		{
			explosive_flag = true;
		}

	}
	
}

void CBomb::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 0), true);


}