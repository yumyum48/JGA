#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "Boss.h"
#include "Select.h"
#include "Init.h"
#include "HP.h"
#include "Trap.h"

// ゲームプレイのメイン関数
void GamePlay() {
	// デバッグ用で一旦入れ替えGamePlayMove();
	GamePlayMove();
	GamePlayDisp();

	static int timecnt = 0;	// フレーム単位で加算する
	if (timecnt++ >= 60) {
		g_playTime++;	// プレイタイムを加算
		timecnt = 0;
	}
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	MapDisp();						// マップの描画
	MonsterDisp();					// 弱い敵、ボスの表示
	
	PlayerDisp();					// プレイヤーの描画
	RainDisp();						// 雨の描画

#ifndef DEBUG_TRAP_ON
	TrapDisp();						// トラップの表示
#endif // DEBUG_TRAP_ON

	HpDisp();						// HP表示処理
	
	LastBossRightNingAnime();		// ラスボス前の７体の蛇の出現アニメーション
}

// ゲームプレイの動き
void GamePlayMove() {
	MapMove();						// マップの動き
	MonsterMove();					// 弱い敵、ボスの動き
	
	PlayerMove();					// プレイヤーの動き
	RainMove();						// 雨の動き

#ifndef EBUG_TRAP_ON
	TrapMove();						// トラップの動き
#endif // EBUG_TRAP_ON
#ifdef DEBUG_LEVEL_OFF
	HpMove();						// HPの計算処理
#endif // DEBUG_LEVEL_OFF
}



