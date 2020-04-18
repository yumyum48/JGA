#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"

#define SCREEN_WIDTH (1024)	// 画面の横幅
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード
mapInfo g_map[SCROLL_MAX];

// マップの表示
void MapDisp() {


	// マップの描画
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawGraph(g_map[i].x, g_map[i].y, g_pic.map[((g_game_stage)*3)+i], TRUE);
		//DrawFormatString(100, 100, 0xFF0000, "%d", g_game_stage);
		// マップが画面外に入ったら次のところにセットされる
		if (g_map[i].x + SCREEN_WIDTH < 0) {
			g_map[i].x = SCREEN_WIDTH + SCREEN_WIDTH - g_speedLevel;	// 移動分の量を引く
		}
	}

	
}
// マップの動き
void MapMove() {

	// スクロール処理
	for(int i = 0; i < SCROLL_MAX; i++)
		Scroll(&g_map[i].x);


}

// スクロール加算処理
void Scroll(float *mapX) {
	//float moveX = SCROLL_SPEED;
	float moveX = g_speedLevel;
	
	*mapX -= moveX;
}

// マップデータの初期化
void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
}