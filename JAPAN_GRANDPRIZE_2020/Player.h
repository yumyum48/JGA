#pragma once
#include "DxLib.h"
#include "Struct.h"

#define PLAYER_WIDTH	 (280 * PLAYER_REDUCTION)			// �v���C���[�̉���
#define PLAYER_HEIGHT	 (200 * PLAYER_REDUCTION)			// �v���C���[�̏c��

extern playerInfo g_player;									// �v���C���[�̏��

void PlayerDisp();											// �v���C���[�̕`��
void PlayerMove();											// �v���C���[�̓���
void PlayerInit();											// �v���C���[�̏�����
void PlayerJump();											// �v���C���[�̃W�����v����
void PlayerControl();										// �v���C���[�𑀍삷�鏈��
void EnemyLockOn();											// �v���C���[�̊ԍ����ɓ����Ă���G�����b�N�I��
bool PlayerInterval(int ex, int ey, int ew, int eh);		// �v���C���[�̉摜�ƓG�̉摜�̓����蔻�� (TRUE: �������� | FALSE: ������Ȃ�����)
bool PlayerHitCheck(int ex, int ey, int ew, int eh);		// �v���C���[�̌��̕����̔���𔲂��ɁA�v���C���[���g�̓����蔻��(��ɃG�l�~�[�Ƃ̏Փ˂Ɏg��)(��������:TRUE  �������Ă��Ȃ�����:FALSE)
void EnemyCut();											// �ԍ����ɓ����Ă���G��|������
void PlayerAfterimage(int anime);							// �v���C���[�̎c��


