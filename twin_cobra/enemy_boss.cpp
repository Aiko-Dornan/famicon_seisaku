#include"enemy_boss.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CBossEnemy::CBossEnemy(float fx, float fy)
{
	img = LoadGraph("img\\Boss1.png");

	ImgWidth = 56;
	ImgHeight = 56;

	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;


	vec.y = 2.0f;

	ID = ENEMY;

	hp = 200;

	fire_cooldown = 45;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = true;

	enemyid = BOSSENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;

	// ★ スクロール停止
	if (g_BackGround)
		g_BackGround->stopScroll = true;

	hit_score = 300;
	die_score = 2000;

}

int CBossEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (!p) return 0;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	if (ForcedFoward > 0)
	{
		vec.y = 2.0f;
		ForcedFoward--;
		
	}
	else
	{
		if (stop_flag)
		{
			stop_moving_time--;
			vec.y = 0.0f;
			anime_flame = 0;
			if (stop_moving_time < 0)
			{
				stop_flag = false;
				allow_moving_time = 45;
			}

			//if (pos.y > move_limit && p->m_pos.y - drawY > 50&&!limit)
			//{
			//	Fwd_Bwd_Flag = false;
			//}
			//else
			//{
			//	limit = true;
			//	//Fwd_Bwd_Flag = true;
			//}

			switch (GetRand(1))
			{
			case 0:
				if (pos.y > move_limit)
				{
					Fwd_Bwd_Flag = false;
					break;
				}

			case 1:
				if (pos.y < 800)
				{
					Fwd_Bwd_Flag = true;
					break;
				}
			default:
				Fwd_Bwd_Flag = false;
				break;
			}

		}
		else
		{
			vec.y = Fwd_Bwd_Flag ? 1.0f : -1.0f;

			allow_moving_time--;

			if (allow_moving_time < 0)
			{
				stop_flag = true;
				stop_moving_time = 45;
			}

		}
	}

	

	

	pos.x += vec.x;
	pos.y += vec.y;

	if (hp <= 0/*||pos.y>p->pos.y+WINDOW_HEIGHT*/)
	{
		if (g_BackGround)
			g_BackGround->stopScroll = false;

		Die(base);

		//FLAG = false;
	}

	if (fire_cooldown < 0)
	{
		//base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos));

		//Fire(base);
		if (p) Fire(base, p->m_pos);  // ← プレイヤー座標を渡す

	}
	else
	{
		fire_cooldown--;
	}

	Animetion(base);


	return 0;
}

void CBossEnemy::Draw()
{
	//DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


	if (!g_BackGround) return;



	DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "%d", hp);

	DrawRectGraph(
		drawX, drawY,
		CutX, CutY,
		ImgWidth, ImgHeight,
		img, true
	);

	//// base から背景取得
	//extern vector<unique_ptr<BaseVector>> base; // もしグローバルで持っているなら
	//CBackGround* bg = (CBackGround*)Get_obj(base, BACKGROUND);
	//if (!bg) return;

	//float drawX = pos.x - bg->camera.x + WINDOW_WIDTH / 2;
	//float drawY = pos.y - bg->camera.y + WINDOW_HEIGHT / 2;

	//DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);
}