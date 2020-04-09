#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Rain.h"
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード


rainInfo g_rain[2];

void RainDisp(){
	DrawGraph(g_rain[1].x, g_rain[1].y, g_pic.rain[1], TRUE);
	DrawGraph(g_rain[0].x, g_rain[0].y, g_pic.rain[0], TRUE);
}

void RainMove() {
	const int rainSpead = 10;

	g_rain[0].x -= SCROLL_SPEED;
	g_rain[1].x -= SCROLL_SPEED;
	g_rain[0].y += SCROLL_SPEED;
	g_rain[1].y += SCROLL_SPEED;

	if (g_rain[0].y > 0)g_rain[0].RainInit2();
	if (g_rain[1].y > 0)g_rain[1].RainInit2();
}

void RainInit() {
	g_rain[0].RainInit1();
	g_rain[1].RainInit2();
}


/////////
/// GamePlay.cpp のゲームプレイの描画動きに RainDisp();、RainMove(); をそれぞれ追加

/// Init.cpp の GameInit() に RainInit(); を追加

/*  loadPic.cpp の LoadPicture() に
	   if ((g_pic.rain[0] = LoadGraph("image/RainLarge.png")) == -1) return -1;
	   if ((g_pic.rain[1] = LoadGraph("image/RainLarge.png")) == -1) return -1;
	を追加 */

/*  Struct.h に
// 雨の情報
struct rainInfo {
	int x, y;
	void RainInit1() {
		x = 0;
		y = -768;
	}
	void RainInit2() {
		x = 0;
		y = -768;
	}
};
   を追加 */