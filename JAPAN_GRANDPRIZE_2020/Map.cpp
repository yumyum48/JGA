#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"

#define SCREEN_WIDTH (1024)	// ��ʂ̉���
#define SCROLL_SPEED (8.0F)	// �}�b�v�̃X�N���[������X�s�[�h
mapInfo g_map[SCROLL_MAX];

// �}�b�v�̕\��
void MapDisp() {


	// �}�b�v�̕`��
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawGraph(g_map[i].x, g_map[i].y, g_pic.map[((1-1)*3)+i], TRUE);
		
		// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
		if (g_map[i].x + SCREEN_WIDTH < 0) {
			g_map[i].x = SCREEN_WIDTH + SCREEN_WIDTH - 8;
		}
	}

	
}
// �}�b�v�̓���
void MapMove() {

	// �X�N���[������
	for(int i = 0; i < SCROLL_MAX; i++)
		Scroll(&g_map[i].x);


}

// �X�N���[�����Z����
void Scroll(float *mapX) {
	float moveX = SCROLL_SPEED;
	
	*mapX -= moveX;
}

// �}�b�v�f�[�^�̏�����
void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
}