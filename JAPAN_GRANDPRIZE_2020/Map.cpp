#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

extern image g_pic;
mapInfo g_map[3];
// �}�b�v�̕\��
void MapDisp() {


	// �}�b�v�̕`��
	DrawGraph(g_map[0].x, g_map[0].y, g_pic.map[0], TRUE);
	DrawGraph(g_map[1].x, g_map[1].y, g_pic.map[1], TRUE);
	DrawGraph(g_map[2].x, g_map[2].y, g_pic.map[2], TRUE);
}
// �}�b�v�̓���
void MapMove() {

	//if()
}

void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
}