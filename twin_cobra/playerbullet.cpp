#include"playerbullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"
#include"background.h"

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
	
	CBackGround* bg = (CBackGround*)Get_obj(base, BACKGROUND);

	

	if (pos.y<10|| pos.y >WINDOW_HEIGHT||pos.x<0|| pos.x >WINDOW_WIDTH)
	{
		FLAG = false;
	}

	/*if (pos.y<bg->camera.y - WINDOW_HEIGHT || pos.y > bg->camera.y + WINDOW_HEIGHT || pos.x<p->pos.x - WINDOW_WIDTH || pos.x > p->pos.x + WINDOW_WIDTH)
	{
		FLAG = false;
	}*/
	

	switch (p->bullet_id)
	{
	case 0://ƒm[ƒ}ƒ‹
		vec.y = -8.0f;

		
		break;
	case 1 ://ƒŒ[ƒU[
		vec.y = -12.0f;
		break;
	case 2://ŠgŽU
		-8.0f;
		pos.x += cosf(angle) * speed;
		pos.y += sinf(angle) * speed;
		break;
	case 3://\Žš
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
			float drawX = (*i)->pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
			float drawY = (*i)->pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;
			if (HitCheck_box(drawX, drawY, /*(*i)->pos.x, (*i)->pos.y,*/ pos.x, pos.y, (*i)->ImgWidth, (*i)->ImgHeight, radius, radius)&&(*i)->hp>0)
			//if(HitCheck_box(this,enemy))
			{
				auto* enemy = (CEnemyBase*)(*i).get();
				enemy->vault_situation = enemy->situation;
				enemy->situation = enemy->DAMEGED;
				enemy->anime_time = enemy->re_anime_time;
				//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
				//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
				(*i)->hp -= 1;  // © HP‚ðŒ¸‚ç‚·I
				if (p->bullet_id != 1)
				{
					FLAG = false;    // ’e‚ðÁ‚·
				}

				
				break;           // 1‘Ì‚É“–‚½‚Á‚½‚çI—¹
				/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
				{

				}*/

			}

			//if (HitCheck_box((*i)->pos.x,(*i)->pos.y,pos.x,pos.y, eb->ImgWidth, eb->ImgHeight,radius,radius))
			//{
			//	//‚±‚±‚Å“G‚ÌHP‚ðŒ¸‚ç‚·
			//	//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
			//	(*i)->hp -= 1;  // © HP‚ðŒ¸‚ç‚·I
			//	if (p->bullet_id!=1)
			//	{
			//		FLAG = false;    // ’e‚ðÁ‚·
			//	}
			//	
			//	break;           // 1‘Ì‚É“–‚½‚Á‚½‚çI—¹
			//	/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
			//	{
			//		
			//	}*/

			//}


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