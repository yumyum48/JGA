#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"

image g_pic;
mouse g_mouseInfo;
key g_keyInfo;

float moveX;	// �v���C���[�̓����ɍ��킹�ă}�b�v�𓮂���

// �Q�[���v���C�̃��C���֐�
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
}
// �Q�[���v���C�̕`��
void GamePlayDisp() {
	
	MapDisp();		// �}�b�v�̕`��
	PlayerDisp();	// �v���C���[�̕`��
	
}

// �Q�[���v���C�̓���
void GamePlayMove() {

	PlayerMove();

}
void MapDisp() {

	static int map1X = 0;	// �΃}�b�v��X���W
	static int map2X = 1024;// ���F�}�b�v��X���W
	
	// �}�b�v���J��Ԃ�����
	if ((int)moveX + 1024 + map1X <= 0) {
		map1X = map2X + 1024;
	}

	if ((int)moveX + 1024 + map2X <= 0) {
		map2X = map1X + 1024;
	}
	// �}�b�v�̕`��
	DrawGraph(map1X + moveX, 0, g_pic.map[0], TRUE);
	DrawGraph(map2X + moveX, 0, g_pic.map[1], TRUE);
}


