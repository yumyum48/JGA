#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"


#define G                (0.5F)		// �d��
#define JUMP_POWER       (15.0F)		// �W�����v��

playerInfo g_player;

float g_speed = 0.0F;	//�����鑬�x

void PlayerDisp() {
	DrawGraph(g_player.x, g_player.y, g_pic.player, TRUE);
}

void PlayerMove() {

	//���E�ړ�
	if (g_button.moveStick == 2
		|| g_button.moveStick == 3
		|| g_button.moveStick == 4) {
		g_player.x += 8.0F;
	}
	if (g_button.moveStick == 6
		|| g_button.moveStick == 7
		|| g_button.moveStick == 8) {
		if (g_player.x > 0)g_player.x -= 1.0F;
	}

	if (g_player.x > 0) g_player.x -= 5.0F;


	//�W�����v����(�~�{�^��)
	if (g_player.jumpFlg == FALSE && g_button.crossButton == true) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;
	
	if (g_player.y == 450) {
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
	}

	//�U��(�Z�{�^��)
	if (g_button.circleButton == true) {

	}

	//(���{�^��??)
	if (g_button.squareButton == true) {

	}

}

void PlayerInit() {
	g_player.Init();
}