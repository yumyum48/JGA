#pragma once
#include "DxLib.h"
#include "Struct.h"

#define PLAYER_WIDTH	 (280 * PLAYER_REDUCTION)			// �v���C���[�̉���
#define PLAYER_HEIGHT	 (200 * PLAYER_REDUCTION)			// �v���C���[�̏c��

extern playerInfo g_player;									// �v���C���[�̏��

enum PlayerAnime {											// �v���C���[�̃A�j���[�V����
	CLOSE_MOVE_S = 0,			//�[�����:����(�J�n)
	CLOSE_MOVE_E = 7,			//�[�����:����(�I��)
	OPEN_MOVE_S = 8,			//�������:����(�J�n)
	OPEN_MOVE_E = 15,			//�������:����(�I��)
	CLOSE_JUMP_UP = 16,			//�[�����:�W�����v�㏸
	CLOSE_JUMP_DOWN_S = 17,		//�[�����:�W�����v���~(�J�n)
	CLOSE_JUMP_DOWN_E = 18,		//�[�����:�W�����v���~(�I��)
	OPEN_JUMP_UP = 24,			//�������:�W�����v�㏸
	OPEN_JUMP_DOWN_S = 25,		//�������:�W�����v���~(�J�n)
	OPEN_JUMP_DOWN_E = 26,		//�������:�W�����v���~(�I��)
	SWORD_OPEN_S = 32,			//�������[�V����(�J�n)
	SWORD_OPEN_E = 33,			//�������[�V����(�I��)
	SWORD_CLOSE_S = 40,			//�[�����[�V����(�J�n)
	SWORD_CLOSE_E = 41,			//�[�����[�V����(�I��)
	DAMAGE = 48					//�_���[�W
};

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
int  SkillChange();											// 
void PlayerAnimation();										// �v���C���[�̃A�j���[�V����

