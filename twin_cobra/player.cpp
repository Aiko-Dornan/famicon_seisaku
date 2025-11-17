#include"player.h"
#include"playerbullet.h"
#include"bomb.h"

CPlayer::CPlayer()
{
	//img = _img;

	img = LoadGraph("img\\player.png");

	//チップサイズ
	ImgWidth = 30;
	ImgHeight = 40;

	//pos = _p;//描画位置

	//pos.x = WINDOW_WIDTH/2;
	//pos.y = 6000;

	hp = 3;

	m_pos.x = WINDOW_WIDTH / 2;
	m_pos.y = 6150;

	pos = m_pos;

	//切り取り位置
	//16はマップチップ画像の横個数

	CutX = (/*_No*/ 7% 6) * ImgWidth;
	CutY = (/*_No*/ 7/ 5) * ImgHeight;

	pri = 10;

	ID = PLAYER;

	//tipNo = _No;

}

int CPlayer::Action(vector<unique_ptr<BaseVector>>& base) { 
	
	if (CheckHitKey(KEY_INPUT_W))
	{
		vec.y -= 3.0f;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		vec.y += 3.0f;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		vec.x -= 3.0f;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		vec.x += 3.0f;
	}
	if (CheckHitKey(KEY_INPUT_F)&&bomb_num>0&&bomb_interval<0&&bomb_flag)
	{
		base.emplace_back((unique_ptr<BaseVector>)new CBomb(pos));
		bomb_num--;
		bomb_interval = 20;
		bomb_flag = false;
	}
	else if (!CheckHitKey(KEY_INPUT_F))
	{
		
		bomb_flag = true;
	}
	bomb_interval--;

	if (CheckHitKey(KEY_INPUT_SPACE)&&fire_cooldown<0)
	{
		//base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x,pos.y));
		Fire(base);
	}
	fire_cooldown--;


	if (m_pos.x>=WINDOW_WIDTH-ImgWidth)
	{
		m_pos.x = WINDOW_WIDTH-ImgWidth;
	}
	if (m_pos.x<=0)
	{
		m_pos.x = 0;

	}

	


	m_pos.x += vec.x;
	m_pos.y += vec.y;
	
	vec.x = 0.0f;
	vec.y = 0.0f;

	return 0; }

void CPlayer::Draw()
{
	//DrawCircle(pos.x, pos.y, 32, GetColor(255, 255, 255), true);

	DrawRectGraph(
		pos.x, pos.y,
		CutX, CutY,
		ImgWidth, ImgHeight,
		img, true
	);

	DrawFormatString(pos.x - 50, pos.y + 30, GetColor(255, 255, 255), "bull:%d,bomb:%d", bullet_num, bomb_num);

}

void CPlayer::Fire(vector<unique_ptr<BaseVector>>&base)
{
	for (int i = 1; i <= bullet_num; i++)
	{
		if (bullet_num == 1)
		{
			base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y));
		}
		else
		{
			if (bullet_num % 2 == 0)
			{
				if (i % 2 == 0)
				{
					base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + 7 * (i - 1), pos.y));
				}
				else
				{
					base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - 7 * i, pos.y));
				}
			}
			else
			{
				if (i == 1)
				{
					base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y));
				}
				else
				{
					if (i % 2 == 0)
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + 7 * (i), pos.y));
					}
					else
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - 7 * (i - 1), pos.y));
					}
				}



			}


		}



	}

	fire_cooldown = 10;
}