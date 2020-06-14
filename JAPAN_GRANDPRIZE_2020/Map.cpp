#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Boss.h"
#include "StageClear.h"

#define SCREEN_WIDTH (250 * 2.0F)	// 画面の横幅
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード

#define UI_Gl_X	45   //ボタンのｘ座標の起点
#define UI_Gl_Y	160   //ボタンのY座標の起点


mapInfo g_backmap[SCROLL_MAX];

// マップの表示
void MapDisp() {
	
	
	// マップの描画
	for (int i = 0; i < SCROLL_MAX; i++) {

		DrawRotaGraph2(g_backmap[i].x, g_backmap[i].y, 0, 0, 2.0, 0.0, g_pic.backMap[(SCROLL_MAX * g_select_Stage) + i], TRUE);
		//DrawFormatString(100, 100, 0xFF0000, "%d", g_game_stage);
		
		
	}

	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}


	//ボタンのUI

	if (g_animationScene) {			//ボスのHPってなんですかねぇ？
		// 描画ブレンドモードをアルファブレンド（５０％）にする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);

		DrawBox(UI_Gl_X - 10, UI_Gl_Y - 10, UI_Gl_X + 320, UI_Gl_Y + 130, 0xffffff, TRUE);

		//描画ブレンドモードを元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaGraph2(UI_Gl_X, UI_Gl_Y, 0, 0, 0.65, 0.0, g_pic.button[1], TRUE);		//ボタンの描画（B）
		DrawRotaGraph2(UI_Gl_X, UI_Gl_Y + 60, 0, 0, 0.65, 0.0, g_pic.button[2], TRUE);		//ボタンの描画（A）
		//DrawFormatString(100, 100, 0x000000, "X : %d  Y : %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);

		SetFontSize(55);
		DrawFormatString(UI_Gl_X + 60, UI_Gl_Y, 0x000000, "剣技発動");		//UIの文字(↓同)
		DrawFormatString(UI_Gl_X + 60, UI_Gl_Y + 60, 0x000000, "ジャンプ");
	}
	
	
}

// マップの動き
void MapMove() {
	for (int i = 0; i < SCROLL_MAX; i++) {
		g_map[i].x = Scroll(g_map[i].x, g_speedLevel);
		if (g_map[i].x + SCREEN_WIDTH <= 0) {
			MapReset(i);                                // リセット
		}

		g_backmap[i].x = Scroll(g_backmap[i].x, 3);
		if (g_backmap[i].x + SCREEN_WIDTH <= 0) {
			MapReset2(i);								// リセット
		}
	}

}

void MapReset(int i) {
	// マップが画面外に入ったら次のところにセットされる
	int max = g_map[0].x;    // 一旦マックスに数字を入れる
	for (int j = 0; j < SCROLL_MAX; j++) {// スクロールさせる回数ループ
		if (g_map[j].x > max) {
			max = g_map[j].x;    // 一番x座標が遠い場所を記憶
		}
	}
	g_map[i].x = max + SCREEN_WIDTH;    // 遠い場所の次に画像をセット
	if (i == 0) {
		g_map[i].x = max + SCREEN_WIDTH - g_speedLevel;    // スクロールでずれた分は、移動量を引いて修正
	}
}

void MapReset2(int i) {
	// マップが画面外に入ったら次のところにセットされる
	int max = g_backmap[0].x;    //一旦マックスに数字を入れる
	for (int j = 0; j < SCROLL_MAX; j++) {//スクロールさせる回数ループ
		if (g_backmap[j].x > max) {
			max = g_backmap[j].x;    // 一番x座標が遠い場所を記憶
		}
	}
	g_backmap[i].x = max + SCREEN_WIDTH;    // 遠い場所の次に画像をセット
	if (i == 0) {
		g_backmap[i].x = max + SCREEN_WIDTH - g_speedLevel;    // スクロールでずれた分は、移動量を引いて修正
	}
}
// スクロール加算処理
int Scroll(int mapX, int speed) {

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