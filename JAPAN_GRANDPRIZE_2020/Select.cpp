#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"
#include "Picture.h"
#include "Change_ScReen_Animation.h"
#include "Init.h"
#define STAGE_NUMBER 7

#define MENU_SELECT_WIDTH 320	// ���j���[��ʂ̒��̑I�����郁�j���[�ꗗ�̉���
#define MENU_SELECT_HEIGHT 84	// ���j���[��ʂ̒��̑I�����郁�j���[�ꗗ�̏c��

picInfo g_menuBox;		// ���j���[�E�B���h�E�̏��
bool g_menuFlg = FALSE;		// ���j���[�E�B���h�E���o��������t���O TURE:�o�������� FALSE:�o�������Ȃ�
int g_menuSelect;			// ���I�����Ă��郁�j���[���擾����

void StageSelect() {
	
	SpeedSelect();
	SelectMove();
	SelectDisp();
}

void SelectDisp(void) {
	picInfo stage[8];
	
	// �Z���N�g��ʂ̔w�i
	DrawGraph(0, 0, g_pic.selectBack, TRUE);

	// �Z���N�g��ʂ̃}�b�v
	for (int i = 0; i < MAP_MAX; i++) {
		stage[i].SelectStageInit(i);
		DrawBox(stage[i].x, stage[i].y, stage[i].x + 100, stage[i].y + 100, 0x00FF00, TRUE);
		if (i == 7) {
			DrawBox(stage[i].x, stage[i].y, stage[i].x + 200, stage[i].y + 200, 0x00FF00, TRUE);
		}
	}
	
	// �Z���N�g��ʂ̑I�𒆂̃E�B���h�E��\��
	DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 100, stage[g_select_Stage].y + 100, 0xFF0000, FALSE);
	if (g_select_Stage == 7) {
		DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 200, stage[g_select_Stage].y + 200, 0xFF0000, FALSE);
	}
	int menuSelect_X = g_menuBox.x + 122;												// �Z���N�g�E�B���h�E�̃��j���[����X���W
	int menuSelect_Y[3] = { g_menuBox.y +  79, g_menuBox.y + 320, g_menuBox.y + 571};	// �Z���N�g�E�B���h�E�̃��j���[����Y���W


	// ���j���[���
	DrawBox(g_menuBox.x, g_menuBox.y, g_menuBox.x + 625, g_menuBox.y + 700, 0xFFFFFF, TRUE);
	// ���j���[��ʂ̍���
	DrawBox(menuSelect_X, menuSelect_Y[0], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[1], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[2], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);

	
	// ���j���[��ʂ��o�ĂȂ��Ƃ�
	if (g_menuFlg == FALSE) {
		//c�őI���i�f�o�b�N�j
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			//g_gameScene = GAME_PLAY;
			Get_NowDisp(GAME_PLAY, 2);
			g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

		}
	}
	// ���j���[��ʂ��o�Ă���Ƃ�
	else {
		DrawBox(menuSelect_X, menuSelect_Y[g_menuSelect], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			switch (g_menuSelect)
			{
			case 0: break;// �f�[�^�̃Z�[�u
			case 1: break;// �X�L���J�X�^�}�C�Y
			case 2: GameInit();  g_gameScene = GAME_TITLE; break;	// �^�C�g���ֈړ�
			default:
				break;
			}
		}
	}
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + 100, g_mouseInfo.mouseY + 100, 0x00FF00, TRUE);
	//int stageX = 455;		//�X�e�[�W�Z���N�gX���W
	//int stageY = 285;		//�X�e�[�W�Z���N�gY���W
	//int stageW = 305;		//�X�e�[�W�Z���N�g��
	//int stageH = 298;		//�X�e�[�W�Z���N�g����

	//float g_x;	// 
	//float g_y;	// 

	//for (int i = 0; i < STAGE_NUMBER; i++) {
	//	float bb = i % STAGE_NUMBER;
	//	float angle = (DX_TWO_PI / STAGE_NUMBER * bb) + 6.0675;
	//	g_x = stageX + cos(angle) * stageW;
	//	g_y = stageY + sin(angle) * stageH;

	//	//�X�e�[�W�\��
	//	DrawBox( g_x , g_y ,g_x + 180,g_y + 180, 0x00ff00, TRUE);

	//}

	//DrawBox(420, 235, 655, 470,0x008000, TRUE);

	//switch (g_select_Stage)
	//{
	//case 0:	DrawBox(g_x-265, g_y-3, g_x - 85, g_y + 178, 0xFF0000, FALSE);break;
	//case 1: DrawBox(g_x, g_y, g_x + 180, g_y + 180, 0xFF0000, FALSE); break;
	//case 2: DrawBox(g_x+163, g_y+205, g_x + 345, g_y + 385, 0xFF0000, FALSE); break;
	//case 3: DrawBox(g_x+103, g_y+455, g_x + 282, g_y + 637, 0xFF0000, FALSE); break;
	//case 4: DrawBox(g_x-138, g_y+565, g_x + 44, g_y + 745, 0xFF0000, FALSE); break;
	//case 5: DrawBox(g_x- 375, g_y+450, g_x - 195, g_y +631, 0xFF0000, FALSE); break;
	//case 6: DrawBox(g_x-432.5, g_y+198.5, g_x - 250, g_y + 380, 0xFF0000, FALSE); break;
	//case 7: DrawBox(420,235,655,470, 0xFF0000, FALSE); break;
	//default: break;
	//}
}
void SelectMove() {
	

	if (g_menuFlg == FALSE) {	// ���j���[��ʂ��o�ĂȂ��Ƃ��̏���(�}�b�v�Z���N�g)
		// ���j���[��ʂ����ɃX�N���[��
		if (g_menuBox.x < 1182) {
			g_menuBox.x += 10;
		}
		else{
			g_menuBox.x = 1182;
		}
		//���j���[�J�[�\���ړ�����
		if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
			if (++g_select_Stage > 7) g_select_Stage = 0;
		}
		// ���j���[�J�[�\�����䏈��
		if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
			if (--g_select_Stage < 0) g_select_Stage = 7;
		}

		////c�őI���i�f�o�b�N�j
		//if (g_keyInfo.keyFlg & PAD_INPUT_3) {
		//	//g_gameScene = GAME_PLAY;
		//	Get_NowDisp(GAME_PLAY, 1);
		//	g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;
		//	
		//}
	}
	else {	// ���j���[��ʂ�\�����鎞
		
		// ���j���[��ʂ�������悤�ɃX�N���[��
		if (g_menuBox.x > 724) {
			g_menuBox.x -= 10;
		}
		else {
			g_menuBox.x = 724;
		}

		
		if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
			if (++g_menuSelect > 2) g_menuSelect = 0;
		}
		// ���j���[�J�[�\�����䏈��
		if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
			if (--g_menuSelect < 0) g_menuSelect = 2;
		}
		
	}


	// ���{�^���������ƃ��j���[���J��
	if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == FALSE) {
		g_menuFlg = TRUE;
	}
	else if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == TRUE) {
		g_menuFlg = FALSE;
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
	if (speedSelect == 0) {
		g_speedLevel = SPEED_EASY;
	}
	if (speedSelect == 1) {
		g_speedLevel = SPEED_NORMAL;
	}
	if (speedSelect == 2) {
		g_speedLevel = SPEED_HARD;
	}
	//// �X�N���[�����x�̌���
	//if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 0)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_EASY;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 1)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_NORMAL;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0)*/
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 2)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_HARD;
	//}
}

void SelectInit() {
	g_menuBox.MenuWindowInit();
	g_menuFlg = FALSE;
}
