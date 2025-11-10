#include"enemybase.h"
#include"function.h"
#include"enemybullet.h"
#include"item.h"

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
    // 敵→プレイヤー方向ベクトル
    Point dir;
    dir.x = targetPos.x - pos.x;
    dir.y = targetPos.y - pos.y;

    // 正規化
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
    {
        dir.x /= len;
        dir.y /= len;
    }

    // 弾生成
    base.emplace_back((unique_ptr<BaseVector>)new CEbullet(pos, dir));
    fire_cooldown = refire_cooldown;
}


void CEnemyBase::Die(vector<unique_ptr<BaseVector>>& base)
{
    if (item_drop)
    {
        //アイテムドロップ処理 
        ItemDrop(base,pos);


    }


    FLAG = false;
}

void CEnemyBase::ItemDrop(vector<unique_ptr<BaseVector>>& base,Point pos)
{
    base.emplace_back((unique_ptr<BaseVector>)new CItem(pos));


}