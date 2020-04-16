#pragma once
#include "DxLib.h"

void PlayerDisp();						// プレイヤーの描画
void PlayerMove();						// プレイヤーの動き
void PlayerInit();						// プレイヤーの初期化
void PlayerJump();						// プレイヤーのジャンプ処理
void PlayerControl();					// プレイヤーを操作する処理
void EnemyLockOn();						// プレイヤーの間合いに入っている敵をロックオン
int PicHitCheck(int ex, int ey);		// プレイヤーと敵の判定を確認する処理
void EnemyCut();						// 間合いに入っている敵を倒す処理


