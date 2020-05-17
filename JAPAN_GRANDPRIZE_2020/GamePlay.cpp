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
	GamePlayDisp();
	GamePlayMove();
	static int timecnt;	// フレーム単位で加算する
	if(timecnt++ >= 60)g_playTime++;	// プレイタイムを加算
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	MapDisp();						// マップの描画
	MonsterDisp();					// 弱い敵、ボスの表示
	
	PlayerDisp();					// プレイヤーの描画
	RainDisp();						// 雨の描画
	TrapDisp();						// トラップの表示
	HpDisp();						// HP表示処理
	
}

// ゲームプレイの動き
void GamePlayMove() {
	MapMove();						// マップの動き
	MonsterMove();					// 弱い敵、ボスの動き
	
	PlayerMove();					// プレイヤーの動き
	RainMove();						// 雨の動き
	TrapMove();						// トラップの動き
	HpMove();						// HPの計算処理
}



