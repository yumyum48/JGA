#include "DxLib.h"
#include "SkillCustom.h"
#include "GameScene.h"
#include "control.h"
#include "Struct.h"
#include "Player.h"
#include "Sounds.h"

static int g_Skill_Num = 1;	//�I�����Ă���X�L���ԍ�
int g_set = 0;			//�Z�b�g�����ԍ�

void SkillCustom() {
	SkillCustom_Move();
	SkillCustom_Disp();

}

// �X�L���J�X�^�}�C�Y�̕\��
void SkillCustom_Disp() {

	//�f�o�b�O�p
	DrawFormatString(0, 60, 0xFFFFFF, "%d", g_player.skillcustom[0]);
	DrawFormatString(10, 60, 0xFFFFFF, "%d", g_player.skillcustom[1]);
	DrawFormatString(20, 60, 0xFFFFFF, "%d", g_player.skillcustom[2]);
	DrawFormatString(0, 80, 0xFFFFFF, "%d", g_Skill_Num);

	DrawFormatString(0, 100, 0xFFFFFF, "%d", g_set);

	//���m�点�p
	DrawString(800, 800, "���{�^���ŃX�L������", 0xFFFFFF);
	DrawString(800, 900, "���{�^���ŃX�L������", 0xFFFFFF);

	//�X�L���I��������
	DrawCircle(600, 450, 100, 0xFF0000, TRUE);			//�X�L���P
	DrawCircle(330, 380, 70, 0x00FF00, TRUE);			//�X�L���Q
	DrawCircle(240, 230, 40, 0xFFFF00, TRUE);			//�X�L���R
	DrawCircle(450, 145, 20, 0xFF00FF, TRUE);			//�X�L���S
	DrawCircle(805, 145, 20, 0x00FFFF, TRUE);			//�X�L���T
	DrawCircle(1000, 230, 40, 0xFFFFFF, TRUE);			//�X�L���U
	DrawCircle(870, 380, 70, 0x0000FF, TRUE);			//�X�L���V

	DrawBox(35, 650, 280, 735, 0xFFFFFF, FALSE);

	//�X�L���i�[�̏ꏊ
	{
		if (g_player.skillcustom[0] != 0) {
			switch (g_player.skillcustom[0]) {
			case 1: DrawCircle(85, 695, 30, 0xFF0000, TRUE); break;
			case 2: DrawCircle(85, 695, 30, 0x00FF00, TRUE); break;
			case 3: DrawCircle(85, 695, 30, 0xFFFF00, TRUE); break;
			case 4: DrawCircle(85, 695, 30, 0xFF00FF, TRUE); break;
			case 5: DrawCircle(85, 695, 30, 0x00FFFF, TRUE); break;
			case 6: DrawCircle(85, 695, 30, 0xFFFFFF, TRUE); break;
			case 7: DrawCircle(85, 695, 30, 0x0000FF, TRUE); break;
			default: break;
			}
		}
		if (g_player.skillcustom[1] != 0) {
			if (g_player.skillcustom[0] != g_player.skillcustom[1]) {
				switch (g_player.skillcustom[1]) {
				case 1: DrawCircle(155, 695, 30, 0xFF0000, TRUE); break;
				case 2: DrawCircle(155, 695, 30, 0x00FF00, TRUE); break;
				case 3: DrawCircle(155, 695, 30, 0xFFFF00, TRUE); break;
				case 4: DrawCircle(155, 695, 30, 0xFF00FF, TRUE); break;
				case 5: DrawCircle(155, 695, 30, 0x00FFFF, TRUE); break;
				case 6: DrawCircle(155, 695, 30, 0xFFFFFF, TRUE); break;
				case 7: DrawCircle(155, 695, 30, 0x0000FF, TRUE); break;
				default: break;
				}
			}
		}
		if (g_player.skillcustom[2] != 0) {
			if (g_player.skillcustom[0] != g_player.skillcustom[2]
				&& g_player.skillcustom[1] != g_player.skillcustom[2]) {
				switch (g_player.skillcustom[2]) {
				case 1: DrawCircle(225, 695, 30, 0xFF0000, TRUE); break;
				case 2: DrawCircle(225, 695, 30, 0x00FF00, TRUE); break;
				case 3: DrawCircle(225, 695, 30, 0xFFFF00, TRUE); break;
				case 4: DrawCircle(225, 695, 30, 0xFF00FF, TRUE); break;
				case 5: DrawCircle(225, 695, 30, 0x00FFFF, TRUE); break;
				case 6: DrawCircle(225, 695, 30, 0xFFFFFF, TRUE); break;
				case 7: DrawCircle(225, 695, 30, 0x0000FF, TRUE); break;
				default: break;
				}
			}
		}
	}
}


// �X�L���J�X�^�}�C�Y�̓���
void SkillCustom_Move() {
	int g_kari;				//���i�[

	//�X�L���I��
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) if (++g_Skill_Num > 7) g_Skill_Num = 1;
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) 	if (--g_Skill_Num < 1) g_Skill_Num = 7;

	//�X�L������i���j
	if ((g_keyInfo.keyFlg & PAD_INPUT_UP) && g_set < 3) {
		
		g_kari = g_Skill_Num;
		
		if ((g_kari != g_player.skillcustom[0])
			&& (g_kari != g_player.skillcustom[1])
			&& (g_kari != g_player.skillcustom[2])) {
			g_player.skillcustom[g_set++] = g_kari;
		}
	}

	//�X�L������(��)
	if ((g_keyInfo.keyFlg & PAD_INPUT_DOWN) && g_set > 0) g_player.skillcustom[--g_set] = 0;
	
	if (g_keyInfo.keyFlg & PAD_INPUT_A) g_gameScene = GAME_SELECT;
}
