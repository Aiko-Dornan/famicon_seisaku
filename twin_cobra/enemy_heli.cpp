#include"enemy_heli.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CHeliEnemy::CHeliEnemy(float fx, float fy)
{

	ImgWidth = radius * 2;
	ImgHeight = radius * 2;

	vec.x = 0.0f;  // 初期直進速度
	vec.y = 4.0f;

	ID = ENEMY;

	hp = 1;

	fire_cooldown = 25;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = false;

	enemyid = NORMALENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;

	state = EnemyState::Approach; // 初期状態は直進
	switchDistance = 200.0f;      // プレイヤー追尾に切替える距離
}

int CHeliEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
	if (!p) return 0;

	drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;

	// プレイヤーとの距離
	float dx = p->pos.x - drawX;
	float dy = p->pos.y - drawY;
	float dist = sqrtf(dx * dx + dy * dy);

	// 状態切替
	if (state == EnemyState::Approach && dist < switchDistance)
	{
		state = EnemyState::Chase;
	}

	// 移動
	if (state == EnemyState::Approach)
	{
		pos.x += vec.x;
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
		Die(base);

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

	return 0;
}

void CHeliEnemy::Draw()
{
	//DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


	if (!g_BackGround) return;



	DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "%f,%f", pos.x, pos.y);

	DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);

	//// base から背景取得
	//extern vector<unique_ptr<BaseVector>> base; // もしグローバルで持っているなら
	//CBackGround* bg = (CBackGround*)Get_obj(base, BACKGROUND);
	//if (!bg) return;

	//float drawX = pos.x - bg->camera.x + WINDOW_WIDTH / 2;
	//float drawY = pos.y - bg->camera.y + WINDOW_HEIGHT / 2;

	//DrawCircle(drawX, drawY, radius, GetColor(255, 255, 255), true);
}