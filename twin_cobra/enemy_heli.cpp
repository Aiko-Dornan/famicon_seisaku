#include"enemy_heli.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CHeliEnemy::CHeliEnemy(float fx, float fy)
{
	img = LoadGraph("img\\SmallHeli.png");

	ImgWidth = 28;
	ImgHeight = 28;

	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	vec.x = 0.0f;  // 初期直進速度
	vec.y = 4.0f;

	ID = ENEMY;

	hp = 1;

	fire_cooldown = 25;
	refire_cooldown = fire_cooldown;

	

	item_drop = false;

	enemyid = CHASEENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;

	situation = EnemySitu::ROTATE;
	HeliORTurretRotate = 2;
	state = EnemyState::Approach; // 初期状態は直進
	switchDistance = 400.0f;      // プレイヤー追尾に切替える距離
}

int CHeliEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (!p) return 0;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	CutX = anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;

	// プレイヤーとの距離
	float dx = p->pos.x - drawX;
	float dy = p->pos.y - drawY;
	float dist = sqrtf(dx * dx + dy * dy);

	// 状態切替
	if (state == EnemyState::Approach && dist < switchDistance&&dy>-20)
	{
		state = EnemyState::Chase;
	}
	else
	{
		state = EnemyState::Approach;
		vec.x = 0.0f;
	}

	// 移動
	if (state == EnemyState::Approach)
	{
		//pos.x += vec.x;
		pos.y += vec.y;
	}
	else if (state == EnemyState::Chase)
	{
		if (dist > 100&&dy>0)
		{
			pos.x += dx / dist * 4.0f; // 追尾速度
			pos.y += dy / dist * 4.0f;
		}
		else
		{
			vec.y = 4.0f;
			vec.x = dx / dist * 4.0f;
			
			pos.x += vec.x;
			pos.y += vec.y;
		}
	}



	if (hp <= 0/*||pos.y>p->pos.y+WINDOW_HEIGHT*/)
	{
		state = EnemyState::Approach;
		Die(base);
		vec.x = 0.0f;
		vec.y = 0.0f;
		//FLAG = false;
	}

	if (fire_cooldown < 0&&state == EnemyState::Chase)
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

void CHeliEnemy::Draw()
{
	//DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


	if (!g_BackGround) return;



	DrawFormatString(drawX + 40, drawY, GetColor(255, 255, 255), "%d", anime_flame);
	DrawFormatString(drawX - 40, drawY, GetColor(255, 255, 255), "%d", anime_time);

	DrawRectGraph(
		drawX, drawY,
		CutX, CutY,
		ImgWidth, ImgHeight,
		img, true
	);

	//DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);

	//// base から背景取得
	//extern vector<unique_ptr<BaseVector>> base; // もしグローバルで持っているなら
	//CBackGround* bg = (CBackGround*)Get_obj(base, BACKGROUND);
	//if (!bg) return;

	//float drawX = pos.x - bg->camera.x + WINDOW_WIDTH / 2;
	//float drawY = pos.y - bg->camera.y + WINDOW_HEIGHT / 2;

	//DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);
}