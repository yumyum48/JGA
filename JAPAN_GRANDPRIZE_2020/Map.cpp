#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Boss.h"
#include "StageClear.h"

#define SCREEN_WIDTH (250 * 2.0F)	// ��ʂ̉���
#define SCROLL_SPEED (8.0F)	// �}�b�v�̃X�N���[������X�s�[�h

#define UI_Gl_X	45   //�{�^���̂����W�̋N�_
#define UI_Gl_Y	160   //�{�^����Y���W�̋N�_


mapInfo g_backmap[SCROLL_MAX];

// �}�b�v�̕\��
void MapDisp() {
	
	
	// �}�b�v�̕`��
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawRotaGraph2(g_backmap[i].x, g_backmap[i].y, 0, 0, 2.0, 0.0, g_pic.backMap[(SCROLL_MAX * g_select_Stage) + i], TRUE);
		//DrawFormatString(100, 100, 0xFF0000, "%d", g_game_stage);
		
		
	}

	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}


	//�{�^����UI

	if (g_animationScene) {			//�{�X��HP���ĂȂ�ł����˂��H
		// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);

		DrawBox(UI_Gl_X - 10, UI_Gl_Y - 10, UI_Gl_X + 320, UI_Gl_Y + 130, 0xffffff, TRUE);

		//�`��u�����h���[�h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaGraph2(UI_Gl_X, UI_Gl_Y, 0, 0, 0.65, 0.0, g_pic.button[1], TRUE);		//�{�^���̕`��iB�j
		DrawRotaGraph2(UI_Gl_X, UI_Gl_Y + 60, 0, 0, 0.65, 0.0, g_pic.button[2], TRUE);		//�{�^���̕`��iA�j
		//DrawFormatString(100, 100, 0x000000, "X : %d  Y : %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);

		SetFontSize(55);
		DrawFormatString(UI_Gl_X + 60, UI_Gl_Y, 0x000000, "���Z����");		//UI�̕���(����)
		DrawFormatString(UI_Gl_X + 60, UI_Gl_Y + 60, 0x000000, "�W�����v");
	}
	
	
}

// �}�b�v�̓���
void MapMove() {
	for (int i = 0; i < SCROLL_MAX; i++) {
		g_map[i].x = Scroll(g_map[i].x, g_speedLevel);
		if (g_map[i].x + SCREEN_WIDTH <= 0) {
			MapReset(i);                                // ���Z�b�g
		}

		g_backmap[i].x = Scroll(g_backmap[i].x, 3);
		if (g_backmap[i].x + SCREEN_WIDTH <= 0) {
			MapReset2(i);								// ���Z�b�g
		}
	}

}

void MapReset(int i) {
	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	int max = g_map[0].x;    // ��U�}�b�N�X�ɐ���������
	for (int j = 0; j < SCROLL_MAX; j++) {// �X�N���[��������񐔃��[�v
		if (g_map[j].x > max) {
			max = g_map[j].x;    // ���x���W�������ꏊ���L��
		}
	}
	g_map[i].x = max + SCREEN_WIDTH;    // �����ꏊ�̎��ɉ摜���Z�b�g
	if (i == 0) {
		g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;    // �X�N���[���ł��ꂽ���́A�ړ��ʂ������ďC��
	}
}

void MapReset2(int i) {
	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	int max = g_backmap[0].x;    //��U�}�b�N�X�ɐ���������
	for (int j = 0; j < SCROLL_MAX; j++) {//�X�N���[��������񐔃��[�v
		if (g_backmap[j].x > max) {
			max = g_backmap[j].x;    // ���x���W�������ꏊ���L��
		}
	}
	g_backmap[i].x = max + SCREEN_WIDTH;    // �����ꏊ�̎��ɉ摜���Z�b�g
	if (i == 0) {
		g_backmap[i].x = max + SCREEN_WIDTH - g_speedLevel;    // �X�N���[���ł��ꂽ���́A�ړ��ʂ������ďC��
	}
}
// �X�N���[�����Z����
int Scroll(int mapX, int speed) {

	return mapX -= speed;

}

// �}�b�v�f�[�^�̏�����
void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
	g_map[3].MapInit4();

	g_backmap[0].MapInit1();
	g_backmap[1].MapInit2();
	g_backmap[2].MapInit3();
	g_backmap[3].MapInit4();
}