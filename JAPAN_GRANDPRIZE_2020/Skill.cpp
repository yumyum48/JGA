#include "DxLib.h"
#include "Skill.h"
#include "Player.h"
#include "Struct.h"


void SkillDisp_1(int aniMAX, int aniMIN) {
	// スキル中
	EnemyLockOn();
	/*
	//アニメーション
	if (g_player.jumpFlg == TRUE) {
		if (g_speed < 0) {
			g_resetMotion = 24;
			g_maxMotion = 24;
		}
		else {
			g_resetMotion = 25;
			g_maxMotion = 26;
		}
	}
	else {
		g_resetMotion = 8;
		g_maxMotion = 15;
	}
	if (g_player.attackFlg == TRUE) {//スキル攻撃
		g_resetMotion = 32;
		g_maxMotion = 32;
	}
	*/

	DrawBox(0, 0, 100, 100, 0xFF0000, TRUE);
}
void SkillMove_1() {

}