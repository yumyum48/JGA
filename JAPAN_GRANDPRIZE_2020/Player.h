#pragma once
#include "DxLib.h"
#define PLAYER_WIDTH	 (280)			// �v���C���[�̉���
#define PLAYER_HEIGHT	 (200)			// �v���C���[�̏c��

extern playerInfo g_player;				// �v���C���[�̏��

void PlayerDisp();						// �v���C���[�̕`��
void PlayerMove();						// �v���C���[�̓���
void PlayerInit();						// �v���C���[�̏�����
void PlayerJump();						// �v���C���[�̃W�����v����
void PlayerControl();					// �v���C���[�𑀍삷�鏈��
void EnemyLockOn();						// �v���C���[�̊ԍ����ɓ����Ă���G�����b�N�I��
int PicHitCheck(int ex, int ey, int ew, int eh);		// �v���C���[�ƓG�̔�����m�F���鏈��
void EnemyCut();						// �ԍ����ɓ����Ă���G��|������
void PlayerAfterimage(int anime);		// �v���C���[�̎c��


