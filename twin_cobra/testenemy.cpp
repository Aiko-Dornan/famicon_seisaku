#include"testenemy.h"
#include"function.h"
#include"player.h"

CTestEnemy::CTestEnemy(/*Point pos*/)
{

	vec.x = 2.0f;

	ID = ENEMY;

	hp = 5;

	radius = 16;

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


		FLAG = false;
	}



	return 0;
}

void CTestEnemy::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);


}