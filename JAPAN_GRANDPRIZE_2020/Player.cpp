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

void PlayerDisp() {
	static int anime = 0;			// プレイヤーの画像を変える
	static int time = 0;			// 画像を切り替えるタイミング調整
	if (++time % 4 == 0) anime++;	
	if (anime > 7) anime = 0;
	DrawGraph(g_player.x, g_player.y, g_pic.player[anime], TRUE);
	DrawFormatString(400, 0, 0xffffff, "%d", g_player.hp);

	
}

void PlayerMove() {

	PlayerJump();		// プレイヤーのジャンプ処理	
	PlayerControl();	// プレイヤーを操作する関数
	

}

// ジャンプ処理
void PlayerJump() {
	//ジャンプ処理(×ボタン)
	if (g_player.jumpFlg == FALSE && g_button.crossButton == true) {
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
	if (g_player.attackFlg == FALSE && g_button.circleButton == true) {
		g_player.x += 500.0F;
		g_player.attackFlg = TRUE;
	}
	if (g_player.attackFlg == TRUE && g_player.x > 100) {
		g_player.x -= 10.0F;
	}
	else if (g_player.attackFlg == TRUE) {
		g_player.attackFlg = FALSE;
	}

	//(□ボタン??)
	if (g_button.squareButton == true) {

	}

	static int skill = 0;
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		skill = 1;
	}
	
	if (skill == 1) {
		EnemyLockOn();
		if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
			skill = 0;
		}
	}
	
}

// 敵を間合いに入ったらロックオンをする処理
void EnemyLockOn(){
	DrawBox(g_player.x + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, g_player.x + PLAYER_WIDTH + PLAYER_WIDTH, 10, 0xFF0000, 0);
	for (int i = 0; i < ENEMY_MAX; i++) {
		
		if( (g_enemy[i].walk.flg == TRUE)
		&&  (PicHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y) == 1) ){
			DrawBox(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT, 0xFF0000, 1);
			if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
				g_player.x = g_enemy[i].walk.x-PLAYER_WIDTH;
				g_enemy[i].walk.flg = FALSE;
			}
		}
	}
	
}

// プレイヤーの画像と敵の画像の当たり判定
int PicHitCheck(int ex, int ey) {

	if (( g_player.x + PLAYER_WIDTH <= ex + ENEMY_WIDTH)		// 敵のX座標が、プレイヤーのX座標内だったら真
		&& (g_player.x + PLAYER_WIDTH + PLAYER_WIDTH >= ex)
		&& (g_player.y <= ey + ENEMY_HEIGHT)		// 敵のY座標が、プレイヤーのY座標内だったら真
		&& (g_player.y + PLAYER_HEIGHT >= ey)) {
		return 1;
	}

	return 0;
}
// プレイヤーの初期化処理
void PlayerInit() {
	g_player.Init();
}