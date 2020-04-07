#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"

#define MAP_MAX		 (3)	// マップの最大数
#define SCREEN_WIDTH (1024)	// 画面の横幅

mapInfo g_map[3];
// マップの表示
void MapDisp() {


	// マップの描画
	for (int i = 0; i < MAP_MAX; i++) {
		DrawGraph(g_map[i].x, g_map[i].y, g_pic.map[i], TRUE);
		
		// マップが画面外に入ったら次のところにセットされる
		if (g_map[i].x + SCREEN_WIDTH < 0) {
			g_map[i].x = SCREEN_WIDTH + SCREEN_WIDTH;
		}
	}

	
}
// マップの動き
void MapMove() {

	// スクロール処理
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