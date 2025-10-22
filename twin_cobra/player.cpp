#include"player.h"

CPlayer::CPlayer()
{
	//img = _img;

	img = LoadGraph("img\\player.png");

	//チップサイズ
	ImgWidth = 30;
	ImgHeight = 40;

	//pos = _p;//描画位置

	pos.x = 100;
	pos.y = 100;

	//切り取り位置
	//16はマップチップ画像の横個数

	CutX = (/*_No*/ 7% 6) * ImgWidth;
	CutY = (/*_No*/ 7/ 5) * ImgHeight;

	pri = 10;

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

	pos.x += vec.x;
	pos.y += vec.y;
	
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



}