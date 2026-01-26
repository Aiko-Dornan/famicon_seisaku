#include"enemybullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"
#include"background.h"

CEbullet::CEbullet(Point startPos, Point dir)
{
	img = LoadGraph("img\\EnemyBullet.png");

	ImgWidth = 8;
	ImgHeight = 8;

	//vec.y += 8.0f;

	ID = EBULLET;

	pos = startPos;
	vec.x = dir.x;
	vec.y = dir.y;

	FLAG = true;


	pri = 10;


}

int CEbullet::Action(vector<unique_ptr<BaseVector>>& base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;


	pos.x += vec.x * speed;
	pos.y += vec.y * speed;

	// âÊñ äOÇ≈çÌèú
	if (drawX < 0 || drawX > WINDOW_WIDTH || drawY < 0 || drawY > WINDOW_HEIGHT)
		FLAG = false;

	CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);

	


	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == PLAYER)
		{
			if (HitCheck_box((*i)->pos.x, (*i)->pos.y, drawX, drawY, p->ImgWidth, p->ImgHeight, ImgWidth, ImgHeight))
			{
				//Ç±Ç±Ç≈ìGÇÃHPÇå∏ÇÁÇ∑
				//CPlayer* player = (CPlayer*)Get_obj(base, PLAYER);
				(*i)->hp -= 1;  // Å© HPÇå∏ÇÁÇ∑ÅI
				FLAG = false;    // íeÇè¡Ç∑
				break;           // 1ëÃÇ…ìñÇΩÇ¡ÇΩÇÁèIóπ
				/*if (HitCheck_box(enemy->pos.x, enemy->pos.y, pos.x, pos.y, enemy->radius, radius))
				{

				}*/

			}


		}


	}



	return 0;
}

void CEbullet::Draw()
{
	DrawGraph(drawX, drawY, img, true);


}