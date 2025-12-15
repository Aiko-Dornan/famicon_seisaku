#include"enemybase.h"
#include"function.h"
#include"enemybullet.h"
#include"itembase.h"
#include"player.h"

//CEnemyBase::CEnemyBase()
//{
//
//}

//void CEnemyBase::Fire(vector<unique_ptr<BaseVector>>&base)
//{
//	base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos));
//	
//	fire_cooldown = refire_cooldown;
//}

void CEnemyBase::Fire(std::vector<std::unique_ptr<BaseVector>>& base, Point targetPos)
{
    Point dir;
    float len;
    Point bulletDir;

    Point center;
    Point firePos;
    int dir2;
    static const Point GunOffset[8] =
    {
        {-10, -10}, {0, -14}, {10, -10}, {14, 0},
        {10, 10}, {0, 14}, {-10, 10}, {-14, 0}
    };

    static const Point DirVector[8] =
    {
        {-0.707f, -0.707f}, {0, -1}, {0.707f, -0.707f}, {1, 0},
        {0.707f, 0.707f}, {0, 1}, {-0.707f, 0.707f}, {-1, 0}
    };

    if (arrive_flag)
    {
        switch (enemyid)
        {
        case 0://通常弾

            
            center.x = pos.x + ImgWidth / 2;
            center.y = pos.y + ImgHeight / 2;

             dir2 = anime_flame;

            firePos.x = center.x + GunOffset[dir2].x;
            firePos.y = center.y + GunOffset[dir2].y;

            base.emplace_back(
                (unique_ptr<BaseVector>)new CEbullet(firePos, DirVector[dir2]));

            fire_cooldown = refire_cooldown;

            //// 敵→プレイヤー方向ベクトル

            //dir.x = (targetPos.x + 15) - pos.x;
            //dir.y = (targetPos.y + 20) - pos.y;

            //// 正規化
            //len = sqrtf(dir.x * dir.x + dir.y * dir.y);
            //if (len != 0)
            //{
            //    dir.x /= len;
            //    dir.y /= len;
            //}
            //Point firePos;
            //firePos.x = pos.x + ImgWidth / 2;
            //firePos.y = pos.y + ImgHeight / 2;
            //// 弾生成
            //base.emplace_back((unique_ptr<BaseVector>)new CEbullet(firePos, dir));
            break;
        case 1://正面に拡散弾
        {
            // 弾の基本方向（例: 右方向に飛ばす）
            Point dir;
            dir.x = 0.0f; // x方向の速度
            dir.y = 1.0f; // y方向の速度

            // 拡散角度（ラジアン）
            float spreadAngle = 0.2f; // ±0.2ラジアン（約11.5度）
            float angles[3] = { -spreadAngle, 0.0f, spreadAngle };

            for (int i = 0; i < 3; i++)
            {
                float cosA = cosf(angles[i]);
                float sinA = sinf(angles[i]);


                bulletDir.x = dir.x * cosA - dir.y * sinA;
                bulletDir.y = dir.x * sinA + dir.y * cosA;

                base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos, bulletDir));
            }
            break;
        }
        case 2://ボス
        {
            dir.x = (targetPos.x + 15) - pos.x;
            dir.y = (targetPos.y + 20) - pos.y;

            // 正規化
            len = sqrtf(dir.x * dir.x + dir.y * dir.y);
            if (len != 0)
            {
                dir.x /= len;
                dir.y /= len;
            }

            // 拡散角度 (ラジアン)
            float spreadAngle = 0.2f; // ±0.2ラジアン（約11.5度）
            float angles[3] = { -spreadAngle, 0.0f, spreadAngle };

            for (int i = 0; i < 3; i++)
            {
                float cosA = cosf(angles[i]);
                float sinA = sinf(angles[i]);


                bulletDir.x = dir.x * cosA - dir.y * sinA;
                bulletDir.y = dir.x * sinA + dir.y * cosA;

                base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos, bulletDir));
            }

            break;
        }
        default:
            break;
        }


        fire_cooldown = refire_cooldown;
    }

    
}


void CEnemyBase::Die(vector<unique_ptr<BaseVector>>& base)
{
    vec.x = 0.0f;
    vec.y = 0.0f;

    if (break_flag)
    {
        situation = BREAK;
    }
    else
    {
        situation = DIE;
        if (anime_flame >= 4)
            FLAG = false;
    }

   
    
    arrive_flag = false;
    if (!arrive_flag && /*situation == DIE &&*/ !die_anime_flag)
    {
        anime_flame_t = 2;
        anime_flame = 0;
        die_anime_flag = true;

        if (item_drop)
        {
            //アイテムドロップ処理 
            ItemDrop(base, pos);


        }
        else
        {
            if (GetRand(100) < 20)
            {
                //アイテムドロップ処理 
                ItemDrop(base, pos);
            }
        }
        
    }

    

    
}

void CEnemyBase::ItemDrop(vector<unique_ptr<BaseVector>>& base,Point pos)
{
    base.emplace_back((unique_ptr<BaseVector>)new CItemBase(pos));
    
    

}

void  CEnemyBase::Animetion(vector<unique_ptr<BaseVector>>& base)
{
    if (situation!=DAMEGED)
    {
        vault_situation = situation;
    }

    switch (situation)
    {
       
    case IDLE:
        if (arrive_flag == true)
        {
            if (anime_time < 0)
            {
                if (anime_flame == 0)
                {
                    anime_flame = 1;
                }
                else
                {
                    anime_flame = 0;
                }
                anime_time = re_anime_time;
            }
            anime_time--;
        }
        break;
    case ROTATE:
        if (arrive_flag == true)
        {
            CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
            if (!p) break;

            float dx = p->m_pos.x - pos.x;
            float dy = p->m_pos.y - pos.y;

            float angle = atan2f(dy, dx);
            if (angle < 0) angle += DX_PI_F * 2.0f;

            int dir8 = (int)((angle + DX_PI_F / 8) / (DX_PI_F * 2) * 8) % 8;

            static const int DirToImg[8] =
            {
                3, // 右
                4, // 右下
                5, // 下
                6, // 左下
                7, // 左
                0, // 左上
                1, // 上
                2  // 右上
            };

            anime_flame = DirToImg[dir8];
            anime_flame_t = 0;
        }
        break;

    case DAMEGED:
        if (arrive_flag == true)
        {
            anime_flame_t = 1;

            if (anime_time < 0)
            {
                anime_flame_t = 0;
                situation = vault_situation;
                anime_time = re_anime_time;
            }
            else
            {
                anime_time--;
            }
        }
        break;

        
    case DIE:
        DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "Die\nDie\nDie");

        if (anime_time < 0 && anime_flame < 5)
        {
            anime_flame++;
            anime_time = re_anime_time / 2;
        }
        else if (anime_flame < 5)
        {
            anime_time--;
        }

        break;
    case BREAK:
        
        if (anime_time < 0 && anime_flame < 4)
        {
            anime_flame++;
            anime_time = re_anime_time / 2;
        }
        else if (anime_flame < 4)
        {
            anime_time--;
        }
        break;

    default:
        break;
    }


}