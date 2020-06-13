#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "Boss.h"
#include "Select.h"
#include "Init.h"
#include "HP.h"
#include "Trap.h"

// �Q�[���v���C�̃��C���֐�
void GamePlay() {
	// �f�o�b�O�p�ň�U����ւ�GamePlayMove();
	GamePlayMove();
	GamePlayDisp();

	static int timecnt = 0;	// �t���[���P�ʂŉ��Z����
	if (timecnt++ >= 60) {
		g_playTime++;	// �v���C�^�C�������Z
		timecnt = 0;
	}
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();						// �}�b�v�̕`��
	MonsterDisp();					// �ア�G�A�{�X�̕\��
	
	PlayerDisp();					// �v���C���[�̕`��
	RainDisp();						// �J�̕`��

#ifndef DEBUG_TRAP_ON
	TrapDisp();						// �g���b�v�̕\��
#endif // DEBUG_TRAP_ON

	HpDisp();						// HP�\������
	
	LastBossRightNingAnime();		// ���X�{�X�O�̂V�̂̎ւ̏o���A�j���[�V����
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	MapMove();						// �}�b�v�̓���
	MonsterMove();					// �ア�G�A�{�X�̓���
	
	PlayerMove();					// �v���C���[�̓���
	RainMove();						// �J�̓���

#ifndef EBUG_TRAP_ON
	TrapMove();						// �g���b�v�̓���
#endif // EBUG_TRAP_ON
#ifdef DEBUG_LEVEL_OFF
	HpMove();						// HP�̌v�Z����
#endif // DEBUG_LEVEL_OFF
}



