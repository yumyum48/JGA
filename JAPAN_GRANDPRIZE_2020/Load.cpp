#include "Load.h"
#include "DxLib.h"
#include "GameTitle.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Save.h"
#include "GameScene.h"
#include "Init.h"
#include "Macro.h"
void GameLoad() {
	static int select = 0;	// ���v���C���[���I�����Ă�����̂��i�[
	GameLoadMove(&select);
	GameLoadDisp(select);
	
}
void GameLoadDisp(int select) {
	picInfo backImage;

	DrawRotaGraph2(backImage.x, backImage.y, 0, 0, 8.0, 0.0, g_pic.title[0], TRUE);		// �^�C�g���̔w�i
	int loadSelect_X = 437;																// �Z���N�g�E�B���h�E�̃Z�[�u����X���W
	int loadSelect_Y[3] = { 72, 72 + 250, 72 + 500 };									// �Z���N�g�E�B���h�E�̃Z�[�u����Y���W


	DrawBox(loadSelect_X, loadSelect_Y[0], loadSelect_X + MENU_SELECT_WIDTH, loadSelect_Y[0] + MENU_SELECT_HEIGHT, 0xFFFFFF, TRUE);	// �Z�[�u�f�[�^���̂P
	DrawBox(loadSelect_X, loadSelect_Y[1], loadSelect_X + MENU_SELECT_WIDTH, loadSelect_Y[1] + MENU_SELECT_HEIGHT, 0xFFFFFF, TRUE);	// �Z�[�u�f�[�^���̂Q
	DrawBox(loadSelect_X, loadSelect_Y[2], loadSelect_X + MENU_SELECT_WIDTH, loadSelect_Y[2] + MENU_SELECT_HEIGHT, 0xFFFFFF, TRUE);	// �Z�[�u�f�[�^���̂R

	DrawBox(loadSelect_X, loadSelect_Y[select], loadSelect_X + MENU_SELECT_WIDTH, loadSelect_Y[select] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);

	SaveModeDisp(loadSelect_X, loadSelect_Y);	// �Z�[�u�f�[�^�̕\��
}
void GameLoadMove(int *select) {

	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (++*select > 2) *select = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (-- *select < 0) *select = 2;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		if (Read(*select) == 1) {
			DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF0000, TRUE);
		}
		else {
			g_gameScene = GAME_SELECT;
			*select = 0;
		}
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_B) {
		g_gameScene = GAME_TITLE;
		*select = 0;
		GameInit();
	}
}