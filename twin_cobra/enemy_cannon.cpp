#include"enemy_cannon.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CCannonEnemy::CCannonEnemy(float fx, float fy)
{
	img = LoadGraph("img\\Turret.png");

	ImgWidth = 34;
	ImgHeight = 34;

	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	vec.x = 0.0f;  // 初期直進速度
	vec.y = 4.0f;

	ID = ENEMY;

	hp = 2;

	fire_cooldown = 25;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = false;

	enemyid = NORMALENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;

	situation = EnemySitu::ROTATE;
	HeliORTurretRotate = 1;
	break_flag = true;

	hit_score = 50;
	die_score = 100;

}

int CCannonEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (!p) return 0;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	

	



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

void CCannonEnemy::Draw()
{
	//DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


	if (!g_BackGround) return;

	//DrawFormatString(drawX+40, drawY, GetColor(255, 255, 255), "%d", anime_flame);

	//DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "%f,%f", pos.x, pos.y);

	//DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);

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