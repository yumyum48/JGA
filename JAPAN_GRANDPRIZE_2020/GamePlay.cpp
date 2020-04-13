#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"


// �Q�[���v���C�̃��C���֐�
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
	
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();		// �}�b�v�̕`��
	EnemyDisp();	// �G�l�~�[�̕`��
	PlayerDisp();	// �v���C���[�̕`��
	RainDisp();		// �J�̕`��
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	MapMove();		// �}�b�v�̓���
	EnemyMove();	// �G�l�~�[�̓���
	PlayerMove();	// �v���C���[�̓���
	RainMove();		// �J�̓���
}



