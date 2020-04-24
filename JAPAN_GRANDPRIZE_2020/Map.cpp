#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"

#define SCREEN_WIDTH (250 * 2.0F)	// 画面の横幅
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード
mapInfo g_map[SCROLL_MAX];

// マップの表示
void MapDisp() {
	
	DrawRotaGraph2(0, 0, 0, 0, 2.0, 0.0, g_pic.backMap, TRUE);
	// マップの描画
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[((g_game_stage)*4)+i], TRUE);
		//DrawFormatString(100, 100, 0xFF0000, "%d", g_game_stage);
		
		
	}

	
}

// マップの動き
void MapMove() {

	// スクロール処理
	for (int i = 0; i < SCROLL_MAX; i++) {
		Scroll(&g_map[i].x);

		
		MapReset(i);	// マップが画面外に入ったら次のところにセットされる
	}



}

void MapReset(int i) {
	// マップが画面外に入ったら次のところにセットされる
	if (g_map[i].x + SCREEN_WIDTH <= 0) {
		int max = g_map[0].x;	// 一番最後の画像のX座標を格納
		for (int j = 1; j < SCROLL_MAX; j++) {// 一番最後の画像を探索処理

			if (g_map[j].x > max) {
				max = g_map[j].x;	// 一番最後の画像を見つけるとmaxに格納
			}
		}
		g_map[i].x = max + SCREEN_WIDTH;	// 一番最後の画像の後に座標を移動
		if (i == 0) {
			g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;	// 一番最初の画像は移動分だけマイナス
		}
	}
}

// スクロール加算処理
void Scroll(float *mapX) {
	//float moveX = SCROLL_SPEED;
	
	
	*mapX -= g_speedLevel;
}

// マップデータの初期化
void MapInit() {
	g_map[0].MapInit1();
	g_map[1].MapInit2();
	g_map[2].MapInit3();
	g_map[3].MapInit4();
}