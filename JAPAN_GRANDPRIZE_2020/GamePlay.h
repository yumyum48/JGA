#pragma once
#include "DxLib.h"

extern int g_enemybeat;	// エネミーを倒した数をカウントするグローバル変数

void GamePlay();		// ゲームプレイのメイン関数
void GamePlayDisp();	// ゲームプレイ中の描画処理
void GamePlayMove();	// ゲームプレイ中の動きの処理
void MapDisp();			// マップの描画
void PlayerDisp();		// プレイヤーの描画
void PlayerMove();		// プレイヤーの動き

