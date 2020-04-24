#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"

#define SCREEN_WIDTH (250 * 2.0F)	// ��ʂ̉���
#define SCROLL_SPEED (8.0F)	// �}�b�v�̃X�N���[������X�s�[�h
mapInfo g_map[SCROLL_MAX];

// �}�b�v�̕\��
void MapDisp() {
	
	DrawRotaGraph2(0, 0, 0, 0, 2.0, 0.0, g_pic.backMap, TRUE);
	// �}�b�v�̕`��
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[((g_game_stage)*4)+i], TRUE);
		//DrawFormatString(100, 100, 0xFF0000, "%d", g_game_stage);
		
		
	}

	
}

// �}�b�v�̓���
void MapMove() {

	// �X�N���[������
	for (int i = 0; i < SCROLL_MAX; i++) {
		Scroll(&g_map[i].x);

		
		MapReset(i);	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	}



}

void MapReset(int i) {
	// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
	if (g_map[i].x + SCREEN_WIDTH <= 0) {
		int max = g_map[0].x;	// ��ԍŌ�̉摜��X���W���i�[
		for (int j = 1; j < SCROLL_MAX; j++) {// ��ԍŌ�̉摜��T������

			if (g_map[j].x > max) {
				max = g_map[j].x;	// ��ԍŌ�̉摜���������max�Ɋi�[
			}
		}
		g_map[i].x = max + SCREEN_WIDTH;	// ��ԍŌ�̉摜�̌�ɍ��W���ړ�
		if (i == 0) {
			g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;	// ��ԍŏ��̉摜�͈ړ��������}�C�i�X
		}
	}
}

// �X�N���[�����Z����
void Scroll(float *mapX) {
	//float moveX = SCROLL_SPEED;
	
	
	*mapX -= g_speedLevel;
}

// �}�b�v�f�[�^�̏�����
void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
	g_map[3].MapInit4();
}