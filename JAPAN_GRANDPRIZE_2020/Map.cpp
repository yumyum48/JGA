#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Boss.h"

#define SCREEN_WIDTH (250 * 2.0F)	// ��ʂ̉���
#define SCROLL_SPEED (8.0F)	// �}�b�v�̃X�N���[������X�s�[�h

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