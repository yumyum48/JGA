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
// �Q�[���v���C�̃��C���֐�
void GamePlay() {
	// �f�o�b�O�p�ň�U����ւ�GamePlayMove();
	GamePlayDisp();
	GamePlayMove();
	
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();						// �}�b�v�̕`��
	EnemyDisp();					// �G�l�~�[�̕`��
	BossDisp[0]();		// �{�X�̕\��
	PlayerDisp();					// �v���C���[�̕`��
	RainDisp();						// �J�̕`��
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	MapMove();						// �}�b�v�̓���
	EnemyMove();					// �G�l�~�[�̓���
	PlayerMove();					// �v���C���[�̓���
	BossMove[0]();		// �{�X�̓���
	RainMove();						// �J�̓���
}



