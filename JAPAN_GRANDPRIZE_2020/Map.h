#pragma once
#include "Struct.h"

#define SCROLL_MAX  (4)		// スクロール画像の最大数
#define MAP_MAX		(8)		// マップの数

void MapDisp();				// マップの表示
void MapMove();				// マップの動き
void MapInit();				// マップの初期化
void MapReset(int i);		// スクロールするマップをループさせる
void MapReset2(int i);		// スクロールするマップの背景をループさせる
void Scroll(float* mapX, int speed);	// スクロール処理
