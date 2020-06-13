#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"
#include "Picture.h"
#include "SkillCustom.h"
#include "Change_ScReen_Animation.h"
#include "Init.h"
#include "Save.h"
#include "Sounds.h"

/******************************************************
// �}�N���̒�`
*******************************************************/
#define STAGE_NUMBER			 (7)
#define MENU_SAVE_BOX_XPOINT_MAX (724)	// ���j���[��ʂƃZ�[�u��ʂ̔w�i���ړ����ĕ\�������X���W
#define MENU_SAVE_BOX_MOBE		 (10)	// ���j���[��ʂƃZ�[�u��ʂ̔w�i���ړ�����X�s�[�h
#define MENU_BOX_XPOINT_MIN		 (1182)	// ���j���[��ʂ��B��Ă��鎞��X���W
#define SAVE_BOX_XPOINT_MIN		 (1280)	// �Z�[�u��ʂ��B��Ă��鎞��X���W
/******************************************************
// �O���[�o���ϐ��̐錾
*******************************************************/
picInfo g_menuBox;		// ���j���[�E�B���h�E�̏��
picInfo g_saveBox;		// �Z�[�u�E�B���h�E�̏��
int g_menuFlg;			// ���j���[�E�B���h�E���o��������t���O  0:�o�������Ȃ� 1:���j���[��ʂ��o�������� 2:�Z�[�u��ʂ��o��������
int g_menuSelect;		// ���I�����Ă��郁�j���[���擾����
int g_saveSelect;		// ���I�����Ă���Z�[�u�t�H���_���擾����

int g_cursorAnime = 0;	//���j���[�̃J�[�\���A�j���[�V����
/******************************************************
// �񋓑̂̐錾
*******************************************************/
enum {
	MENU_OFF,	// ���j���[��ʂ��I�t
	MENU_ON,	// ���j���[��ʂ��I��
	MENU_SAVE,	// �Z�[�u��ʂ��I��
};
/******************************************************
// �Z���N�g��ʂ̊Ǘ�
*******************************************************/
void StageSelect() {
	PlaySoundMem(g_sound[BGM_SELECT], DX_PLAYTYPE_LOOP, FALSE);            //�Z���N�gBGM�Đ�
	SpeedSelect();	// �Q�[���̃X�N���[���X�s�[�h��ύX
	SelectMove();	// �Z���N�g��ʂ̑���⓮��
	SelectDisp();	// �Z���N�g��ʂ̕\��
}
/******************************************************
// �Z���N�g��ʂ̕\��
*******************************************************/
void SelectDisp(void) {
	picInfo stage[8];

	// �Z���N�g��ʂ̔w�i
	//DrawGraph(0, 0, g_pic.selectBack, TRUE);
	DrawRotaGraph2(0, 0, 0, 0, 8.0, 0.0, g_pic.selectBack, TRUE);		// �^�C�g���̔w�i

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


	int menuSelect_X = g_menuBox.x + 61;												// �Z���N�g�E�B���h�E�̃��j���[����X���W
	int menuSelect_Y[3] = { g_menuBox.y + 57, g_menuBox.y + 57 + 250, g_menuBox.y + 57 + 500 };	// �Z���N�g�E�B���h�E�̃��j���[����Y���W

	// ���j���[��ʂ̕\��
	//DrawBox(g_menuBox.x, g_menuBox.y, g_menuBox.x + 625, g_menuBox.y + 700, 0xFFFFFF, TRUE);
	//DrawRotaGraph(g_menuBox.x + 200, g_menuBox.y + 350, 3.8, -3.14 / 2, g_pic.selectUI[4], TRUE);
	//DrawModiGraph(g_menuBox.x + 200, g_menuBox.y + 350,		// ����
	//	g_menuBox.x + 625, g_menuBox.y + 350,				// �E��
	//	g_menuBox.x + 200, g_menuBox.y + 700,				// ����
	//	g_menuBox.x + 625, g_menuBox.y + 700,				// �E��
	//	g_pic.selectUI[4], TRUE
	//);
	DrawModiGraph(g_menuBox.x, g_menuBox.y,			// ����
		g_menuBox.x + 625, g_menuBox.y,				// �E��
		g_menuBox.x + 625, g_menuBox.y + 700,		// �E��
		g_menuBox.x, g_menuBox.y + 700,				// ����
		g_pic.selectUI[4], TRUE
	);
	// ���j���[��ʂ̍���
	//DrawBox(menuSelect_X, menuSelect_Y[0], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	//DrawBox(menuSelect_X, menuSelect_Y[1], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	//DrawBox(menuSelect_X, menuSelect_Y[2], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[0] + 10, g_pic.selectUI[1], TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[1] + 10, g_pic.selectUI[3], TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[2] + 10, g_pic.selectUI[2], TRUE);


	// Y�{�^���̕\��
	int yButtonX = menuSelect_X - 64;
	int yButtonY = 75;
	DrawGraph(yButtonX, yButtonY, g_pic.button[0], TRUE);


	// �Z�[�u��ʂ̕\��
	//DrawBox(g_saveBox.x, g_saveBox.y, g_saveBox.x + 625, g_saveBox.y + 700, 0x808080, TRUE);
	//DrawRotaGraph(g_saveBox.x + 200, g_saveBox.y + 350, 3.8, -3.14 / 2, g_pic.selectUI[4], TRUE);
	DrawModiGraph(g_saveBox.x, g_saveBox.y,		// ����
		g_saveBox.x + 625, g_saveBox.y,				// �E��
		g_saveBox.x + 625, g_saveBox.y + 700,		// �E��
		g_saveBox.x, g_saveBox.y + 700,				// ����
		g_pic.selectUI[4], TRUE
	);
	int saveSelect_X = g_saveBox.x + 61;												// �Z���N�g�E�B���h�E�̃Z�[�u����X���W
	int saveSelect_Y[3] = { g_saveBox.y + 65, g_saveBox.y + 55 + 250, g_saveBox.y + 55 + 500 };	// �Z���N�g�E�B���h�E�̃Z�[�u����Y���W
	/*DrawBox(saveSelect_X, saveSelect_Y[0], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[1], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[2], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);*/

	// Y�{�^���̕\��
	int yButtonX2 = saveSelect_X - 64;
	int yButtonY2 = 75;
	DrawGraph(yButtonX2, yButtonY2, g_pic.button[0], TRUE);

	// ���j���[��ʂ̋@�\
	{
		// ���j���[��ʂ��o�ĂȂ��Ƃ�
		if (g_menuFlg == MENU_OFF) {
			if (g_keyInfo.keyFlg & PAD_INPUT_A) {

				Get_NowDisp(GAME_PLAY, 2);
				//g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;
			}
		}
		// ���j���[��ʂ��o�Ă���Ƃ�
		else if (g_menuFlg == MENU_ON) {
			if (g_cursorAnime < 200) g_cursorAnime += 10;
			//DrawBox(menuSelect_X, menuSelect_Y[g_menuSelect], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, FALSE);
			//DrawGraph(menuSelect_X + 20, menuSelect_Y[g_menuSelect] + 60, g_pic.bossTongue, TRUE);
			DrawExtendGraph(menuSelect_X + 20, menuSelect_Y[g_menuSelect] + 80,
				menuSelect_X + 76 + g_cursorAnime, menuSelect_Y[g_menuSelect] + 100, g_pic.bossTongue, TRUE);
			//DrawGraph(menuSelect_X + 50, menuSelect_Y[g_menuSelect] - 45, g_pic.gauge, TRUE);
			DrawRotaGraph(menuSelect_X + 10 + g_cursorAnime, menuSelect_Y[g_menuSelect] + 50, 0.5, 0, g_pic.skillEffect[9], TRUE);
			DrawGraph(menuSelect_X, menuSelect_Y[g_menuSelect], g_pic.Life[1], TRUE);
		}
		// ���j���[��ʂŕۑ��������ꂽ�ꍇ
		else if (g_menuFlg == MENU_SAVE) {
			if (g_cursorAnime < 400) g_cursorAnime += 20;
			if (g_saveBox.x == MENU_SAVE_BOX_XPOINT_MAX) {	// ���W���Œ肳�ꂽ�瑀��\
				//DrawBox(saveSelect_X, saveSelect_Y[g_saveSelect], saveSelect_X + MENU_SELECT_WIDTH - 100, saveSelect_Y[g_saveSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
				SaveModeDisp(saveSelect_X, saveSelect_Y);	// �Z�[�u�f�[�^�\��

				// �Z���N�g���Ă�����̂����o��
				DrawExtendGraph(saveSelect_X + 20, saveSelect_Y[g_saveSelect] + 80,
					saveSelect_X + 76 + g_cursorAnime, saveSelect_Y[g_saveSelect] + 100, g_pic.bossTongue, TRUE);
				DrawRotaGraph(saveSelect_X + 10 + g_cursorAnime, saveSelect_Y[g_saveSelect] + 50, 0.5, 0, g_pic.skillEffect[9], TRUE);
				DrawGraph(saveSelect_X, saveSelect_Y[g_saveSelect], g_pic.Life[1], TRUE);
			}
		}
	}

}
/******************************************************
// �Z���N�g��ʂ̓���
*******************************************************/
void SelectMove() {


	if (g_menuFlg == MENU_OFF) {				// ���j���[��ʂ��o�ĂȂ��Ƃ��̏���(�}�b�v�Z���N�g)

		MenuScrollOut();						// ���j���[��ʂ����ɃX�N���[���A�E�g

		StageSelectOper();						// �X�e�[�W�̌���̂��߂̃J�[�\���𑀍삳����

		if (g_keyInfo.keyFlg & PAD_INPUT_A) {	// ���肵���X�e�[�W�Ɉړ����Ȃ���V�[�����Q�[���v���C�ɕς���

			//Get_NowDisp(GAME_PLAY, 2);
			HyperStop(g_sound[BGM_SELECT]);		//���ׂĎ~�߂�ŋ��֐�
			g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

		}
	}
	else if (g_menuFlg == MENU_ON) {	// ���j���[��ʂ�\�����鎞

		MenuScrollIn();		// ���j���[��ʂ�������悤�ɉ�ʒ����t�߂܂ňړ������A�Z�[�u��ʂ�����΁A������

		MenuSelectOper();	// ���j���[�J�[�\�����䏈��

		MenuSelect();		// ����{�^���������ƑΏۂ̃��j���[�ւƐڑ�
	}
	else if (g_menuFlg == MENU_SAVE) {	// �Z�[�u��ʂ��o��Ƃ�

		bool saveflg = FALSE;			// �Z�[�u��ʂ�\�������邩�ǂ��� FALSE:�\�������Ȃ� TRUE:�\��������

		SaveSelectOper();				// �Z�[�u���j���[�J�[�\�����䏈��

		saveflg = SaveMenu_MenuScrollOut(saveflg);			// ���j���[��ʂ���ʊO�܂ŃX�N���[���A�E�g�����A������������Z�[�u��ʂ�\��������t���O���I���ɂ���
		if (saveflg == TRUE) {

			SaveMenu_ScrollIn();							// �Z�[�u��ʂ���ʒ����t�߂܂œ�����
			if (g_saveBox.x == MENU_SAVE_BOX_XPOINT_MAX) {	// �Z�[�u��ʂ������܂ŗ����瑀��\
				if (g_keyInfo.keyFlg & PAD_INPUT_A) {		// ����{�^����������
					SaveMenu_Save();
					g_cursorAnime = 0;						// �I�����ꂽ�t�@�C���ɃZ�[�u�����s����
				}
				if (g_keyInfo.keyFlg & PAD_INPUT_B) {		// B�{�^���������ƁA���j���[�I����ʂɖ߂�
					g_menuFlg = MENU_ON;
					g_cursorAnime = 0;
					//g_menuSelect = 0;
				}
			}
		}

	}


	// ���{�^���������ƃ��j���[���J��
	if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == FALSE) {
		g_menuFlg = MENU_ON;
	}
	else if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == TRUE) {
		g_menuFlg = MENU_OFF;
	}


}
/******************************************************
// �I�����ꂽ�t�@�C���ɃZ�[�u�����s����
*******************************************************/
void SaveMenu_Save() {
	Save(g_saveSelect);
	//switch (g_saveSelect) {
	//case 0: ; break;	// �t�@�C���P�ɕۑ�
	//case 1:; break;	// �t�@�C���Q�ɕۑ�
	//case 2:; break;	// �t�@�C���R�ɕۑ�
	//default:  break;	// �Ⴄ����������Ɖ������Ȃ�
	//}
}
/******************************************************
// �Z�[�u��ʂ���ʒ����t�߂܂œ�����
*******************************************************/
void SaveMenu_ScrollIn() {
	if (g_saveBox.x > MENU_SAVE_BOX_XPOINT_MAX) {	// �Z�[�u��ʂ��X�N���[���C��������
		g_saveBox.x -= MENU_SAVE_BOX_MOBE;
	}
	else {
		g_saveBox.x = MENU_SAVE_BOX_XPOINT_MAX;		// �ړI�̍��W�܂ŃZ�[�u��ʂ���������W���Œ�
	}
}
/******************************************************
// ���j���[��ʂ���ʊO�܂ŃX�N���[���A�E�g�����A������������Z�[�u��ʂ�\��������t���O���I���ɂ���
*******************************************************/
bool SaveMenu_MenuScrollOut(bool saveFlg) {

	if (g_menuBox.x < WINDOW_WIDTH) {	// ���j���[����ʊO�փX�N���[���A�E�g
		g_menuBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_menuBox.x = WINDOW_WIDTH;
		saveFlg = TRUE;				// �X�N���[���A�E�g��������
	}
	return saveFlg;
}
/******************************************************
// ����{�^���������ƑΏۂ̃��j���[�ւƐڑ�
*******************************************************/
void MenuSelect() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		PlaySoundMem(g_sound[SE_KETTEI], DX_PLAYTYPE_BACK, TRUE);			//����SE�Đ�
		switch (g_menuSelect) {
		case 0: g_menuFlg = MENU_SAVE;		g_menuSelect = 0;		   break;	// �f�[�^�̃Z�[�u
		case 1: g_gameScene = GAME_SKILLCUSTOM;   g_menuSelect = 0;     break;	// �X�L���J�X�^�}�C�Y
		case 2: GameInit(); g_menuFlg = MENU_OFF; g_gameScene = GAME_TITLE; HyperStop(g_sound[BGM_SELECT]); break;    // �^�C�g���ֈړ�
		default:
			break;
		}
	}
}
/******************************************************
// ���j���[��ʂ�������悤�ɉ�ʒ����t�߂܂ňړ�������
*******************************************************/
void MenuScrollIn() {
	if (g_saveBox.x < SAVE_BOX_XPOINT_MIN) {	// �Z�[�u���j���[���X�N���[���A�E�g
		g_saveBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_saveBox.x = SAVE_BOX_XPOINT_MIN;		// �Z�[�u���j���[���ڕW�n�_�ɗ�������W���Œ�
		// �Z�[�u��ʂ��ړ��������Ă���
		// ���j���[��ʂ�������悤�ɃX�N���[��
		if (g_menuBox.x > MENU_SAVE_BOX_XPOINT_MAX) {
			g_menuBox.x -= MENU_SAVE_BOX_MOBE;
		}
		else {
			g_menuBox.x = MENU_SAVE_BOX_XPOINT_MAX;
		}
	}
}
/******************************************************
// ���j���[��ʂ���ʒ[�t�߂Ɉړ�������
*******************************************************/
void MenuScrollOut() {
	if (g_menuBox.x < MENU_BOX_XPOINT_MIN) {
		g_menuBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_menuBox.x = MENU_BOX_XPOINT_MIN;
	}
}
/******************************************************
// �X�e�[�W�����肳����J�[�\���𑀍삳����
*******************************************************/
void StageSelectOper() {
	//���j���[�J�[�\���ړ�����
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_select_Stage > g_select_MAX) g_select_Stage = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
	}
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_select_Stage < 0) g_select_Stage = g_select_MAX;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
	}
}
/******************************************************
// ���j���[�ꗗ�̃J�[�\���𑀍삳����
*******************************************************/
void MenuSelectOper() {
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
		if (++g_menuSelect > 2) g_menuSelect = 0;
	}
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
		if (--g_menuSelect < 0) g_menuSelect = 2;
	}
}
/******************************************************
// �Z�[�u���j���[�̃J�[�\�����ړ�������
*******************************************************/
void SaveSelectOper() {
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
		if (++g_saveSelect > 2) g_saveSelect = 0;
	}
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//�I��SE�Đ�
		if (--g_saveSelect < 0) g_saveSelect = 2;
	}
}

/******************************************************
// �X�N���[�����x�̑I��
*******************************************************/
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
/******************************************************
// �Z���N�g�V�[���̏�����
*******************************************************/
void SelectInit() {
	g_menuBox.MenuWindowInit();
	g_saveBox.MenuSaveWindowInit();
	//g_menuFlg = FALSE;
}
