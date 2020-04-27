#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "control.h"
#include "Map.h"
#include "Select.h"
#include "Rain.h"
//#include "ScroolDown.h"
#define SCROLL_SPEED (8.0F)	// マップのスクロールするスピード


rainInfo g_rain[2];

void RainDisp(){
	DrawGraph(g_rain[1].x, g_rain[1].y, g_pic.rain, TRUE);
	DrawGraph(g_rain[0].x, g_rain[0].y, g_pic.rain, TRUE);
}

void RainMove() {
	const int rainSpead = 10;

	g_rain[0].x -= SCROLL_SPEED;
	g_rain[1].x -= SCROLL_SPEED;
	g_rain[0].y += SCROLL_SPEED;
	g_rain[1].y += SCROLL_SPEED;

	if (g_rain[0].y > 0)g_rain[0].RainInit1();
	if (g_rain[1].y > 0)g_rain[1].RainInit1();
}

void RainInit() {
	g_rain[0].RainInit1();
	g_rain[1].RainInit1();
}