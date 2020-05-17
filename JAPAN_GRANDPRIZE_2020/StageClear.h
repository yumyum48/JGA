#pragma once
#include "DxLib.h"

void StageClear();				// ステージクリア関数の管理
void StageClearDisp();			// ステージクリアの表示
void StageClearMove();			// ステージクリアの動き
int Player_StageClearMove();	// ステージクリア時のプレイヤーの動き
int ClearTextMove();			// [討伐完了]の画像のアニメーション
void StageClearInit();			// ステージクリア画面の初期化
