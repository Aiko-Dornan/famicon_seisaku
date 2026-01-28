#include"player.h"
#include"playerbullet.h"
#include"background.h"
#include"bomb.h"

CPlayer::CPlayer()
{
	//img = _img;

	img = LoadGraph("img\\player2.png");

	//チップサイズ
	ImgWidth = 38;
	ImgHeight = 40;

	//pos = _p;//描画位置

	//pos.x = WINDOW_WIDTH/2;
	//pos.y = 6000;

	hp = 30000;

	m_pos.x = WINDOW_WIDTH / 2;
	m_pos.y = /*6150;*/3000;

	pos = m_pos;

	//切り取り位置
	//16はマップチップ画像の横個数

	

	CutX =/* (_No 7 % 6)*/anime_flame * ImgWidth;
	CutY = anime_flame_t*ImgHeight;

	pri = 15;

	ID = PLAYER;

	player_state = STATE_IDLE;
	//tipNo = _No;

}

int CPlayer::Action(vector<unique_ptr<BaseVector>>& base) { 
	
	CutX =anime_flame * ImgWidth;
	CutY = anime_flame_t * ImgHeight;
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

	if (hp<0)
	{
		arrive_flag = false;
		player_state = STATE_DIE;
	}

	if (m_pos.x>=WINDOW_WIDTH-ImgWidth)
	{
		m_pos.x = WINDOW_WIDTH-ImgWidth;
	}
	if (m_pos.x<=0)
	{
		m_pos.x = 0;

	}

	if (!arrive_flag&&player_state==STATE_DIE&&!die_anime_flag)
	{
		anime_flame_t = 1;
		anime_flame = 0;
		die_anime_flag = true;

		if (g_BackGround)
			g_BackGround->stopScroll = true;

		//base.emplace_back((unique_ptr<BaseVector>)new CBomb(pos));
	}

	
	if (vec.x==0.0f&&arrive_flag==true)
	{
		player_state = STATE_IDLE;
	}
	else if (arrive_flag==true)
	{
		if (vec.x<0.0f||vec.x>0.0f)
		{
			player_state = STATE_FLY;
		}

		
	}

	switch (player_state)
	{
	case STATE_IDLE:
		if (anime_time < 0) 
		{
			if (anime_flame == 2)
			{
				anime_flame = 3;
			}
			else
			{
				anime_flame = 2;
			}
			anime_time = re_anime_time;
		}
		anime_time--;
		break;
	case STATE_FLY:
		if (anime_time < 0)
		{
			if (vec.x>0.0f)
			{
				if (anime_flame == 4)
				{
					anime_flame = 5;
				}
				else
				{
					anime_flame = 4;
				}
			}
			else if(vec.x<0.0f)
			{
				if (anime_flame == 0)
				{
					anime_flame = 1;
				}
				else
				{
					anime_flame = 0;
				}
			}

			
			anime_time = re_anime_time;
		}
		anime_time--;
		break;
	case STATE_DIE:
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "Die\nDie\nDie");
		
		if (anime_time<0&&anime_flame<5)
		{
			anime_flame++;
			anime_time = re_anime_time/2;
		}
		else if (anime_flame<5)
		{
			anime_time--;
		}
		
		break;

	default:
		break;
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
	DrawFormatString(pos.x-50, pos.y+50, GetColor(255, 255, 255), "%d", anime_time);
}

void CPlayer::Fire(vector<unique_ptr<BaseVector>>&base)
{
	//通常弾およびレーザー弾-----------------------------------------------------
	if (bullet_id == 0 || bullet_id == 1)
	{



		for (int i = 1; i <= bullet_num; i++)
		{
			if (bullet_num == 1)
			{
				base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y,rad,bullet_id));
			}
			else
			{
				if (bullet_num % 2 == 0)
				{
					if (i % 2 == 0)
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + (7-bullet_id*4) * (i - 1), pos.y, rad, bullet_id));
					}
					else
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - (7 - bullet_id * 4) * i, pos.y, rad, bullet_id));
					}
				}
				else
				{
					if (i == 1)
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y, rad, bullet_id));
					}
					else
					{
						if (i % 2 == 0)
						{
							base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + (7 - bullet_id * 4) * (i), pos.y, rad, bullet_id));
						}
						else
						{
							base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - (7 - bullet_id * 4) * (i - 1), pos.y, rad, bullet_id));
						}
					}



				}


			}



		}

		


	}
	//-------------------------------------------

	//拡散弾--------------------------------

	if (bullet_id==2)
	{
		int n = bullet_num+2;
		float spread = 20.0f;
		 rad = 3.14159265f / 180.0f;

		for (int i = 0; i < n; i++)
		{
			float t = (n == 1) ? 0.0f :
				-spread + (spread * 2.0f) * i / (float)(n - 1);

			float angle = -90.0f * rad + t * rad;

			base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y, angle, bullet_id));
		}
	}
	//-------------------------------------

	//十字弾--------

	if (bullet_id==3)
	{
		rad = 3.14159265f / 180.0f;

		// 基本の4方向（上・下・右・左）
		float dirList[4] = {
			-90.0f * rad,   // 上
			 90.0f * rad,   // 下
			  0.0f * rad,   // 右
			180.0f * rad    // 左
		};

		// 基本1発・残り extra を順に割り当てる
		int extra = bullet_num - 1;
		int count[4] = { 1, 1, 1, 1 };

		for (int i = 0; i < extra; i++)
		{
			count[i % 4]++;
		}

		// 各方向へ発射
		for (int d = 0; d < 4; d++)
		{
			int c = count[d];     // この方向の弾数
			float angle = dirList[d];

			// オフセット幅（調整可能）
			float offsetStep = 8.0f;

			for (int k = 0; k < c; k++)
			{
				// -n/2 ～ n/2 に広げる
				float t = (c == 1) ? 0.0f :
					(k - (c - 1) * 0.5f);

				float offX = 0.0f;
				float offY = 0.0f;

				// 方向ごとに「横方向」の軸を変える
				if (d == 0 || d == 1)  // 上・下 → x をずらす
				{
					offX = t * offsetStep;
				}
				else                  // 右・左 → y をずらす
				{ 
					offY = t * offsetStep;
				}

				base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + offX,pos.y + offY,angle, bullet_id));
			}
		}
	}



	//-----------------

	switch (bullet_id)
	{
	case 1:
		fire_cooldown = 2;
		break;

	default:
		fire_cooldown = 10;
		break;
	}



}