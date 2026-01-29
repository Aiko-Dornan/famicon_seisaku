#include"enemy_bonusheli.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CBonusHeliEnemy::CBonusHeliEnemy(float fx, float fy)
{
	img = LoadGraph("img\\THeli.png");

	ImgWidth = 46;
	ImgHeight = 66;

	CutX =anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	if (pos.x<WINDOW_WIDTH/2)
	{
		vec.x = +0.5f;  // 初期直進速度
	}
	else
	{
		vec.x = -0.5f;
	}

	
	vec.y = 0.3f;

	ID = ENEMY;

	hp = 10;

	fire_cooldown = 75;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = true;

	enemyid = BONUSENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;

	hit_score = 100;
	die_score = 500;
	
	switchDistance = 200.0f;      // プレイヤー追尾に切替える距離
}

int CBonusHeliEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (!p) return 0;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	

	if (pos.x<0 + radius / 2 || pos.x>WINDOW_WIDTH - radius / 2)
	{
		vec.x = -vec.x;
	}
	

	if (move_down_time>0)
	{
		if (move_down_time>10)
		{
			vec.y = vec.y;
		}
		else
		{
			vec.y = -vec.y;
		}

		move_down_time--;
	}
	else
	{
		move_down_time = 20;
	}

	pos.x += vec.x;
	pos.y += vec.y;

	if (hp <= 0/*||pos.y>p->pos.y+WINDOW_HEIGHT*/)
	{
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

void CBonusHeliEnemy::Draw()
{
	//DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


	if (!g_BackGround) return;



	//DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "%d", hp);

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