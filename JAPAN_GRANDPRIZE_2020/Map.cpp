#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Boss.h"

#define SCREEN_WIDTH (250 * 2.0F)	// ��ʂ̉���
#define SCROLL_SPEED (8.0F)	// �}�b�v�̃X�N���[������X�s�[�h

mapInfo g_backmap[SCROLL_MAX];		// �}�b�v�w�i�̕`��

// �}�b�v�̕\��
void MapDisp() {
	
	// �}�b�v�̕`��
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_backmap[i].x, g_backmap[i].y, 0, 0, 2.0, 0.0, g_pic.backMap[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}
	
}

// �}�b�v�̓���
void MapMove() {

	// �X�N���[������
	for (int i = 0; i < SCROLL_MAX; i++) {

		g_map[i].x = Scroll(g_map[i].x, g_speedLevel);
		if (g_map[i].x + SCREEN_WIDTH <= 0) {
			MapReset(i);								// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
		}

		if(g_select_Stage != BOSS_LASTBOSS)
			g_backmap[i].x = Scroll(g_backmap[i].x, 3);	// �Z���N�g���ꂽ��ʂ��{�X�ȊO�Ȃ獶����E�֔w�i��������蓮����
		if (g_backmap[i].x + SCREEN_WIDTH <= 0) {
			MapReset2(i);							// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
		}
	}


}

void MapReset(int i) {
	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	
	int max = g_map[0].x;	// ��ԍŌ�̉摜��X���W���i�[
	for (int j = 0; j < SCROLL_MAX; j++) {// ��ԍŌ�̉摜��T������
		if (g_map[j].x > max) {
			max = g_map[j].x;	// ��ԍŌ�̉摜���������max�Ɋi�[
		}
	}
	g_map[i].x = max + SCREEN_WIDTH;	// ��ԍŌ�̉摜�̌�ɍ��W���ړ�
	if (i == 0) {
		g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;	// ��ԍŏ��̉摜�͈ړ��������}�C�i�X
	}
}

void MapReset2(int i) {
	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	
	int max = g_backmap[0].x;	// ��ԍŌ�̉摜��X���W���i�[
	for (int j = 0; j < SCROLL_MAX; j++) {// ��ԍŌ�̉摜��T������

		if (g_backmap[j].x > max) {
			max = g_backmap[j].x;	// ��ԍŌ�̉摜���������max�Ɋi�[
		}
	}
	g_backmap[i].x = max + SCREEN_WIDTH;	// ��ԍŌ�̉摜�̌�ɍ��W���ړ�
	if (i == 0) {
		g_backmap[i].x = max + SCREEN_WIDTH - g_speedLevel;	// ��ԍŏ��̉摜�͈ړ��������}�C�i�X
	}
}
// �X�N���[�����Z����
int Scroll(int mapX, int speed) {
	//float moveX = SCROLL_SPEED;
	
	
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