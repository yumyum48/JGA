#include "DxLib.h"
#include "control.h"
#include "Controler.h"
#include "GameTitle.h"
#include "Picture.h"
#include "Struct.h"
#include "GameScene.h"
#include "Macro.h"
#include "Rain.h"
#include "Init.h"

enum {	// �^�C�g���̃e�L�X�g�̏��
	TITLE_NEW_START,	// �V�����Q�[�����n�߂�
	TITLE_ROAD,			// �Z�[�u�f�[�^����I��ŃQ�[�����n�߂�
	TITLE_END,			// �Q�[�����I������
	TITLE_MAX,			// ���̍ő吔
};
// �萔�̐錾
const int TITLETEXT_X[TITLE_MAX] = { 498, 498, 549};	// [���߂���]��[��������]��[�I��]�̉摜��X���W
const int TITLETEXT_Y[TITLE_MAX] = { 402, 536, 665};	// [���߂���]��[��������]��[�I��]�̉摜��Y���W

int g_selectCheck;	// ���v���C���[���I�����Ă�����̂��m�F����(0:���߂��� 1:�������� 2:�I��)

// �Q�[���^�C�g���̃��C���֐�
void GameTitle() {
	TitleMove();
	TitleDisp();	
}

// �^�C�g���̕`��
void TitleDisp() {
	picInfo backImage;		// �^�C�g���̔w�i�摜�̍��W
	picInfo titleRogo;		// �^�C�g�����S�̉摜�̍��W
	
	RainDisp();

	DrawRotaGraph2(backImage.x, backImage.y, 0, 0, 8.0, 0.0, g_pic.title[0], TRUE);		// �^�C�g���̔w�i
	DrawGraph(107, 118, g_pic.titleText[0], TRUE);										// �^�C�g���̃��S
	DrawGraph(TITLETEXT_X[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START], g_pic.titleText[1], TRUE);										// [���߂���]�̕���
	DrawGraph(TITLETEXT_X[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD], g_pic.titleText[2], TRUE);										// [��������]�̕���
	DrawGraph(TITLETEXT_X[TITLE_END], TITLETEXT_Y[TITLE_END], g_pic.titleText[3], TRUE);										// [�I��]�̕���

	int titleTextW[3] = { 280, 280, 188 };	// �^�C�g����[���߂���][��������][�I��]�̃e�L�X�g�摜�̉���
	int titleTextH[3] = { 84, 84, 87 };	// �^�C�g����[���߂���][��������][�I��]�̃e�L�X�g�摜�̏c��
	switch (g_selectCheck) {
	case 0:
		// ����I�����Ă��邩�킩��悤�Ɏl�p�����o��
		DrawBox(TITLETEXT_X[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START], TITLETEXT_X[TITLE_NEW_START] + titleTextW[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START] + titleTextH[TITLE_NEW_START], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_SELECT;	// �Q�[���Z���N�g�ֈړ�
			Reset();					// �Q�[�����e�����Z�b�g�ɂ���
		}
		break;
	case 1:
		// ����I�����Ă��邩�킩��悤�Ɏl�p�����o��
		DrawBox(TITLETEXT_X[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD], TITLETEXT_X[TITLE_ROAD] + titleTextW[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD] + titleTextH[TITLE_ROAD], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_SELECT;	// �Q�[���Z���N�g�ֈړ�
			// ���{���̓��[�h����f�[�^��I�����ă��[�h���I���ăQ�[���Z���N�g�ֈړ�
		}
		break;
	case 2:
		// ����I�����Ă��邩�킩��悤�Ɏl�p�����o��
		DrawBox(TITLETEXT_X[TITLE_END], TITLETEXT_Y[TITLE_END], TITLETEXT_X[TITLE_END] + titleTextW[TITLE_END], TITLETEXT_Y[TITLE_END] + titleTextH[TITLE_END], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_END;		// �Q�[���I��
		}
		break;
	default:
		break;
	}

	
}

void TitleSound() {
	
}

// �^�C�g���ł̓���
void TitleMove() {
	

	RainMove();


	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {	// ��ԉ��ŉ���������x�����Ə�ɖ߂�
		if (++g_selectCheck > 2) g_selectCheck = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {		// ��ԏ�ŏ��������x�����ƁA���ɍs��
		if (--g_selectCheck < 0) g_selectCheck = 2;
	}


	

}