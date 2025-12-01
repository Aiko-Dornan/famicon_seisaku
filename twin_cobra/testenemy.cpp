#include"testenemy.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"
#include"background.h"

CTestEnemy::CTestEnemy(float fx,float fy)
{

	ImgWidth = radius*2;
	ImgHeight = radius*2;

	vec.x = 2.0f;

	ID = ENEMY;

	hp = 1;

	fire_cooldown = 25;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = false;

	//enemyid = NORMALENEMY;
	enemyid = BONUSENEMY;
	pri = 10;

	pos.x = fx;
	pos.y = fy;

	appear = true;
}

int CTestEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);

	 drawX = pos.x - g_BackGround->camera.x + WINDOW_WIDTH / 2;
	 drawY = pos.y - g_BackGround->camera.y + WINDOW_HEIGHT / 2;



	//if (!appear)
	//{


	//	pos.y = p->pos.y-300;

	//	//appear = true;
	//}

	if (pos.x<0+radius/2||pos.x>WINDOW_WIDTH-radius/2)
	{
		vec.x = -vec.x;
	}
	pos.x += vec.x;


	if (hp<0/*||pos.y>p->pos.y+WINDOW_HEIGHT*/)
	{
		Die(base);

		//FLAG = false;
	}

	if (fire_cooldown<0)
	{
		//base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos));

		//Fire(base);
		if (p) Fire(base, p->m_pos);  // ← プレイヤー座標を渡す
		
	}
	else
	{
		fire_cooldown --;
	}

	return 0;
}

void CTestEnemy::Draw()
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