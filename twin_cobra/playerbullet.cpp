#include"playerbullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"
#include"background.h"

CPbullet::CPbullet(float posx,float posy,float ang,int BulletID)
{
	//img = LoadGraph("img\\PBulletRed.png");

	//ImgWidth = 8;
	//ImgHeight = 12;

	

	this->pos.x = posx;
	this->pos.y = posy;

	this->pos.x = pos.x + 15.0f;

	angle = ang;
	speed = 8.0f;

	//vec.y -= 8.0f;

	ID = PBULLET;

	
	pri = 10;

	//this->testid = BulletID;

	// íeéÌÇ≤Ç∆ÇÃâÊëúê›íË
	ChangeID(BulletID);
	
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
	case 0://ÉmÅ[É}Éã
		vec.y = -8.0f;

		
		
		break;
	case 1 ://ÉåÅ[ÉUÅ[
		vec.y = -12.0f;

		

		break;
	case 2://ägéU
		-8.0f;
		pos.x += cosf(angle) * speed;
		pos.y += sinf(angle) * speed;

		

		break;
	case 3://è\éö
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
			if (HitCheck_box(drawX, drawY, /*(*i)->pos.x, (*i)->pos.y,*/ pos.x, pos.y, (*i)->ImgWidth, (*i)->ImgHeight, ImgWidth, ImgHeight)&&(*i)->hp>0)
			//if(HitCheck_box(this,enemy))
			{
				auto* enemy = (CEnemyBase*)(*i).get();
			
					//enemy->vault_situation2 = enemy->situation;
					enemy->situation = enemy->DAMEGED;
					enemy->anime_time = enemy->re_anime_time;
					//Ç±Ç±Ç≈ìGÇÃHPÇå∏ÇÁÇ∑
					//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
					if (enemy->invincible_time<0)
					{
						(*i)->hp -= 1;  // Å© HPÇå∏ÇÁÇ∑ÅI
						enemy->invincible_time = enemy->re_anime_time;
					}
					
				

			
				if (p->bullet_id != 1)
				{
					FLAG = false;    // íeÇè¡Ç∑
				}

				
				break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ
				/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
				{

				}*/

			}

			//if (HitCheck_box((*i)->pos.x,(*i)->pos.y,pos.x,pos.y, eb->ImgWidth, eb->ImgHeight,radius,radius))
			//{
			//	//Ç±Ç±Ç≈ìGÇÃHPÇå∏ÇÁÇ∑
			//	//CEnemyBase* enemy = (CEnemyBase*)Get_obj(base, ENEMY);
			//	(*i)->hp -= 1;  // Å© HPÇå∏ÇÁÇ∑ÅI
			//	if (p->bullet_id!=1)
			//	{
			//		FLAG = false;    // íeÇè¡Ç∑
			//	}
			//	
			//	break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ
			//	/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
			//	{
			//		
			//	}*/

			//}


		}


	}

	//testid=p->bullet_id;

	

	return 0;
}

void CPbullet::Draw()
{
	DrawGraph(pos.x, pos.y, img, true);

	//DrawCircle(pos.x, pos.y, radius,GetColor(255, 255, 255), true);

	//DrawFormatString(pos.x, pos.y + 5, GetColor(255, 255, 255), "%d", testid);
	
}

void CPbullet::ChangeID(int bulletID)
{

	/*CPlayer* cp = new CPlayer;*/


	switch (bulletID)
	{
	case 0://ÉmÅ[É}Éã
		img = LoadGraph("img\\PBulletRed.png");

		ImgWidth = 8;
		ImgHeight = 12;
		break;
	case 1://ÉåÅ[ÉUÅ[
		img = LoadGraph("img\\PBulletGreen.png");

		ImgWidth = 7;
		ImgHeight = 14;
		break;
	case 2://ägéU
		img = LoadGraph("img\\PBulletBlue.png");

		ImgWidth = 8;
		ImgHeight = 8;
		break;
	case 3://è\éö
		img = LoadGraph("img\\PBulletYellow.png");

		ImgWidth = 8;
		ImgHeight = 8;
		break;
	default:
		break;
	}

}