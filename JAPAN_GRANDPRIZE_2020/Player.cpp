#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "HP.h"

#define G                (0.5F)		// �d��
#define JUMP_POWER       (15.0F)	// �W�����v��



float g_speed = 0.0F;	//�����鑬�x
int g_resetMotion = 0;	//�A�j���[�V�����n�_
int g_maxMotion = 7;	//�I�_
int g_attackTime = 0;	//�U���̃N�[���^�C��
bool g_skillFlg;		// �X�L�������ǂ����̃t���O

void PlayerDisp() {
	static int anime = 0;							// �v���C���[�̉摜��ς���
	static int time = 0;							// �摜��؂�ւ���^�C�~���O����

	if (++time % 4 == 0) anime++;
	if (anime < g_resetMotion || anime > g_maxMotion) anime = g_resetMotion;

	// �c��
	PlayerAfterimage(anime);
	//�v���C���[
	DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime], TRUE);
	DrawFormatString(500, 0, 0xff0000, "%d", g_attackTime);
	DrawFormatString(600, 0, 0xffffff, "%d", g_boss[0].hp);

	
}

void PlayerMove() {

	PlayerJump();		// �v���C���[�̃W�����v����	
	PlayerControl();	// �v���C���[�𑀍삷��֐�


}

void PlayerAfterimage(int anime) {
	static int resetMotion_Buf[3] = { 0, 0, 0 };		// �}�C�t���[���̃v���C���[�̃A�j���[�V�������i�[
	static int maxMotion_Buf[3] = { 0, 0, 0 };		// �}�C�t���[���̃v���C���[�̃A�j���[�V�������i�[
	if (g_skillFlg == TRUE) {
		int anime_Buf = anime - 1;					// �ߋ��̃v���C���[�A�j���[�V�������i�[����
		resetMotion_Buf[2] = resetMotion_Buf[1];
		resetMotion_Buf[1] = resetMotion_Buf[0];
		resetMotion_Buf[0] = g_resetMotion;

		maxMotion_Buf[2] = maxMotion_Buf[1];
		maxMotion_Buf[1] = maxMotion_Buf[0];
		maxMotion_Buf[0] = g_maxMotion;

		for (int i = 0; i < 3; i++) {
			if (anime_Buf < resetMotion_Buf[i] || anime_Buf > maxMotion_Buf[i]) anime_Buf = resetMotion_Buf[i];
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			// �c���v���C���[�\��
			DrawGraph(g_player.x - ((i + 1) * 30), g_player.y, g_pic.player[anime_Buf], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}
// �W�����v����
void PlayerJump() {
	//�W�����v����(�~�{�^��)
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
// �{�^�������������̏���
void PlayerControl() {
	//�U��(�Z�{�^��)
	//if (g_player.attackFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if ((g_player.attackFlg == FALSE && g_skillFlg == TRUE) && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if(g_skillFlg == TRUE){
		//g_player.x += 500.0F;
		//g_player.attackFlg = TRUE;
	//}
	if (g_player.attackFlg == TRUE) {
		g_attackTime++;
	}
	if (g_attackTime > 20) {
		g_attackTime = 0;
		g_player.attackFlg = FALSE;
	}
	if (g_player.x > 100 && g_player.attackFlg == FALSE) {
		g_player.x -= 10.0F;
	}

	if (g_player.x < 100) g_player.x = 100;


	//�ʏ�U��
	if (g_skillFlg == FALSE && (g_keyInfo.keyFlg & PAD_INPUT_3)) {
		//g_player.attackFlg = TRUE;
		EnemyCut();		// �G�l�~�[��|������
	}


	//(���{�^��??)
	if (g_button.squareButton == true) {

	}



	// �X�L����
	if (g_skillFlg == TRUE) {
		EnemyLockOn();

		//�A�j���[�V����
		if (g_player.jumpFlg == TRUE) {
			if (g_speed < 0) {
				g_resetMotion = 24;
				g_maxMotion = 24;
			} else {
				g_resetMotion = 25;
				g_maxMotion = 26;
			}
		} else {
			g_resetMotion = 8;
			g_maxMotion = 15;
		}
		if (g_player.attackFlg == TRUE) {//�X�L���U��
			g_resetMotion = 32;
			g_maxMotion = 32;
		}

		// �X�L����ԉ�������
		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_skillFlg = FALSE;
		}
	}else if (g_skillFlg == FALSE) {

		if (g_player.jumpFlg == TRUE) {
			if (g_speed < 0) {
				g_resetMotion = 16;
				g_maxMotion = 16;
			}
			else {
				g_resetMotion = 17;
				g_maxMotion = 18;
			}
		}else {
			g_resetMotion = 0;
			g_maxMotion = 7;
		}
		if (g_player.attackFlg == TRUE) {//�ʏ�U��
			g_resetMotion = 40;
			g_maxMotion = 40;
		}
		// �X�L����ԃI��
		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_skillFlg = TRUE;
		}
	}

	
}

// �G���ԍ����ɓ������烍�b�N�I�������鏈��
void EnemyLockOn() {
	DrawBox(g_player.x + PLAYER_WIDTH, g_player.y, g_player.x + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0xFF0000, 0);
	EnemyCut();		// �G�l�~�[��|������
}

// �v���C���[�̊ԍ����ɓ����Ă���G��|������
void EnemyCut() {

	for (int i = 0; i < ENEMY_MAX; i++) {
		// �����G
		if ((g_enemy[i].walk.flg == TRUE)
			&& (PlayerInterval(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].walk.x + (ENEMY_WIDTH / 3), g_enemy[i].walk.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_keyInfo.keyFlg & PAD_INPUT_3) {
				if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].walk.WalkInit();
				g_player.attackFlg = TRUE;
			}
		}
		// ���ł���G
		if ((g_enemy[i].fly.flg == TRUE)
			&& (PlayerInterval(g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].fly.x + (ENEMY_WIDTH / 3), g_enemy[i].fly.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_keyInfo.keyFlg & PAD_INPUT_3) {
				if (g_skillFlg == TRUE) g_player.x = g_enemy[i].fly.x - PLAYER_WIDTH;
				g_player.y = g_enemy[i].fly.y - PLAYER_HEIGHT;
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].fly.WalkInit();
				g_player.attackFlg = TRUE;
			}
		}
	}
	//boss
	if (g_enemybeat > 10) {
		if (PlayerInterval(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == TRUE) {
			if (g_boss[0].hp > 0) {
				if (g_keyInfo.keyFlg & PAD_INPUT_3) {
					if (g_skillFlg == TRUE) g_player.x = g_boss[0].x - PLAYER_WIDTH;
					g_boss[0].hp--;
					
					g_player.attackFlg = TRUE;
				}
			}
		}
	}

}
// �v���C���[�̉摜�ƓG�̉摜�̓����蔻�� (TRUE: �������� | FALSE: ������Ȃ�����)
bool PlayerInterval(int ex, int ey, int ew, int eh) {

	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
		&& ((long int)g_player.y <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
		return TRUE;
	}

	return FALSE;
}

// �v���C���[�̌��̕����̔���𔲂��ɁA�v���C���[���g�̓����蔻��(��ɃG�l�~�[�Ƃ̏Փ˂Ɏg��)(��������:TRUE  �������Ă��Ȃ�����:FALSE)
bool PlayerHitCheck(int ex, int ey, int ew, int eh) {
	if( (g_player.x  <= ex + ew)
	&&	(g_player.x + (PLAYER_WIDTH / 2) >= ex)
	&&	(g_player.y  <= ey + eh)
	&&	(g_player.y + (PLAYER_HEIGHT / 2) >= ey) ){
		
		return TRUE;
	}

	return FALSE;
}
// �v���C���[�̏���������
void PlayerInit() {
	g_player.Init();
}