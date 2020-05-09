#include "DxLib.h"
#include "Skill.h"
#include "Player.h"
#include "Struct.h"
#include "Macro.h"
#include "enemy.h"
#include "Controler.h"
#include "GamePlay.h"
#include "control.h"
#include "Macro.h"

int g_skillAnime = 0;
bool g_skillAniFlg = FALSE;

int g_skill_X = 100;
int g_skill_Y = 490;

//bool g_skillswitch = TRUE;

//上方向への斬撃
void SkillDisp_1(int aniMAX, int aniMIN) {		//間合い伸びるやつ（player.cppのPlayerIntervalに書いてある）
	//static int skill_X = 100;
	//static int skill_Y = 490;

	bool g_skillFlg = false;

	// スキル中
	EnemyLockOn();

	/*
	//アニメーション
	if (g_player.jumpFlg == TRUE) 
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

	//DrawBox(skill_X, skill_Y, skill_X + 100, skill_Y + 100, 0xFF0000, TRUE);

}

bool SkillMove_1(int ex, int ey, int ew, int eh){		//スキルの当たり判定

	//間合いが伸びる
	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
		&& ((long int)g_player.y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
		&& ((long int)g_player.y + (long int)PLAYER_HEIGHT >= ey)) {
		return TRUE;
	}

	return FALSE;
}

void SkillDisp_2(int aniMAX, int aniMIN){ //飛ばすやつ

	// スキル中
	//EnemyLockOn();

	if (g_keyInfo.keyFlg & PAD_INPUT_3 && g_skillAniFlg == FALSE) {
		g_skillAniFlg = TRUE;
		g_skill_Y = g_player.y;
	}

	if(g_skillAniFlg == TRUE){
		g_skillAnime += 10;
		EnemyCut();
		if (g_skillAnime < 1300) DrawBox(g_skill_X + g_skillAnime + PLAYER_WIDTH, g_skill_Y, g_skill_X + PLAYER_WIDTH + PLAYER_WIDTH + g_skillAnime, g_skill_Y + PLAYER_HEIGHT, 0x0000ff, true);
		else g_skillAniFlg = FALSE, g_skillAnime = 0;
	}
}

bool SkillMove_2(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	////飛ぶ斬撃（未完）
	//if (g_skillAniFlg == TRUE) {
	//	g_skillAnime += 10;
	//	if (g_skillAnime + 10  < 1300) {
			if (((long int)g_skill_X + (long int)g_skillAnime + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
				&& ((long int)g_skill_X + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH + (long int)g_skillAnime >= ex)
				&& ((long int)g_skill_Y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
				&& ((long int)g_skill_Y + (long int)PLAYER_HEIGHT >= ey)) {
				return TRUE;
			}
		//}
		//else {
		//	g_skillAniFlg = FALSE;
		//	g_skillAnime = 0;
		//}
	

	return FALSE;

}

void SkillDisp_3(int aniMAX, int aniMIN) { //上方向に延びるやつ
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	bool g_skillFlg = false;

	// スキル中
	EnemyLockOn();

	DrawBox(g_skill_X + PLAYER_WIDTH, g_player.y - PLAYER_HEIGHT, g_skill_X + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y+ PLAYER_HEIGHT, 0x0000ff, false);

}

bool SkillMove_3(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	//上方向に延びる（未完）
	if (((long int)g_skill_X + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
		&& ((long int)g_skill_X + (long int)PLAYER_WIDTH + PLAYER_WIDTH >= ex)
		&& ((long int)g_player.y - (long int)PLAYER_HEIGHT <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
		&& ((long int)g_player.y + (long int)PLAYER_HEIGHT >= ey)) {
		return TRUE;
	}

	return FALSE;

}

void SkillDisp_4(int aniMAX, int aniMIN) { //未定
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	// スキル中
	EnemyLockOn();

}

bool SkillMove_4(int ex, int ey, int ew, int eh) {		//スキルの当たり判定
	return FALSE;

}

void SkillDisp_5(int aniMAX, int aniMIN) { //未定
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	// スキル中
	EnemyLockOn();

}

bool SkillMove_5(int ex, int ey, int ew, int eh) {		//スキルの当たり判定
	return FALSE;

}

void SkillDisp_6(int aniMAX, int aniMIN) { //未定
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	// スキル中
	EnemyLockOn();

}

bool SkillMove_6(int ex, int ey, int ew, int eh) {		//スキルの当たり判定
	return FALSE;

}

void SkillDisp_7(int aniMAX, int aniMIN) { //未定
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	// スキル中
	EnemyLockOn();

}

bool SkillMove_7(int ex, int ey, int ew, int eh) {		//スキルの当たり判定
	return FALSE;

}

void SkillDisp_8(int aniMAX, int aniMIN) { //未定
	static int skill_X = 100;
	static int skill_Y = 490;
	static int anime = 0;

	// スキル中
	EnemyLockOn();

}

bool SkillMove_8(int ex, int ey, int ew, int eh) {		//スキルの当たり判定
	return FALSE;
}