#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// タイトル画像
	if ((g_pic.title[0] = LoadGraph("image/titleimage5a.png")) == -1) return -1;

	// タイトルのテキスト画像
	if ((g_pic.titleText[0] = LoadGraph("image/Title_Text2.png")) == -1) return -1;		// タイトルロゴ
	if ((g_pic.titleText[1] = LoadGraph("image/NewGame.png")) == -1) return -1;			// タイトルロゴ
	if ((g_pic.titleText[2] = LoadGraph("image/Continue.png")) == -1) return -1;		// タイトルロゴ
	if ((g_pic.titleText[3] = LoadGraph("image/fin.png")) == -1) return -1;		// タイトルロゴ
	
	

	// プレイヤー画像の読み込み
	if (LoadDivGraph("image/player2.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	//スキルモーション画像
	if (LoadDivGraph("image/Skill_player.png", 9, 3, 3, 280, 200, g_pic.SkillMotion, 0) == -1) return -1;
	//UI画像
	if ((g_pic.PlayerUI = LoadGraph("image/Aicon2.png")) == -1) return -1;
	//Life画像
	if (LoadDivGraph("image/Life.png", 2, 2, 1, 100, 100, g_pic.Life, 0) == -1) return -1;

	//ゲージ画像
	if ((g_pic.gauge = LoadGraph("image/AiconGauge.png")) == -1) return -1;

	//スキル2モーション(仮)
	if (LoadDivGraph("image/skill2.png", 4, 4, 1, 200, 200, g_pic.skill2, 0) == -1) return -1;
	//スキル3モーション(仮)
	if (LoadDivGraph("image/skill3.png", 5, 5, 1, 1443/5, 289, g_pic.skill3, 0) == -1) return -1;

	// 歩く雑魚敵画像の読み込み
	if ((g_pic.enemy_walk[0] = LoadGraph("image/enemy.png")) == -1) return -1;

	// 飛ぶ雑魚敵画像の読み込み
	if (LoadDivGraph("image/skill3.png", 2, 2, 1, 1443 / 5, 289, g_pic.enemy_fly, 0) == -1) return -1;
	/*//マップの読み込み
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// マップ読み込み
	if (LoadDivGraph("image/Stage1_main2.png", 4, 4, 1, 250, 400, g_pic.map, 0) == -1)
		return -1;
	//// マップ背景読み込み
	//if ((g_pic.backMap = LoadGraph("image/Stage1_Back2.png")) == -1) return -1;
	
		// マップ背景読み込み
	if (LoadDivGraph("image/Stage1_Back2.png", 4, 4, 1, 250, 400, g_pic.backMap, 0) == -1)
		return -1;
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// 雨の画像の読み込み
	if ((g_pic.rain = LoadGraph("image/RainLarge.png")) == -1) return -1;

	if ((g_pic.trap = LoadGraph("image/toge.png")) == -1) return -1;
	// レティクル画像の読み込み
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;

	// ボス_１の画像読み込み
	if (LoadDivGraph("image/Boss_1.png", 16, 8, 2, 280, 200, g_pic.boss_1_1, 0) == -1)
		return -1;

	//// ボス_１の泡画像読み込み
	//if (LoadDivGraph("image/Boss1_Water.png", 8, 8, 0, 280, 200, g_pic.boss_1_2, 0) == -1)
	//	return -1;
	// セレクト画面の背景読み込み
	if ((g_pic.selectBack = LoadGraph("image/Select.png")) == -1) return -1;

	// 水弾の画像の読み込み
	if (LoadDivGraph("image/watb1.png", 5, 5, 1, 32, 32, g_pic.waterBullet, 0) == -1);

	// 敵撃破時の水しぶき
	if (LoadDivGraph("image/bassha.png", 5, 5, 1, 100, 100, g_pic.enemySplashes, 0) == -1);
	// 敵撃破時の蒸気
	if (LoadDivGraph("image/moku1.png", 5, 5, 1, 100, 100, g_pic.enemyVapour, 0) == -1);


	return 0;
}