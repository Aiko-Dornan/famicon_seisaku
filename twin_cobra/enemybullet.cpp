#include"enemybullet.h"
#include"function.h"
#include"player.h"
#include"enemybase.h"

CEbullet::CEbullet(Point startPos, Point dir)
{

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

	


	pos.x += vec.x * speed;
	pos.y += vec.y * speed;

	// âÊñ äOÇ≈çÌèú
	if (pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT)
		FLAG = false;

	CEnemyBase* eb = (CEnemyBase*)Get_obj(base, ENEMY);

	


	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == PLAYER)
		{
			if (HitCheck_box((*i)->pos.x, (*i)->pos.y, pos.x, pos.y, p->ImgWidth, p->ImgHeight, radius, radius))
			{
				//Ç±Ç±Ç≈ìGÇÃHPÇå∏ÇÁÇ∑
				CPlayer* player = (CPlayer*)Get_obj(base, PLAYER);
				player->hp -= 1;  // Å© HPÇå∏ÇÁÇ∑ÅI
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
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


}