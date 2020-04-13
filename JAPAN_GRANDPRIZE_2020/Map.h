#pragma once
#include "Struct.h"

#define SCROLL_MAX  (3)		// スクロール画像の最大数
#define MAP_MAX		(8)		// マップの数

void MapDisp();				// マップの表示
void MapMove();				// マップの動き
void MapInit();				// マップの初期化
void Scroll(float* mapX);	// スクロール処理