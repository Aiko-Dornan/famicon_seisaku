#include"playerbullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"

CPbullet::CPbullet(Point pos)
{
	this->pos = pos;

	this->pos.x = pos.x + 15.0f;

	vec.y -= 8.0f;

	ID = PBULLET;

	
	pri = 10;

	
}

int CPbullet::Action(vector<unique_ptr<BaseVector>>&base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);
	
	if (pos.y<p->pos.y-WINDOW_HEIGHT)
	{
		FLAG = false;
	}
	

	pos.y += vec.y;

	
	for (auto i = base.begin(); i != base.end();i++)
	{
		if ((*i)->ID==ENEMY)
		{
			if (HitCheck_box((*i)->pos.x,(*i)->pos.y,pos.x,pos.y, eb->ImgWidth, eb->ImgHeight,radius,radius))
			{
				//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
				CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
				enemy->hp -= 1;  // © HP‚ðŒ¸‚ç‚·I
				FLAG = false;    // ’e‚ðÁ‚·
				break;           // 1‘Ì‚É“–‚½‚Á‚½‚çI—¹
				/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
				{
					
				}*/

			}


		}


	}

	

	return 0;
}

void CPbullet::Draw()
{
	DrawCircle(pos.x, pos.y, radius,GetColor(255, 255, 255), true);


}