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

int g_HP = 3;
boolean g_HPflg = false;


void ManagementHP() {
	DispHP();
	DecreaseHP();
}

void DispHP(void) {

	DrawBox(g_player.x + 70, g_player.y + 50, g_player.x + 200, g_player.y + 200, 0xFFFFFF, TRUE);

	if (++g_MutekiTime > 60 && g_HPflg == true) g_HPflg = false;

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].walk.flg == TRUE)		//’nã‚Ì“G•`‰æ
			DrawBox(g_enemy[i].walk.x + 30, g_enemy[i].walk.y + 15, g_enemy[i].walk.x + 100, g_enemy[i].walk.y + 100, 0xFFFFFF, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//‹ó’†‚Ì“G•`‰æ
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50, 0xFFFFFF, TRUE);
	}


	if (g_HP > 0) {
		for (int i = 0; i < g_HP; i++) {
			DrawBox(65 + (i * 30), 65, 85 + (i * 30), 85, 0xFF0000, TRUE);
		}
	}
	else {
		g_gameScene = GAME_OVER;
	}
}


void DecreaseHP(void) {
	//if (g_keyInfo.keyFlg & PAD_INPUT_A) --g_HP;


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].walk.flg == TRUE && g_HPflg == false) {		//’nã‚Ì“G•`‰æ
			if (g_player.x + 70 < g_enemy->walk.x &&
				g_player.x + 200 > g_enemy->walk.x&&
				g_player.y + 15 < g_enemy->walk.y &&
				g_player.y + 200 > g_enemy->walk.y) {
				--g_HP;
				g_HPflg = true;
				g_MutekiTime = 0;
			}
		}
		if (g_enemy[i].fly.flg == TRUE && g_HPflg == false) {		//‹ó’†‚Ì“G•`‰æ
			if (g_player.x + 70 < g_enemy->fly.x &&
				g_player.x + 200 > g_enemy->fly.x&&
				g_player.y + 15 < g_enemy->fly.y &&
				g_player.y + 200 > g_enemy->fly.y) {
				--g_HP;
				g_HPflg = true;
				g_MutekiTime = 0;
			}
		}
	}
}