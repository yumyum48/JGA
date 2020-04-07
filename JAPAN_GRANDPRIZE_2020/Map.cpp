#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"

#define MAP_MAX		 (3)	// �}�b�v�̍ő吔
#define SCREEN_WIDTH (1024)	// ��ʂ̉���

mapInfo g_map[3];
// �}�b�v�̕\��
void MapDisp() {


	// �}�b�v�̕`��
	for (int i = 0; i < MAP_MAX; i++) {
		DrawGraph(g_map[i].x, g_map[i].y, g_pic.map[i], TRUE);
		
		// �}�b�v����ʊO�ɓ������玟�̂Ƃ���ɃZ�b�g�����
		if (g_map[i].x + SCREEN_WIDTH < 0) {
			g_map[i].x = SCREEN_WIDTH + SCREEN_WIDTH;
		}
	}

	
}
// �}�b�v�̓���
void MapMove() {

	// �X�N���[������
	if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
		for(int i=0; i<MAP_MAX; i++)
			Scroll(&g_map[i].x);
	}


}

void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
}

void Scroll(int *mapX) {
	int moveX = 8;
	
	*mapX -= moveX;
}