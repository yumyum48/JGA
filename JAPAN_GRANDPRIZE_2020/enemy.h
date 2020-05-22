#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// ƒGƒlƒ~[‚Ì‰¡•
#define ENEMY_HEIGHT	 (545 * 0.2)// ƒGƒlƒ~[‚Ìc•
extern enemyType g_enemy[ENEMY_MAX];	// “G‚Ìî•ñ
extern enemyInfo g_enemyBuffer[ENEMY_MAX];	// Œ‚”j‚µ‚½“G‚Ìî•ñ‚ğŠi”[‚·‚é•Ï”

extern const int ENEMY_BEAT_MAX[MAP_MAX];	//ŠeƒXƒe[ƒW‚ÌG‹›“G‚ğ“|‚·”‚Å‚·

extern int g_enemybeat;	// ƒGƒlƒ~[‚ğ“|‚µ‚½”‚ğƒJƒEƒ“ƒg‚·‚éƒOƒ[ƒoƒ‹•Ï”

//extern int g_killCount;
void MonsterDisp();		// ã‚¢“GAƒ{ƒX‚Ì•\¦
void MonsterMove();		// ã‚¢“GAƒ{ƒX‚Ì“®‚«
void EnemyDisp_stage1();		// “G‚Ì•`‰æ
void EnemyDisp_stage2();		// “G‚Ì•`‰æ
void EnemyDisp_stage3();		// “G‚Ì•`‰æ
void EnemyDisp_stage4();		// “G‚Ì•`‰æ
void EnemyDisp_stage5();		// “G‚Ì•`‰æ
void EnemyDisp_stage6();		// “G‚Ì•`‰æ
void EnemyDisp_stage7();		// “G‚Ì•`‰æ
void EnemyDisp_stage8();		// “G‚Ì•`‰æ
void EnemyMove();		// “G‚Ì“®‚«
void EnemyInit();		// “G‚Ì‰Šú‰»
int EnemyEvaporation();	// “G‚ÌŒ‚”j‚ÌƒAƒjƒ[ƒVƒ‡ƒ“



void (* const EnemyDisp[MAP_MAX])() = {
		EnemyDisp_stage1,
		EnemyDisp_stage2,
		EnemyDisp_stage3,
		EnemyDisp_stage4,
		EnemyDisp_stage5,
		EnemyDisp_stage6,
		EnemyDisp_stage7,
		EnemyDisp_stage8,
};		// “G‚Ì•`‰æ

