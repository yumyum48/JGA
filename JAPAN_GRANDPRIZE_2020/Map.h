#pragma once
#include "DxLib.h"
#include "Struct.h"

extern mapInfo g_map[SCROLL_MAX];


void MapDisp();				// マップの表示
void MapMove();				// マップの動き
void MapInit();				// マップの初期化
void MapReset(int i);		// スクロールするマップをループさせる
void MapReset2(int i);		// スクロールするマップの背景をループさせる
int Scroll(int mapX, int speed);	// スクロール処理
