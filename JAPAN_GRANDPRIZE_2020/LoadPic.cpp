#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// プレイヤー画像の読み込み
	if (LoadDivGraph("image/player2.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	//UI画像
	if ((g_pic.PlayerUI = LoadGraph("image/Aicon2.png")) == -1) return -1;
	//Life画像
	if (LoadDivGraph("image/Life.png", 2, 2, 1, 100, 100, g_pic.Life, 0) == -1) return -1;

	//スキル3モーション(仮)
	if (LoadDivGraph("image/skill3.png", 5, 5, 1, 1443/5, 289, g_pic.skill, 0) == -1) return -1;

	// エネミー画像の読み込み
	if ((g_pic.enemy = LoadGraph("image/enemy.png")) == -1) return -1;

	/*//マップの読み込み
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// マップ読み込み
	if (LoadDivGraph("image/Stage1_main2.png", 4, 4, 1, 250, 400, g_pic.map, 0) == -1)
		return -1;
	// マップ背景読み込み
	if ((g_pic.backMap = LoadGraph("image/Stage1_Back2.png")) == -1) return -1;
	
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// 雨の画像の読み込み
	if ((g_pic.rain = LoadGraph("image/RainLarge.png")) == -1) return -1;

	// レティクル画像の読み込み
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;

	// ボス_１の画像読み込み
	if (LoadDivGraph("image/Boss_1.png", 8, 4, 4, 280, 200, g_pic.boss_1_1, 0) == -1)
		return -1;

	//// ボス_１の泡画像読み込み
	//if (LoadDivGraph("image/Boss1_Water.png", 8, 8, 0, 280, 200, g_pic.boss_1_2, 0) == -1)
	//	return -1;
	// セレクト画面の背景読み込み
	if ((g_pic.selectBack = LoadGraph("image/Select.png")) == -1) return -1;

	// 水弾の画像の読み込み
	if ((g_pic.waterBullet[0] = LoadGraph("image/watb00.png")) == -1) return -1;
	if ((g_pic.waterBullet[1] = LoadGraph("image/watb01.png")) == -1) return -1;
	if ((g_pic.waterBullet[2] = LoadGraph("image/watb02.png")) == -1) return -1;
	if ((g_pic.waterBullet[3] = LoadGraph("image/watb04.png")) == -1) return -1;


	return 0;
}