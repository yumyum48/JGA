#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"


#define G                (0.3F)		// 重力
#define JUMP_POWER       (6.0F)		// ジャンプ力

playerInfo g_player;

float g_speed = 0.0F;	//落ちる速度

void PlayerDisp() {
	DrawFormatString(0, 100, 0xffff00, "Flg = %d", g_button.circleButton);
	DrawGraph(63, 505 + g_player.y, g_pic.Kirby, TRUE);
}

void PlayerMove() {

	//float moveY = 0.0F;

	//ジャンプ処理(×ボタン)
	if (g_player.jumpFlg == FALSE && g_button.crossButton == true) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;
	
	if (g_player.y == 0) {
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
	}

	/*
	if (g_button.moveStick == 2
		|| g_button.moveStick == 3
		|| g_button.moveStick == 4) {
		g_player.x += 1.0F;
	}
	if (g_button.moveStick == 6
		|| g_button.moveStick == 7
		|| g_button.moveStick == 8) {
		g_player.x -= 1.0F;
	}*/
	
}