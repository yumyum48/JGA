#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"


#define G                (0.3F)		// �d��
#define JUMP_POWER       (6.0F)		// �W�����v��

image g_pic;
playerInfo g_player;
controler g_button;

int g_speed = 0;	//�����鑬�x

void PlayerDisp() {
	DrawGraph(63, 505 + g_player.y, g_pic.Kirby, TRUE);
}

void PlayerMove() {

	//float moveY = 0.0F;

	//�W�����v����(�~�{�^��)
	if (g_player.jumpFlg == FALSE && g_button.crossButton == true) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	if (g_player.jumpFlg == TRUE) {	//�W�����v��
		g_player.y += g_speed;
		g_speed += G;
	}
	
}