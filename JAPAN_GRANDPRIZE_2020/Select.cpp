#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"

#define STAGE_NUMBER 7

void StageSelect() {

	//���j���[�J�[�\���ړ�����
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_game_stage > 7) g_game_stage = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_game_stage < 0) g_game_stage = 7;
	}

	//���őI���i�f�o�b�N�j
	if (g_keyInfo.keyFlg & PAD_INPUT_A)
		g_gameScene = GAME_PLAY;

	SpeedSelect();
	SelectDisp();
}

void SelectDisp(void) {
	int g_stageX = 455;		//�X�e�[�W�Z���N�gX���W
	int g_stageY = 285;		//�X�e�[�W�Z���N�gY���W
	int g_stageW = 305;		//�X�e�[�W�Z���N�g��
	int g_stageH = 298;		//�X�e�[�W�Z���N�g����

	float g_x;
	float g_y;

	for (int i = 0; i < STAGE_NUMBER; i++) {
		float bb = i % STAGE_NUMBER;
		float angle = (DX_TWO_PI / STAGE_NUMBER * bb) + 6.0675;
		g_x = g_stageX + cos(angle) * g_stageW;
		g_y = g_stageY + sin(angle) * g_stageH;

		//�X�e�[�W�\��
		DrawBox( g_x , g_y ,g_x + 180,g_y + 180, 0x00ff00, TRUE);

	}

	DrawBox(420, 235, 655, 470,0x008000, TRUE);

	switch (g_game_stage)
	{
	case 0:	DrawBox(g_x-265, g_y-3, g_x - 85, g_y + 178, 0xFF0000, FALSE);break;
	case 1: DrawBox(g_x, g_y, g_x + 180, g_y + 180, 0xFF0000, FALSE); break;
	case 2: DrawBox(g_x+163, g_y+205, g_x + 345, g_y + 385, 0xFF0000, FALSE); break;
	case 3: DrawBox(g_x+103, g_y+455, g_x + 282, g_y + 637, 0xFF0000, FALSE); break;
	case 4: DrawBox(g_x-138, g_y+565, g_x + 44, g_y + 745, 0xFF0000, FALSE); break;
	case 5: DrawBox(g_x- 375, g_y+450, g_x - 195, g_y +631, 0xFF0000, FALSE); break;
	case 6: DrawBox(g_x-432.5, g_y+198.5, g_x - 250, g_y + 380, 0xFF0000, FALSE); break;
	case 7: DrawBox(420,235,655,470, 0xFF0000, FALSE); break;
	default: break;
	}
}

// �X�N���[�����x�̑I��
void SpeedSelect() {
	static int speedSelect = 0;
	static bool StickFlg = FALSE;

	DrawFormatString(100, 10, 0xffff00, "%d", speedSelect);

	// �v���C���[�̑���
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (++speedSelect > 2) speedSelect = 0;
	}
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (--speedSelect < 0) speedSelect = 2;
	}

	// �X�N���[�����x�̌���
	if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
		(g_keyInfo.keyFlg & PAD_INPUT_A)
		&& (speedSelect == 0)) {
		g_button.conFlg = 1;
		g_speedLevel = SPEED_EASY;
	}
	else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
		(g_keyInfo.keyFlg & PAD_INPUT_A)
		&& (speedSelect == 1)) {
		g_button.conFlg = 1;
		g_speedLevel = SPEED_NORMAL;
	}
	else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0)*/
		(g_keyInfo.keyFlg & PAD_INPUT_A)
		&& (speedSelect == 2)) {
		g_button.conFlg = 1;
		g_speedLevel = SPEED_HARD;
	}
}