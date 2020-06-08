#include "DxLib.h"
#include "SkillCustom.h"
#include "GameScene.h"
#include "control.h"
#include "Struct.h"
#include "Player.h"
#include "Sounds.h"
#include "Picture.h"
#include "Select.h"

static int g_Skill_Num = 1;	//�I�����Ă���X�L���ԍ�
int g_set = 0;			//�Z�b�g�����ԍ�
int debug = 1;
int con_1, con_2;		//�z��R���g���[���ϐ�

bool costomEndFlg = FALSE;	//��ʈړ����̊m�F�t���O
bool skill_ReleaseFlg[7] = { FALSE }; //�X�L������t���O
int past_Skill[3] = { 0 };	//�O�̃X�L������ۑ�


void SkillCustom() {
	SkillCustom_Move();
	SkillCustom_Disp();

}

// �X�L���J�X�^�}�C�Y�̕\��
void SkillCustom_Disp() {

	DrawRotaGraph2(0, 0, 0, 0, 8.0, 0.0, g_pic.customBackimage, TRUE);		// �w�i�\��
	//�f�o�b�O�p
	DrawFormatString(0, 60, 0xFFFFFF, "%d", g_player.skillcustom[0]);
	DrawFormatString(10, 60, 0xFFFFFF, "%d", g_player.skillcustom[1]);
	DrawFormatString(20, 60, 0xFFFFFF, "%d", g_player.skillcustom[2]);
	DrawFormatString(0, 80, 0xFFFFFF, "%d", g_Skill_Num);
	DrawFormatString(10, 80, 0xFFFFFF, "%d", debug);



	DrawFormatString(0, 100, 0xFF0000, "%d", skill_ReleaseFlg[g_Skill_Num - 1]);

	//���m�点�p
	//DrawString(800, 800, "���{�^���ŃX�L������", 0xFFFFFF);
	//DrawString(800, 900, "���{�^���ŃX�L������", 0xFFFFFF);

	//��
	SetFontSize(40);
	DrawString(1000, 650, "����", 0x00FF00);
	if (costomEndFlg == TRUE) DrawBox(1000, 650, 1100, 700, 0x00FF00, FALSE);

	SkillChoice_Dis();

	DrawExtendGraph(35, 650, 320, 735, g_pic.skilChoiceBox, FALSE);

	DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[0]], TRUE, FALSE);
	DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[1]], TRUE, FALSE);
	DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[2]], TRUE, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	SetDrawBright(255, 0, 0);
	if (g_set < 1) DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[0]], TRUE, FALSE);
	if (g_set < 2) DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[1]], TRUE, FALSE);
	if (g_set < 3) DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[2]], TRUE, FALSE);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	//�X�L���i�[�̏ꏊ
	{
		if (g_player.skillcustom[0] != 0) {
			switch (g_player.skillcustom[0]) {
			case 1: DrawRotaGraph(83, 695, 1, 0,  g_pic.skillAicon[1], TRUE, FALSE);break;   //DrawCircle(85, 695, 30, 0xFF0000, TRUE); break;
			case 2: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE); break;
			case 3: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE); break;
			case 4: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE); break;
			case 5: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE); break;
			case 6: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE); break;
			case 7: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE); break;
			default: break;
			}
		}
		if (g_player.skillcustom[1] != 0) {
			switch (g_player.skillcustom[1]) {
			case 1: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[1], TRUE, FALSE); break;
			case 2: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE);  break;
			case 3: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE);  break;
			case 4: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE);  break;
			case 5: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE);  break;
			case 6: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE);  break;
			case 7: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE);  break;
			default: break;
			}
		}
		if (g_player.skillcustom[2] != 0) {
			switch (g_player.skillcustom[2]) {
			case 1: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[1], TRUE, FALSE); break;
			case 2: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE); break;
			case 3: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE); break;
			case 4: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE); break;
			case 5: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE); break;
			case 6: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE); break;
			case 7: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE); break;
			default: break;
			}
		}
	}*/
}


// �X�L���J�X�^�}�C�Y�̓���
void SkillCustom_Move() {
	static int comparation;				//���i�[
	static bool Storage = TRUE;

	//�X�L��������X�V
	for (int i = 0; i < g_select_MAX + 1; i++) skill_ReleaseFlg[i] = TRUE;

	/*if (Storage == TRUE) {
		for (int st_num = 0; st_num < 3; st_num++) g_player.skillcustom[g_set++] = 0, Storage = FALSE;
		g_set = 0;
	}*/
	if (Storage == TRUE) {
		//�O�̃X�L������ۑ�
		for (int i = 0; i < 3; i++) past_Skill[i] = g_player.skillcustom[i];

		if (g_player.skillcustom[g_set] != 0) {
			g_set++;
			if (g_set >= 3) {
				g_set = 0;
				Storage = FALSE;
				costomEndFlg = FALSE;
			}
		}
		else Storage = FALSE;
	}

	//�X�L���I��
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) if (++g_Skill_Num > 7) g_Skill_Num = 1;
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) 	if (--g_Skill_Num < 1) g_Skill_Num = 7;

	//�X�L������i���j
	//if ((g_keyInfo.keyFlg & PAD_INPUT_UP) && g_set < 3) {
	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_set < 3 && costomEndFlg == FALSE) {

		comparation = g_Skill_Num;


		/*if ((comparation != g_player.skillcustom[0])
			&& (comparation != g_player.skillcustom[1])
			&& (comparation != g_player.skillcustom[2])) {
			g_player.skillcustom[g_set++] = comparation;
		}*/
		if (skill_ReleaseFlg[comparation - 1] == TRUE) {
			if (g_set == 0) g_player.skillcustom[g_set++] = comparation;
			if (g_set == 1) {
				if (comparation != g_player.skillcustom[0])
					g_player.skillcustom[g_set++] = comparation;
			}
			if (g_set == 2) {
				if ((comparation != g_player.skillcustom[0])
					&& (comparation != g_player.skillcustom[1]))
					g_player.skillcustom[g_set++] = comparation;
			}
		}
	}

	//�X�L������(��)
	//if ((g_keyInfo.keyFlg & PAD_INPUT_DOWN) && g_set > 0) g_player.skillcustom[--g_set] = 0;
	if ((g_keyInfo.keyFlg & PAD_INPUT_2) && g_set > 0) g_player.skillcustom[--g_set] = 0;
	else if ((g_keyInfo.keyFlg & PAD_INPUT_2) && g_set == 0) {//B�A�łŃZ���N�g��ʂɖ߂�
		for (int i = 0; i < 3; i++) g_player.skillcustom[i] = past_Skill[i];
		//�X�L��������X�V
		for (int i = 0; i < 8; i++) skill_ReleaseFlg[i] = FALSE;
		g_gameScene = GAME_SELECT;
		Storage = TRUE;
		costomEndFlg = FALSE;
	}

	//�Z���N�g��ʂɖ߂�
	//if (g_keyInfo.keyFlg & PAD_INPUT_A) g_gameScene = GAME_SELECT,Storage = TRUE;

	//�Z���N�g��ʂɖ߂�
	if (costomEndFlg == TRUE && (g_keyInfo.keyFlg & PAD_INPUT_A)) {
		if (g_player.skillcustom[0] == 0) g_player.skillcustom[0] = 1; //�����������Ȃ������ꍇ�X�L���P������
		if (g_set == 1) g_player.skillcustom[1] = 0, g_player.skillcustom[2] = 0;
		if (g_set == 2)g_player.skillcustom[2] = 0;
		//�X�L��������X�V
		for (int i = 0; i < 7; i++) skill_ReleaseFlg[i] = FALSE;
		g_gameScene = GAME_SELECT;
		Storage = TRUE;
		costomEndFlg = FALSE;
	}
	//����L�����Z��
	if ((g_keyInfo.keyFlg & PAD_INPUT_2) && costomEndFlg == TRUE) costomEndFlg = FALSE;
	//����m�F
	if (g_set == 3 || g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		costomEndFlg = TRUE;
	}
}

void SkillChoice_Dis()
{
	static float animering = 0;

	for (g_choice.choice_num = 1; g_choice.choice_num < 8; g_choice.choice_num++) {
		DrawExtendGraph(g_choice.x[g_choice.choice_num],
			g_choice.y[g_choice.choice_num],
			g_choice.w[g_choice.choice_num],
			g_choice.h[g_choice.choice_num],
			g_pic.skillAicon[g_choice.choice_num], TRUE);
		if (skill_ReleaseFlg[g_choice.choice_num - 1] == FALSE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			SetDrawBright(0, 0, 0);
			DrawExtendGraph(g_choice.x[g_choice.choice_num],
				g_choice.y[g_choice.choice_num],
				g_choice.w[g_choice.choice_num],
				g_choice.h[g_choice.choice_num],
				g_pic.skillAicon[g_choice.choice_num], TRUE);
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	animering += 0.1F;
	DrawRotaGraph(633, 500, 2.6, animering, g_pic.skillRing[1], TRUE, FALSE);

	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) SkillAni_Plus();
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) SkillAni_Min();

}

void SkillAni_Plus() {
	int box = 7;

	g_choice.x_esc = g_choice.x[7];
	g_choice.y_esc = g_choice.y[7];
	g_choice.w_esc = g_choice.w[7];
	g_choice.h_esc = g_choice.h[7];

	for (int i = 8; i > 1; i--) {
		if (box + (i - 9) > 0) {
			g_choice.x_null = g_choice.x[box];
			g_choice.y_null = g_choice.y[box];
			g_choice.w_null = g_choice.w[box];
			g_choice.h_null = g_choice.h[box];

			g_choice.x[box + (i - 8)] = g_choice.x[box + (i - 9)];
			g_choice.y[box + (i - 8)] = g_choice.y[box + (i - 9)];
			g_choice.w[box + (i - 8)] = g_choice.w[box + (i - 9)];
			g_choice.h[box + (i - 8)] = g_choice.h[box + (i - 9)];

			g_choice.x[box + (i - 9)] = g_choice.x_null;
			g_choice.y[box + (i - 9)] = g_choice.y_null;
			g_choice.w[box + (i - 9)] = g_choice.w_null;
			g_choice.h[box + (i - 9)] = g_choice.h_null;
		}
		else {
			g_choice.x[1] = g_choice.x_esc;
			g_choice.y[1] = g_choice.y_esc;
			g_choice.w[1] = g_choice.w_esc;
			g_choice.h[1] = g_choice.h_esc;

			box = 7;
		}
	}
}

void SkillAni_Min() {
	int box = 1;//g_choice.mana_num;

	g_choice.x_esc = g_choice.x[1];
	g_choice.y_esc = g_choice.y[1];
	g_choice.w_esc = g_choice.w[1];
	g_choice.h_esc = g_choice.h[1];

	for (int i = 1; i < 8; i++) {
		if ((box + i) < 8) {
			g_choice.x_null = g_choice.x[box];
			g_choice.y_null = g_choice.y[box];
			g_choice.w_null = g_choice.w[box];
			g_choice.h_null = g_choice.h[box];

			g_choice.x[box + (i - 1)] = g_choice.x[box + i];
			g_choice.y[box + (i - 1)] = g_choice.y[box + i];
			g_choice.w[box + (i - 1)] = g_choice.w[box + i];
			g_choice.h[box + (i - 1)] = g_choice.h[box + i];

			g_choice.x[box + i] = g_choice.x_null;
			g_choice.y[box + i] = g_choice.y_null;
			g_choice.w[box + i] = g_choice.w_null;
			g_choice.h[box + i] = g_choice.h_null;
		}
		else {
			g_choice.x[7] = g_choice.x_esc;
			g_choice.y[7] = g_choice.y_esc;
			g_choice.w[7] = g_choice.w_esc;
			g_choice.h[7] = g_choice.h_esc;

			box = 1;
		}
	}
}
