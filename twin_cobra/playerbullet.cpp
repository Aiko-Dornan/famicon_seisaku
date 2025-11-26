#include"playerbullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"

CPbullet::CPbullet(float posx,float posy,float ang)
{
	CPlayer cp;

	this->pos.x = posx;
	this->pos.y = posy;

	this->pos.x = pos.x + 15.0f;

	angle = ang;
	speed = 8.0f;

	//vec.y -= 8.0f;

	ID = PBULLET;

	
	pri = 10;

	
}

int CPbullet::Action(vector<unique_ptr<BaseVector>>&base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);
	
	if (pos.y<p->pos.y-WINDOW_HEIGHT|| pos.y > p->pos.y+WINDOW_HEIGHT||pos.x<p->pos.x-WINDOW_WIDTH|| pos.x > p->pos.x + WINDOW_WIDTH)
	{
		FLAG = false;
	}
	

	switch (p->bullet_id)
	{
	case 0:
		vec.y = -8.0f;

		
		break;
	case 1 :
		vec.y = -12.0f;
		break;
	case 2:
		-8.0f;
		pos.x += cosf(angle) * speed;
		pos.y += sinf(angle) * speed;
		break;
	case 3:
		-4.0f;
		pos.x += cosf(angle) * speed;
		pos.y += sinf(angle) * speed;
		break;

	default:
		break;
	}

	pos.y += vec.y;

	
	for (auto i = base.begin(); i != base.end();i++)
	{
		if ((*i)->ID==ENEMY)
		{
			if (HitCheck_box((*i)->pos.x,(*i)->pos.y,pos.x,pos.y, eb->ImgWidth, eb->ImgHeight,radius,radius))
			{
				//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
				//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
				(*i)->hp -= 1;  // © HP‚ðŒ¸‚ç‚·I
				if (p->bullet_id!=1)
				{
					FLAG = false;    // ’e‚ðÁ‚·
				}
				
				break;           // 1‘Ì‚É“–‚½‚Á‚½‚çI—¹
				/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
				{
					
				}*/

			}


		}


	}

	testid=p->bullet_id;

	return 0;
}

void CPbullet::Draw()
{
	DrawCircle(pos.x, pos.y, radius,GetColor(255, 255, 255), true);

	DrawFormatString(pos.x, pos.y + 5, GetColor(255, 255, 255), "%d", testid);
}