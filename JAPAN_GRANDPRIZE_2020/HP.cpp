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

bool g_hpFlg = false;


void ManagementHP() {
	HpDisp();
	HpMove();
}

// HPの表示処理
void HpDisp(void) {
	static int noDamageCnt = 0;

	//if (++g_MutekiTime > 60 && g_hpFlg == true) g_hpFlg = false;
	if (noDamageCnt++ > 60)g_hpFlg = false;

	// HPの表示
	if (g_player.hp > 0) {
		for (int i = 0; i < g_player.hp; i++) {
			DrawBox(65 + (i * 30), 65, 85 + (i * 30), 85, 0xFF0000, TRUE);
		}
	}
	else {
		g_gameScene = GAME_OVER;
	}
}

// HPの減少
void HpMove(void) {
	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_player.hp;


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].walk.flg == TRUE && g_hpFlg == false) {		//地上の敵描画
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == 1) {
				--g_player.hp;
				g_hpFlg = true;
				g_MutekiTime = 0;
			}
		}
		if (g_enemy[i].fly.flg == TRUE && g_hpFlg == false) {		//空中の敵描画
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == 1) {
				--g_player.hp;
				g_hpFlg = true;
				g_MutekiTime = 0;
			}
		}
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