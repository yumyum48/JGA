#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"
#include "enemy.h"

#define G                (0.5F)		// �d��
#define JUMP_POWER       (15.0F)	// �W�����v��

playerInfo g_player;

float g_speed = 0.0F;	//�����鑬�x

void PlayerDisp() {
	static int anime = 0;			// �v���C���[�̉摜��ς���
	static int time = 0;			// �摜��؂�ւ���^�C�~���O����
	if (++time % 4 == 0) anime++;	
	if (anime > 7) anime = 0;
	DrawGraph(g_player.x, g_player.y, g_pic.player[anime], TRUE);
	DrawFormatString(400, 0, 0xffffff, "%d", g_player.hp);

	
}

void PlayerMove() {

	PlayerJump();		// �v���C���[�̃W�����v����	
	PlayerControl();	// �v���C���[�𑀍삷��֐�
	

}

// �W�����v����
void PlayerJump() {
	//�W�����v����(�~�{�^��)
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
// �{�^�������������̏���
void PlayerControl() {
	//�U��(�Z�{�^��)
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

	//(���{�^��??)
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

// �G���ԍ����ɓ������烍�b�N�I�������鏈��
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

// �v���C���[�̉摜�ƓG�̉摜�̓����蔻��
int PicHitCheck(int ex, int ey) {

	if (( g_player.x + PLAYER_WIDTH <= ex + ENEMY_WIDTH)		// �G��X���W���A�v���C���[��X���W����������^
		&& (g_player.x + PLAYER_WIDTH + PLAYER_WIDTH >= ex)
		&& (g_player.y <= ey + ENEMY_HEIGHT)		// �G��Y���W���A�v���C���[��Y���W����������^
		&& (g_player.y + PLAYER_HEIGHT >= ey)) {
		return 1;
	}

	return 0;
}
// �v���C���[�̏���������
void PlayerInit() {
	g_player.Init();
}