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
	GamePlayDisp();
	GamePlayMove();
	static int timecnt;	// �t���[���P�ʂŉ��Z����
	if(timecnt++ >= 60)g_playTime++;	// �v���C�^�C�������Z
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();						// �}�b�v�̕`��
	MonsterDisp();					// �ア�G�A�{�X�̕\��
	
	PlayerDisp();					// �v���C���[�̕`��
	RainDisp();						// �J�̕`��
	TrapDisp();						// �g���b�v�̕\��
	HpDisp();						// HP�\������
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	MapMove();						// �}�b�v�̓���
	MonsterMove();					// �ア�G�A�{�X�̓���
	
	PlayerMove();					// �v���C���[�̓���
	RainMove();						// �J�̓���
	TrapMove();						// �g���b�v�̓���
	HpMove();						// HP�̌v�Z����
}



