#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Boss.h"

#define SCREEN_WIDTH (250 * 2.0F)	// 画面の横幅
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード

mapInfo g_backmap[SCROLL_MAX];		// マップ背景の描画

// マップの表示
void MapDisp() {
	
	// マップの描画
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_backmap[i].x, g_backmap[i].y, 0, 0, 2.0, 0.0, g_pic.backMap[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}
	
}

// マップの動き
void MapMove() {

	// スクロール処理
	for (int i = 0; i < SCROLL_MAX; i++) {

		g_map[i].x = Scroll(g_map[i].x, g_speedLevel);
		if (g_map[i].x + SCREEN_WIDTH <= 0) {
			MapReset(i);								// マップが画面外に入ったら次のところにセットされる
		}

		if(g_select_Stage != BOSS_LASTBOSS)
			g_backmap[i].x = Scroll(g_backmap[i].x, 3);	// セレクトされた画面がボス以外なら左から右へ背景をゆっくり動かす
		if (g_backmap[i].x + SCREEN_WIDTH <= 0) {
			MapReset2(i);							// マップが画面外に入ったら次のところにセットされる
		}
	}


}

void MapReset(int i) {
	// マップが画面外に入ったら次のところにセットされる
	
	int max = g_map[0].x;	// 一番最後の画像のX座標を格納
	for (int j = 0; j < SCROLL_MAX; j++) {// 一番最後の画像を探索処理
		if (g_map[j].x > max) {
			max = g_map[j].x;	// 一番最後の画像を見つけるとmaxに格納
		}
	}
	g_map[i].x = max + SCREEN_WIDTH;	// 一番最後の画像の後に座標を移動
	if (i == 0) {
		g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;	// 一番最初の画像は移動分だけマイナス
	}
}

void MapReset2(int i) {
	// マップが画面外に入ったら次のところにセットされる
	
	int max = g_backmap[0].x;	// 一番最後の画像のX座標を格納
	for (int j = 0; j < SCROLL_MAX; j++) {// 一番最後の画像を探索処理

		if (g_backmap[j].x > max) {
			max = g_backmap[j].x;	// 一番最後の画像を見つけるとmaxに格納
		}
	}
	g_backmap[i].x = max + SCREEN_WIDTH;	// 一番最後の画像の後に座標を移動
	if (i == 0) {
		g_backmap[i].x = max + SCREEN_WIDTH - g_speedLevel;	// 一番最初の画像は移動分だけマイナス
	}
}
// スクロール加算処理
int Scroll(int mapX, int speed) {
	//float moveX = SCROLL_SPEED;
	
	
	return mapX -= speed;
}

// マップデータの初期化
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