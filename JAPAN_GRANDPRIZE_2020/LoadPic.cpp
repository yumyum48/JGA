#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {
	if ((g_pic.Block = LoadGraph("image/block.bmp")) == -1) return -1;
	if ((g_pic.QBlock = LoadGraph("image/Qblock.jpg")) == -1) return -1;
	if ((g_pic.player[0] = LoadGraph("image/1.png")) == -1) return -1;
	if ((g_pic.player[1] = LoadGraph("image/2.png")) == -1) return -1;
	if ((g_pic.player[2] = LoadGraph("image/3.png")) == -1) return -1;
	if ((g_pic.enemy = LoadGraph("image/enemy.png")) == -1) return -1;
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;
	
	if ((g_pic.Block = LoadGraph("image/block.bmp")) == -1) return -1;
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/
	return 0;
}