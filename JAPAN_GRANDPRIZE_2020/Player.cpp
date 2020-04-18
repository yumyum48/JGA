#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"
#include "enemy.h"

#define G                (0.5F)		// 重力
#define JUMP_POWER       (15.0F)	// ジャンプ力

playerInfo g_player;

float g_speed = 0.0F;	//落ちる速度
int g_resetMotion = 0;	//アニメーション始点
int g_maxMotion = 7;	//終点
bool g_skillFlg;		// スキル中かどうかのフラグ

void PlayerDisp() {
	static int anime = 0;							// プレイヤーの画像を変える
	static int time = 0;							// 画像を切り替えるタイミング調整
	
	if (++time % 4 == 0) anime++;
	if (anime < g_resetMotion || anime > g_maxMotion) anime = g_resetMotion;

	// 残像
	PlayerAfterimage(anime);
	//プレイヤー
	DrawGraph(g_player.x, g_player.y, g_pic.player[anime], TRUE);
	DrawFormatString(400, 0, 0xffffff, "%d", g_player.hp);

	
}

void PlayerMove() {

	PlayerJump();		// プレイヤーのジャンプ処理	
	PlayerControl();	// プレイヤーを操作する関数
	

}

void PlayerAfterimage(int anime){
	static int resetMotion_Buf[3] = { 0, 0, 0 };		// マイフレームのプレイヤーのアニメーションを格納
	static int maxMotion_Buf[3] = { 0, 0, 0 };		// マイフレームのプレイヤーのアニメーションを格納
	if (g_skillFlg == TRUE) {
		int anime_Buf = anime - 1;					// 過去のプレイヤーアニメーションを格納する
		resetMotion_Buf[2] = resetMotion_Buf[1];
		resetMotion_Buf[1] = resetMotion_Buf[0];
		resetMotion_Buf[0] = g_resetMotion;

		maxMotion_Buf[2] = maxMotion_Buf[1];
		maxMotion_Buf[1] = maxMotion_Buf[0];
		maxMotion_Buf[0] = g_maxMotion;

		for (int i = 0; i < 3; i++) {
			if (anime_Buf < resetMotion_Buf[i] || anime_Buf > maxMotion_Buf[i]) anime_Buf = resetMotion_Buf[i];
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			// 残像プレイヤー表示
			DrawGraph(g_player.x - ((i + 1) * 30), g_player.y, g_pic.player[anime_Buf], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}
// ジャンプ処理
void PlayerJump() {
	//ジャンプ処理(×ボタン)
	if (g_player.jumpFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_2) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;

	if (g_player.y >= GROUND) {
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
		g_player.y = GROUND;
	}
}
// ボタンを押した時の処理
void PlayerControl() {
	//攻撃(〇ボタン)
	if (g_player.attackFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_3) {
		//g_player.x += 500.0F;
		g_player.attackFlg = TRUE;
	}
	if (g_player.attackFlg == TRUE && g_player.x > 100) {
		g_player.x -= 10.0F;
	}else if (g_player.attackFlg == TRUE) {
		g_player.attackFlg = FALSE;
	}

	//(□ボタン??)
	if (g_button.squareButton == true) {

	}



	// スキル中
	if (g_skillFlg == TRUE) {
		EnemyLockOn();
		
		if (g_player.jumpFlg == TRUE) {
			if (g_speed < 0) {
				g_resetMotion = 24;
				g_maxMotion = 24;
			} else {
				g_resetMotion = 25;
				g_maxMotion = 26;
			}
		}else {
			g_resetMotion = 8;
			g_maxMotion = 15;
		}
		// スキル状態解除処理
		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_skillFlg = FALSE;
		}
	} else if (g_skillFlg == FALSE) {

		if (g_player.jumpFlg == TRUE) {
			if (g_speed < 0) {
				g_resetMotion = 16;
				g_maxMotion = 16;
			}
			else {
				g_resetMotion = 17;
				g_maxMotion = 18;
			}
		}
		else {
			g_resetMotion = 0;
			g_maxMotion = 7;
		}
	}
	if (g_player.attackFlg == TRUE) {
		g_resetMotion = 32;
		g_maxMotion = 32;
	}

	// スキル状態オン
	if (g_keyInfo.keyFlg & PAD_INPUT_4) {
		g_skillFlg = TRUE;
	}
}

// 敵を間合いに入ったらロックオンをする処理
void EnemyLockOn(){
	DrawBox(g_player.x + PLAYER_WIDTH, g_player.y, g_player.x + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y+ PLAYER_HEIGHT, 0xFF0000, 0);
	EnemyCut();		// エネミーを倒す処理
}

// プレイヤーの間合いに入っている敵を倒す処理
void EnemyCut() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		// 歩く敵
		if( (g_enemy[i].walk.flg == TRUE)
		&&  (PicHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y) == 1) ){
			DrawBox(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT, 0xFF0000, 1);
			if(g_keyInfo.keyFlg & PAD_INPUT_3){
				g_player.x = g_enemy[i].walk.x-PLAYER_WIDTH;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].walk.WalkInit();
			}
		}
		// 飛んでいる敵
		if ((g_enemy[i].fly.flg == TRUE)
			&& (PicHitCheck(g_enemy[i].fly.x, g_enemy[i].fly.y) == 1)) {
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT, 0xFF0000, 1);
			if (g_keyInfo.keyFlg & PAD_INPUT_3) {
				g_player.x = g_enemy[i].fly.x - PLAYER_WIDTH;
				g_player.y = g_enemy[i].fly.y - PLAYER_HEIGHT;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].fly.WalkInit();
			}
		}
	}
}
// プレイヤーの画像と敵の画像の当たり判定
int PicHitCheck(int ex, int ey) {
	
	if (( (long int)g_player.x + (long int)PLAYER_WIDTH<= ex)		// 敵のX座標が、プレイヤーのX座標内だったら真
		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
		&& ((long int)g_player.y <= ey + ENEMY_HEIGHT)		// 敵のY座標が、プレイヤーのY座標内だったら真
		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
		return 1;
	}

	return 0;
}
// プレイヤーの初期化処理
void PlayerInit() {
	g_player.Init();
}