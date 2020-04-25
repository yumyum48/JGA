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

//bool g_hpFlg = false;


void ManagementHP() {
	HpDisp();
	HpMove();
}

// HP‚Ì•\¦ˆ—
void HpDisp(void) {

	// HP‚Ì•\¦
	if (g_player.hp > 0) {
		for (int i = 0; i < g_player.hp; i++) {
			DrawBox(65 + (i * 30), 65, 85 + (i * 30), 85, 0xFF0000, TRUE);
		}
	}
	else {
		GameInit();
	}
}

// HP‚ÌŒ¸­
void HpMove(void) {
	static int noDamageCnt = 61;

	if(noDamageCnt++ < 60)DrawBox(g_player.x, g_player.y, g_player.x + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0xffffff, FALSE);

	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_player.hp;


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].walk.flg == TRUE
			&& noDamageCnt > 60) {		//’nã‚Ì“G‚Ì“–‚½‚è”»’è
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == 1) {
				--g_player.hp;
				noDamageCnt = 0;
			}
		}
		if (g_enemy[i].fly.flg == TRUE
			&& noDamageCnt > 60) {		//‹ó’†‚Ì“G‚Ì“–‚½‚è”»’è
			if (PlayerHitCheck(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == 1) {
				--g_player.hp;
				noDamageCnt = 0;
			}
		}
	}
}

//// ƒqƒbƒgƒ|ƒCƒ“ƒg‚ÌŒ¸­
//void DecreaseHP(void) {
//	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_player.hp;
//
//
//	for (int i = 0; i < ENEMY_MAX; i++) {
//		if (g_enemy[i].walk.flg == TRUE && g_hpFlg == false) {		//’nã‚Ì“G•`‰æ
//			if (g_player.x + 70 < g_enemy->walk.x &&
//				g_player.x + 200 > g_enemy->walk.x&&
//				g_player.y + 15 < g_enemy->walk.y &&
//				g_player.y + 200 > g_enemy->walk.y) {
//				--g_player.hp;
//				g_hpFlg = true;
//				g_MutekiTime = 0;
//			}
//		}
//		if (g_enemy[i].fly.flg == TRUE && g_hpFlg == false) {		//‹ó’†‚Ì“G•`‰æ
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