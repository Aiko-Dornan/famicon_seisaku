#include"enemybase.h"
#include"function.h"
#include"enemybullet.h"
#include"itembase.h"

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

    switch (enemyid)
    {
    case 0:
        // 敵→プレイヤー方向ベクトル
       
        dir.x = (targetPos.x + 15) - pos.x;
        dir.y = (targetPos.y + 20) - pos.y;

        // 正規化
        len = sqrtf(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
        {
            dir.x /= len;
            dir.y /= len;
        }

        // 弾生成
        base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos, dir));
    break;
    case 1:
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
    case 2:
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


void CEnemyBase::Die(vector<unique_ptr<BaseVector>>& base)
{
    if (item_drop)
    {
        //アイテムドロップ処理 
        ItemDrop(base,pos);


    }
    else
    {
        if (GetRand(100)<20)
        {
            //アイテムドロップ処理 
            ItemDrop(base, pos);
        }
    }


    FLAG = false;
}

void CEnemyBase::ItemDrop(vector<unique_ptr<BaseVector>>& base,Point pos)
{
    base.emplace_back((unique_ptr<BaseVector>)new CItemBase(pos));
    
    

}