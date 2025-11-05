#pragma once
#include"background.h"
#include "player.h"
#include"function.h"
#include"playerbullet.h"

CBackGround::CBackGround()
{
    img = LoadGraph("LoadMap\\NES - Twin Cobra - Maps - Stage 01.png");

    // マップサイズ
    ImgWidth = 388;
    ImgHeight = 6311;

    camera.x = WINDOW_WIDTH / 2;
    camera.y = ImgHeight - WINDOW_HEIGHT / 2; // 最初は一番下から開始

    tipNo = 1;
}

int CBackGround::Action(vector<unique_ptr<BaseVector>>& base)
{
    CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);

    // 強制スクロール
    float prevCameraY = camera.y;
    camera.y -= scrollspeed;

    // カメラ上限制御
    if (camera.y < WINDOW_HEIGHT / 2)
        camera.y = WINDOW_HEIGHT / 2;

    float cameraMove = camera.y - prevCameraY; // カメラの移動量（通常は負の値）

    // --- プレイヤー操作処理 ---
    p->m_pos.x += p->vec.x;
    p->m_pos.y += p->vec.y;

    // 入力がない（つまりvecがゼロ）の場合は、スクロールに合わせて移動させる
    if (p->vec.x == 0.0f && p->vec.y == 0.0f) {
        p->m_pos.y += cameraMove; // カメラ移動と同じだけ動かす（相対位置維持）
    }

    // プレイヤーの画面内制限
    if (p->m_pos.x < camera.x - WINDOW_WIDTH / 2 + p->ImgWidth / 2)
        p->m_pos.x = camera.x - WINDOW_WIDTH / 2 + p->ImgWidth / 2;

    if (p->m_pos.x > camera.x + WINDOW_WIDTH / 2 - p->ImgWidth / 2)
        p->m_pos.x = camera.x + WINDOW_WIDTH / 2 - p->ImgWidth / 2;

    if (p->m_pos.y < camera.y - WINDOW_HEIGHT / 2 + p->ImgHeight / 2)
        p->m_pos.y = camera.y - WINDOW_HEIGHT / 2 + p->ImgHeight / 2;

    if (p->m_pos.y > camera.y + WINDOW_HEIGHT / 2 - p->ImgHeight / 2)
        p->m_pos.y = camera.y + WINDOW_HEIGHT / 2 - p->ImgHeight / 2;

    // 描画用座標計算
    p->pos.x = p->m_pos.x - camera.x + WINDOW_WIDTH / 2;
    p->pos.y = p->m_pos.y - camera.y + WINDOW_HEIGHT / 2;

    // 背景の描画位置
    pos.x = WINDOW_WIDTH / 2 - camera.x;
    pos.y = WINDOW_HEIGHT / 2 - camera.y;

    // vecリセット
    p->vec = { 0.0f, 0.0f };

    return 0;
}


//int CBackGround::Action(vector<unique_ptr<BaseVector>>& base)
//{
//    CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
//
//    // 強制スクロール
//    camera.y -= scrollspeed;
//
//    // カメラが上限を超えないように
//    if (camera.y < WINDOW_HEIGHT / 2)
//        camera.y = WINDOW_HEIGHT / 2;
//
//    // 背景の描画位置を更新
//    pos.x = WINDOW_WIDTH / 2 - camera.x;
//    pos.y = WINDOW_HEIGHT / 2 - camera.y;
//
//    // プレイヤーの「ワールド上の位置」更新（マップ全体での座標）
//    p->m_pos.x += p->vec.x;
//    p->m_pos.y += p->vec.y;
//
//    // プレイヤーが画面外に出ないように制限
//    if (p->m_pos.x < camera.x - WINDOW_WIDTH / 2 + p->ImgWidth / 2)
//        p->m_pos.x = camera.x - WINDOW_WIDTH / 2 + p->ImgWidth / 2;
//
//    if (p->m_pos.x > camera.x + WINDOW_WIDTH / 2 - p->ImgWidth / 2)
//        p->m_pos.x = camera.x + WINDOW_WIDTH / 2 - p->ImgWidth / 2;
//
//    if (p->m_pos.y < camera.y - WINDOW_HEIGHT / 2 + p->ImgHeight / 2)
//        p->m_pos.y = camera.y - WINDOW_HEIGHT / 2 + p->ImgHeight / 2;
//
//    if (p->m_pos.y > camera.y + WINDOW_HEIGHT / 2 - p->ImgHeight / 2)
//        p->m_pos.y = camera.y + WINDOW_HEIGHT / 2 - p->ImgHeight / 2;
//
//    // 画面上での描画座標（カメラ基準）
//    p->pos.x = p->m_pos.x - camera.x + WINDOW_WIDTH / 2;
//    p->pos.y = p->m_pos.y - camera.y + WINDOW_HEIGHT / 2;
//
//    // vecリセット
//    p->vec = { 0.0f, 0.0f };
//
//    return 0;
//}

void CBackGround::Draw()
{
    DrawGraph(pos.x, pos.y, img, true);

   
}

//CBackGround::CBackGround()
//{
//	img = LoadGraph("LoadMap\\NES - Twin Cobra - Maps - Stage 01.png");
//
//	//マップサイズ
//	ImgWidth = 388;
//	ImgHeight = 6311;
//
//}
//
//int CBackGround::Action(vector<unique_ptr<BaseVector>>& base)
//{
//	//プレイヤーの情報取得
//	CPlayer* p = (CPlayer*)Get_obj(base, PLAYER);
//
//	//カメラ座標をプレイヤーの位置へ
//	camera = p->m_pos;
//
//	//カメラがマップから出ないようにする
//	if (camera.x < WINDOW_WIDTH / 2)
//	{
//		camera.x = WINDOW_WIDTH / 2;//左
//
//	}
//	if (camera.x > ImgWidth - WINDOW_WIDTH / 2)
//	{
//		camera.x = ImgWidth - WINDOW_WIDTH / 2;//右
//	}
//
//
//
//	if (camera.y < WINDOW_HEIGHT / 2)
//	{
//		camera.y = WINDOW_HEIGHT / 2;//上
//
//	}
//	if (camera.y > ImgHeight - WINDOW_HEIGHT / 2)
//	{
//		camera.y = ImgHeight - WINDOW_HEIGHT / 2;//下
//	}
//
//
//	//プレイヤーの描画位置
//	p->pos.x = p->m_pos.x - camera.x + WINDOW_WIDTH / 2;
//	p->pos.y = p->m_pos.y - camera.y + WINDOW_HEIGHT / 2;
//
//	//背景の描画位置
//	pos.x = WINDOW_WIDTH / 2 - camera.x;
//	pos.y = WINDOW_HEIGHT / 2 - camera.y;
//
//	p->m_pos.y -= scrollspeed;
//
//	return 0;
//}
//
//void CBackGround::Draw()
//{
//	DrawGraph(pos.x, pos.y, img, true);
//}