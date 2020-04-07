#include "DxLib.h"
#include "Struct.h"
extern image g_pic;

int LoadPicture() {
	if ((g_pic.Block = LoadGraph("image/block.bmp")) == -1) return -1;
	if ((g_pic.QBlock = LoadGraph("image/Qblock.jpg")) == -1) return -1;
	if ((g_pic.Kirby = LoadGraph("image/KirbyN.png")) == -1) return -1;
	if (LoadDivGraph("image/mori_4.png", 3, 3, 1, 1024, 768, g_pic.map, 0) == -1)
		return -1;
	
	if ((g_pic.Block = LoadGraph("image/block.bmp")) == -1) return -1;
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/
	return 0;
}