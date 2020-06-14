#pragma once
#include "DxLib.h"

extern bool g_animationScene;	// アニメーションを終了させてテキストを表示させるフラグ	TRUE:テキストの表示ON	FALSE:ボスを撃破するアニメーション

void StageClear();				// ステージクリア関数の管理
void StageClearDisp();			// ステージクリアの表示
void StageClearMove();			// ステージクリアの動き
int Player_StageClearMove();	// ステージクリア時のプレイヤーの動き
int ClearTextMove();			// [討伐完了]の画像のアニメーション
void StageClearInit();			// ステージクリア画面の初期化
void BossDefeatAnimationDisp();	// ボス撃破時のアニメーション描画
void BossDefeatAnimationMove();	// ボス撃破時のアニメーション内部処理