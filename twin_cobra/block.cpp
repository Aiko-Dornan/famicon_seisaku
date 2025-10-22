#pragma once
#include"block.h"

CBlock::CBlock(Point _p, int _No, int _img)
{
	img = _img;

	//チップサイズ
	ImgWidth = 96;
	ImgHeight = 96;

	pos = _p;//描画位置

	//切り取り位置
	//16はマップチップ画像の横個数

	CutX = (_No % 12) * ImgWidth;
	CutY = (_No / 12) * ImgHeight;

	pri = 0;

	tipNo = _No;

}

int CBlock::Action(vector<unique_ptr<BaseVector>>& base) { return 0; }

void CBlock::Draw()
{
	DrawRectGraph(
		pos.x, pos.y,
		CutX, CutY,
		ImgWidth, ImgHeight,
		img, true
	);



}