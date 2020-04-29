#include "DxLib.h"
#include "HP.h"
#include "Controler.h"
#include "control.h"
#include "GamePlay.h"
#include "Select.h"
#include "GameScene.h"
#include "Struct.h"
#include "enemy.h"
#include "Player.h"
#include "Init.h"
#include "Picture.h"
#include "Boss.h"
#include "Trap.h"
//bool g_hpFlg = false;


void ManagementHP() {
	HpDisp();
	HpMove();
}

// HPの表示処理
void HpDisp(void) {

	//UI表示
	DrawGraph(20, -40, g_pic.PlayerUI, TRUE);
	for (int i = 0; i < 3; i++) {		//HP
		DrawRotaGraph2(110 + (80 * i), 10, 0, 0, 0.5, 0.0, g_pic.Life[0], TRUE);
	}
	for (int i = 0; i < g_player.hp; i++) {		//HP
		DrawRotaGraph2(110 + (80 * i), 10, 0, 0, 0.5, 0.0, g_pic.Life[1], TRUE);
	}

	
}

// HPの減少
void HpMove(void) {
	static int noDamageCnt = 61;

	if(noDamageCnt++ < 60)DrawBox(g_player.x, g_player.y, g_player.x + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0xffffff, FALSE);

	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_player.hp;

	// トラップとの接触判定
	if(g_trap.x)

	// 弱い敵との接触判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].walk.flg == TRUE
			&& noDamageCnt > 60) {		//地上の敵の当たり判定
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {
				--g_player.hp;
				noDamageCnt = 0;		// 無敵時間発動
			}
		}
		if (g_enemy[i].fly.flg == TRUE
			&& noDamageCnt > 60) {		//空中の敵の当たり判定
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {
				--g_player.hp;
				noDamageCnt = 0;		// 無敵時間発動
			}
		}
	}

	// ボスの当たり判定
	if( (PlayerHitCheck(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == TRUE) 
	&&  (noDamageCnt > 60) ){
		g_player.hp--;
		noDamageCnt = 0;				// 無敵時間発動
	}

	// HPが０になったらゲームオーバー
	if (g_player.hp <= 0) {
		GameInit();
	}
}

//// ヒットポイントの減少
//void DecreaseHP(void) {
//	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_player.hp;
//
//
//	for (int i = 0; i < ENEMY_MAX; i++) {
//		if (g_enemy[i].walk.flg == TRUE && g_hpFlg == false) {		//地上の敵描画
//			if (g_player.x + 70 < g_enemy->walk.x &&
//				g_player.x + 200 > g_enemy->walk.x&&
//				g_player.y + 15 < g_enemy->walk.y &&
//				g_player.y + 200 > g_enemy->walk.y) {
//				--g_player.hp;
//				g_hpFlg = true;
//				g_MutekiTime = 0;
//			}
//		}
//		if (g_enemy[i].fly.flg == TRUE && g_hpFlg == false) {		//空中の敵描画
//			if (g_player.x + 70 < g_enemy->fly.x &&
//				g_player.x + 200 > g_enemy->fly.x&&
//				g_player.y + 15 < g_enemy->fly.y &&
//				g_player.y + 200 > g_enemy->fly.y) {
//				--g_player.hp;
//				g_hpFlg = true;
//				g_MutekiTime = 0;
//			}
//		}
//	}
//}