#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"

extern image g_pic;
mouse g_mouseInfo;
key g_keyInfo;

// �Q�[���v���C�̃��C���֐�
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
	
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();		// �}�b�v�̕`��
	//PlayerDisp();	// �v���C���[�̕`��
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {
	MapMove();		// �}�b�v�̓���
	//PlayerMove();
}



