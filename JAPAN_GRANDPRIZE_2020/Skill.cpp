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
#include "Picture.h"
#include "Boss.h"
#include "Select.h"
#include "HP.h"

int g_skillAnime[8] = { 0 };
bool g_skillAniFlg = FALSE;
int g_motion = 0;

int g_skill_X = 100;
int g_skill_Y = 490;

//bool g_skillswitch = TRUE;

//上方向への斬撃
void SkillDisp_1(int aniMAX, int aniMIN) {		//間合い伸びるやつ（player.cppのPlayerIntervalに書いてある）
	//static int skill_X = 100;
	//static int skill_Y = 490;

	bool g_skillFlg = false;
	/*for (int i = 0; i < 8; i++) {
		g_skillAnime[i] = 0;
	}*/

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_player.gauge > SKILL1_GAUGE
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		} else {
			g_player.attackFlg = TRUE;
		}
		g_motion = 0;
		g_skillAniFlg = TRUE;
		g_player.useSkillGage = SKILL1_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL1_COOLTIME;
	}
	// スキル中
	EnemyLockOn();


	//DrawBox(skill_X, skill_Y, skill_X + 100, skill_Y + 100, 0xFF0000, TRUE);
	if (g_player.attackFlg == TRUE) {
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.SkillMotion[g_motion/10], TRUE);
		if (g_motion <= g_player.skillFlg * 30) g_motion += 1;

	}
	if (g_skillAniFlg == TRUE) {
		DrawFormatString(500, 500, 0xff0000, "%d", g_skillAnime[0]/10);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_skillAnime[0] * 15);
		DrawGraph((g_player.x - 80)+ g_skillAnime[0] * 3, g_player.y - 250, g_pic.skillEffect[g_skillAnime[0] / 10], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (++g_skillAnime[0] >= 50) g_skillAniFlg = FALSE, g_skillAnime[0] = 0;
	}
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

	static int effectAnime = 0;
	// スキル中
	//EnemyLockOn();

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_skillAniFlg == FALSE && g_player.gauge > SKILL2_GAUGE
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		}
		else {
			g_player.attackFlg = TRUE;
		}
		g_skill_Y = g_player.y;
		g_skillAniFlg = TRUE;
		g_motion = 3;
		g_player.useSkillGage = SKILL2_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL2_COOLTIME;
	}

	if(g_skillAniFlg == TRUE){
		g_skillAnime[1] += 10;
		EnemyCut();
		//if (g_skillAnime < 1300) DrawBox(g_skill_X + g_skillAnime + PLAYER_WIDTH, g_skill_Y, g_skill_X + PLAYER_WIDTH + PLAYER_WIDTH + g_skillAnime, g_skill_Y + PLAYER_HEIGHT, 0x0000ff, true);
		if (++effectAnime > 20) effectAnime = 1;
		if (g_skillAnime[1] < 1300) DrawGraph(g_skill_X + g_skillAnime[1], g_skill_Y - 200, g_pic.skillEffect[5 + (effectAnime / 5)], TRUE);
		else g_skillAniFlg = FALSE, g_skillAnime[1] = 0, g_skill_Y = 0;
	}

	if (g_player.attackFlg == TRUE) {
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.SkillMotion[g_motion/10], TRUE);
		if (g_motion <= g_player.skillFlg * 30) g_motion += 1;
	}
}

bool SkillMove_2(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	////飛ぶ斬撃（未完）
	//if (g_skillAniFlg == TRUE) {
	//	g_skillAnime += 10;
	//	if (g_skillAnime + 10  < 1300) {
			if (((long int)g_skill_X + (long int)g_skillAnime[1] + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
				&& ((long int)g_skill_X + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH + (long int)g_skillAnime[1] >= ex)
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
	//static int skill_X = 100;
	//static int skill_Y = 490;
	//static int ANIME = 0;

	bool g_skillFlg = false;

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_player.gauge > SKILL3_GAUGE
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		}
		else {
			g_player.attackFlg = TRUE;
		}
		g_motion = 6;
		g_player.useSkillGage = SKILL3_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL3_COOLTIME;
	}
	// スキル中
	EnemyLockOn();

	if (g_player.attackFlg == TRUE) {
		DrawBox(g_skill_X + PLAYER_WIDTH, g_player.y - PLAYER_HEIGHT, g_skill_X + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0x0000ff, false);
		g_skillAniFlg = TRUE;
		g_skill_Y = g_player.y;
		g_skill_X = g_player.x;
	}
	if (g_skillAniFlg == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_skillAnime[2]*15);
		DrawGraph((g_skill_X - 80) + g_skillAnime[2]*3, g_skill_Y - 200, g_pic.skillEffect[(g_skillAnime[2]/10)+10], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(500, 500, 0xff0000, "%d", g_skillAnime[2]/10 + 10);
		if (++g_skillAnime[2] >= 50) g_skillAniFlg = FALSE, g_skillAnime[2] = 0;
	}

	if (g_player.attackFlg == TRUE) {
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.SkillMotion[g_motion/10], TRUE);
		if (g_motion <= g_player.skillFlg * 30) g_motion += 1;
	}

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

void SkillDisp_4(int aniMAX, int aniMIN) { //エレクトロニックスーパージャンプ
	static int effect_X = 0;
	static int effect_Y = 0;
	static float effect_Ani = 0;

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_player.gauge > SKILL4_GAUGE && g_player.y >= GROUND - PLAYER_HEIGHT
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		}
		else {
			g_player.attackFlg = TRUE;
		}
		g_player.useSkillGage = SKILL4_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL4_COOLTIME;
	}

	if (g_player.attackFlg == TRUE) {
		g_skillAniFlg = TRUE;
		g_skill_Y = -40.0F;
		g_player.jumpFlg = TRUE;
		effect_X = g_player.x;
		effect_Y = g_player.y;
		if (g_enemybeat > ENEMY_BEAT_MAX[g_select_Stage]) g_skill_X = g_boss[g_select_Stage].x - 200;
		else g_skill_X = g_player.x;
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.SkillMotion[9], TRUE);
	}
	if (g_skillAniFlg == TRUE) {
		DrawFormatString(500, 500, 0xff0000, "%d", g_skill_X);
		DrawFormatString(500, 600, 0xff0000, "%d", g_boss[g_select_Stage].popflg);
		g_player.y += g_skill_Y;
		g_skill_Y += 2.0F;
		g_noDamageCnt = 0;
		if(g_skill_X > g_player.x)g_player.x += 15.0F;
		//if(g_player.x < WINDOW_WIDTH/2)g_player.x += 10.0F;
		if (g_player.y >= GROUND - PLAYER_HEIGHT) {
			g_player.jumpFlg = FALSE;
			g_player.y = GROUND - PLAYER_HEIGHT;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - g_skillAnime[3] * 8);
		DrawGraph(effect_X - 150, effect_Y, g_pic.skillEffect[17 + int(effect_Ani - 0.1F)], TRUE);
		DrawGraph(effect_X - 100 - g_skillAnime[3] * 8, GROUND - PLAYER_HEIGHT - 150, g_pic.skillEffect[15 + int(effect_Ani - 0.1F)], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (effect_Ani < 1.99) effect_Ani += 0.2F;
		else effect_Ani = 0;
		DrawFormatString(500, 500, 0xff0000, "%d", g_skillAnime[3] / 10 + 10);
		if (++g_skillAnime[3] >= 50) g_skillAnime[3] = 0,g_skillAniFlg = FALSE;
	}

	// スキル中
	//EnemyLockOn();

}

bool SkillMove_4(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	//特に書くことなし
	return FALSE;

}

void SkillDisp_5(int aniMAX, int aniMIN) { //強化技
	//static int skill_X = 100;
	//static int skill_Y = 490;
	//static int anime = 0;

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_player.gauge > SKILL5_GAUGE
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		}
		else {
			g_player.attackFlg = TRUE;
		}
		//g_skillAniFlg = TRUE;
		g_player.powerUpFlg = TRUE;
		g_player.useSkillGage = SKILL5_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL5_COOLTIME;
	}
	/*
	// スキル中
	EnemyLockOn();

	if (g_player.attackFlg == TRUE) {
		DrawBox(g_skill_X + PLAYER_WIDTH, g_player.y, g_skill_X + PLAYER_WIDTH + PLAYER_WIDTH / 2, g_player.y + PLAYER_HEIGHT, 0x0000ff, false);
		g_skill_Y = g_player.y;
		g_skill_X = g_player.x;
	}*/
}

bool SkillMove_5(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	//ここには必要なし
	return FALSE;

}

void SkillDisp_6(int aniMAX, int aniMIN) { //ヴぁリア
	//static int skill_X = 100;
	//static int skill_Y = 490;
	//static int anime = 0;

	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_player.gauge > SKILL6_GAUGE && g_player.barrierFlg == FALSE
		&& g_player.skillCoolTime[g_player.skillNo] <= 0) {
		if (g_player.swordFlg == FALSE) {
			g_player.timecount = 10;
			g_player.useSkillFlg = TRUE;
		}
		else {
			g_player.attackFlg = TRUE;
		}
		g_player.barrierFlg = TRUE;
		g_player.useSkillGage = SKILL6_GAUGE;
		g_player.skillCoolTime[g_player.skillNo] = SKILL6_COOLTIME;
	}

	// スキル中
	//EnemyLockOn();
	/*
	if (g_player.attackFlg == TRUE) {
		g_skillAniFlg = TRUE;
	}
	if (g_skillAniFlg == TRUE) {
		g_skillAniFlg == FALSE;
	}*/
}

bool SkillMove_6(int ex, int ey, int ew, int eh) {		//スキルの当たり判定

	//特に必要なし
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

void SkillInit() {
	for (int i = 0; i < 8; i++) {
		g_skillAnime[i] = 0;
	}
	g_skillAniFlg = FALSE;
	g_motion = 0;

	g_skill_X = 100;
	g_skill_Y = 490;
}