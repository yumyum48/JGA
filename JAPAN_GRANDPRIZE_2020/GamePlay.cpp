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
	MapMove();						// �}�b�v�̓���
	MapDisp();						// �}�b�v�̕`��
	
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	
	EnemyDisp();					// �G�l�~�[�̕`��
	
	PlayerDisp();					// �v���C���[�̕`��
	RainDisp();						// �J�̕`��
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	
	EnemyMove();					// �G�l�~�[�̓���
	PlayerMove();					// �v���C���[�̓���
	
	RainMove();						// �J�̓���
}



