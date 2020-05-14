#pragma once
#include "DxLib.h"
#include "Struct.h"

#define PLAYER_WIDTH	 (280 * PLAYER_REDUCTION)			// プレイヤーの横幅
#define PLAYER_HEIGHT	 (200 * PLAYER_REDUCTION)			// プレイヤーの縦幅

extern playerInfo g_player;									// プレイヤーの情報

enum PlayerAnime {											// プレイヤーのアニメーション
	CLOSE_MOVE_S = 0,			//納刀状態:走り
	CLOSE_MOVE_E = 7,
	OPEN_MOVE_S = 8,			//抜刀状態:走り
	OPEN_MOVE_E = 15,
	CLOSE_JUMP_UP = 16,			//納刀状態:ジャンプ上昇
	CLOSE_JUMP_DOWN_S = 17,		//納刀状態:ジャンプ下降
	CLOSE_JUMP_DOWN_E = 18,
	OPEN_JUMP_UP = 24,			//抜刀状態:ジャンプ上昇
	OPEN_JUMP_DOWN_S = 25,		//抜刀状態:ジャンプ下降
	OPEN_JUMP_DOWN_E = 26,
	SWORD_OPEN_S = 32,			//抜刀モーション
	SWORD_OPEN_E = 33,
	SWORD_CLOSE_S = 40,			//納刀モーション
	SWORD_CLOSE_E = 41,
	DAMAGE = 48					//ダメージ
};

void PlayerDisp();											// プレイヤーの描画
void PlayerMove();											// プレイヤーの動き
void PlayerInit();											// プレイヤーの初期化
void PlayerJump();											// プレイヤーのジャンプ処理
void PlayerControl();										// プレイヤーを操作する処理
void EnemyLockOn();											// プレイヤーの間合いに入っている敵をロックオン
bool PlayerInterval(int ex, int ey, int ew, int eh);		// プレイヤーの画像と敵の画像の当たり判定 (TRUE: 当たった | FALSE: 当たらなかった)
bool PlayerHitCheck(int ex, int ey, int ew, int eh);		// プレイヤーの剣の部分の判定を抜きに、プレイヤー自身の当たり判定(主にエネミーとの衝突に使う)(当たった:TRUE  当たっていなかった:FALSE)
void EnemyCut();											// 間合いに入っている敵を倒す処理
void PlayerAfterimage(int anime);							// プレイヤーの残像
int  SkillChange();											// 
void PlayerAnimation();										// プレイヤーのアニメーション

