#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"


#define G                (0.5F)		// �d��
#define JUMP_POWER       (15.0F)	// �W�����v��

playerInfo g_player;

float g_speed = 0.0F;	//�����鑬�x

int g_anime = 0;
int g_time = 0;

void PlayerDisp() {
	DrawGraph(g_player.x, g_player.y, g_pic.player[g_anime], TRUE);
	DrawFormatString(400, 0, 0xffffff, "%d", g_player.hp);
}

void PlayerMove() {

	if (++g_time % 8 == 0) g_anime++;
	if (g_anime > 2) g_anime = 0;

	//�W�����v����(�~�{�^��)
	if (g_player.jumpFlg == FALSE && g_button.crossButton == true) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;
	
	if (g_player.y >= 450) {
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
		g_player.y = 450;
	}

	//�U��(�Z�{�^��)
	if (g_player.attackFlg == FALSE && g_button.circleButton == true) {
		g_player.x += 500.0F;
		g_player.attackFlg = TRUE;
	}
	if (g_player.attackFlg == TRUE && g_player.x > 100) {
		g_player.x -= 10.0F;
	} else if(g_player.attackFlg == TRUE){
		g_player.attackFlg = FALSE;
	}

	//(���{�^��??)
	if (g_button.squareButton == true) {

	}

}

void PlayerInit() {
	g_player.Init();
}