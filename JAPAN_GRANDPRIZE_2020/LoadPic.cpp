#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// プレイヤー画像の読み込み
	if (LoadDivGraph("image/player2.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	// エネミー画像の読み込み
	if ((g_pic.enemy = LoadGraph("image/enemy.png")) == -1) return -1;

	/*//マップの読み込み
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// マップ読み込み
	if (LoadDivGraph("image/Stage1_main.png", 4, 4, 1, 250, 400, g_pic.map, 0) == -1)
		return -1;
	// マップ背景読み込み
	if ((g_pic.backMap = LoadGraph("image/Stage1_Back.png")) == -1) return -1;
	
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// 雨の画像の読み込み
	if ((g_pic.rain[0] = LoadGraph("image/RainLarge.png")) == -1) return -1;
	// 雨の画像の読み込み
	if ((g_pic.rain[1] = LoadGraph("image/RainLarge.png")) == -1) return -1;

	// レティクル画像の読み込み
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;
	return 0;
}