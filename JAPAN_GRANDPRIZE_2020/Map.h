#pragma once
#define SCROLL_MAX  (3)
#define MAP_MAX		(8)

extern int g_stageInput;

void MapDisp();	// マップの表示
void MapMove();	// マップの動き
void MapInit();	// マップの初期化
void Scroll(float* mapX);	// スクロール処理