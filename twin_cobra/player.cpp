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
	//通常弾およびレーザー弾-----------------------------------------------------
	if (bullet_id == 0 || bullet_id == 1)
	{



		for (int i = 1; i <= bullet_num; i++)
		{
			if (bullet_num == 1)
			{
				base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y,rad));
			}
			else
			{
				if (bullet_num % 2 == 0)
				{
					if (i % 2 == 0)
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + (7-bullet_id*4) * (i - 1), pos.y, rad));
					}
					else
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - (7 - bullet_id * 4) * i, pos.y, rad));
					}
				}
				else
				{
					if (i == 1)
					{
						base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y, rad));
					}
					else
					{
						if (i % 2 == 0)
						{
							base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + (7 - bullet_id * 4) * (i), pos.y, rad));
						}
						else
						{
							base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x - (7 - bullet_id * 4) * (i - 1), pos.y, rad));
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

			base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x, pos.y, angle));
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

				base.emplace_back((unique_ptr<BaseVector>)new CPbullet(pos.x + offX,pos.y + offY,angle));
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