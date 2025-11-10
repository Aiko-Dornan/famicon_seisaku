#include"testenemy.h"
#include"function.h"
#include"player.h"
#include"enemybullet.h"

CTestEnemy::CTestEnemy(/*Point pos*/)
{

	ImgWidth = radius*2;
	ImgHeight = radius*2;

	vec.x = 2.0f;

	ID = ENEMY;

	hp = 1;

	fire_cooldown = 25;
	refire_cooldown = fire_cooldown;

	radius = 16;
	item_drop = true;

	enemyid = NORMALENEMY;

	pri = 10;

	pos.x = WINDOW_WIDTH / 2;
}

int CTestEnemy::Action(vector<unique_ptr<BaseVector>>& base)
{
	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);

	if (!appear)
	{


		pos.y = p->pos.y-300;

		//appear = true;
	}

	if (pos.x<0+radius/2||pos.x>WINDOW_WIDTH-radius/2)
	{
		vec.x = -vec.x;
	}
	pos.x += vec.x;


	if (hp<0||pos.y>p->pos.y+WINDOW_HEIGHT)
	{
		Die(base);

		//FLAG = false;
	}

	if (fire_cooldown<0)
	{
		//base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos));

		//Fire(base);
		if (p) Fire(base, p->pos);  // ← プレイヤー座標を渡す
		
	}
	else
	{
		fire_cooldown --;
	}

	return 0;
}

void CTestEnemy::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


}