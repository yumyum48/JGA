#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"


#define G                (0.3F)		// �d��
#define JUMP_POWER       (6.0F)		// �W�����v��

playerInfo g_player;

int g_speed = 0;	//�����鑬�x

void PlayerDisp() {
	DrawGraph(63, 505 + g_player.y, g_pic.Kirby, TRUE);
}

void PlayerMove() {

	//float moveY = 0.0F;
	//g_player.jumpFlg = FALSE;

	//�W�����v����(�~�{�^��)
	if (g_player.jumpFlg == FALSE/* && g_button.crossButton == true*/) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;
	
}