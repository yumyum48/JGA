#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Player.h"
#include "control.h"
#include "Controler.h"
#include "Select.h"
#include "GameScene.h"
#include "Init.h"
#include "Macro.h"
#include "HP.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Trap.h"
#include "Skill.h"
#include "Sounds.h"

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
int g_boss4_JumpAnime;			// カエルのジャンプするアニメーション

/*********************************************

* ステージ１のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage1() {
	//	水玉が遅い
	// 二次元配列の0番目は敵本体
	// １番目は水玉
	int bossAnime_MAX[2] = { 7, 15};	// アニメーションの最終尾
	int bossAnime_Start[2] = { 0, 8 };	// アニメーションの最初
	static int anime[2] = { 0, 0 };		// 画像の切り替え
	static int time = 0;				// フレーム単位のカウント

	if (time++ % 4 == 0) anime[0]++;
	if (time % 6 == 0) anime[1]++;
	for (int i = 0; i < 2; i++) {
		if (anime[i] > bossAnime_MAX[i]) {
			anime[i] = bossAnime_Start[i];
		}
	}
	
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[1]], TRUE);
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[0]], TRUE);
	if (g_boss[BOSS_STAGE1].damageFlg == TRUE) {
		Boss_Damage_Disp2(&g_boss[BOSS_STAGE1].damageFlg, g_boss[BOSS_STAGE1].x, g_boss[BOSS_STAGE1].y, g_pic.boss_1_1[anime[1]], 2.0F);
		Boss_Damage_Disp(&g_boss[BOSS_STAGE1].damageFlg, g_boss[BOSS_STAGE1].x, g_boss[BOSS_STAGE1].y, g_pic.boss_1_1[anime[0]], 2.0F);
		

	}
	if (g_boss[0].attackFlg != 0) {
		BossAttackDisp();	// ボスの攻撃
	}

}


/*********************************************

* ボスの動き達

*/////////////////////////////////////////////
// ボスの動きパターン
void BossMoveMotion(int *coolTime, int *moveFlg){

	switch (*moveFlg)
	{
	case BOSSMOVE_ATTACK:
		BossMoveMotion_Pattern1(coolTime, moveFlg);		// ボスがサインはで接近
		break;

	case BOSSMOVE_SPEEDDOWN:
		BossMoveMotion_Pattern2(coolTime, moveFlg);		// ボスのX軸が左に寄っていく
		break;
		
	default:
		break;
	}

}

void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg) {
	static bool teleportFlg = FALSE;

	if (g_boss[g_select_Stage].x > -BOSS_WIDTH
		&& teleportFlg == FALSE) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// 横の振れ幅
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// 縦の振れ幅
		g_boss[g_select_Stage].x -= 5;						// ボスの移動量
	}
	else if(g_boss[g_select_Stage].x <= -BOSS_WIDTH){
		g_boss[g_select_Stage].x = WINDOW_WIDTH + BOSS_WIDTH;
		g_boss[g_select_Stage].y = 160;
		teleportFlg = TRUE;
	}

	if (teleportFlg == TRUE
		&& g_boss[g_select_Stage].x > 700) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// 横の振れ幅
		g_boss[g_select_Stage].y -= sin(angle) * 10 - 0.8;			// 縦の振れ幅
		g_boss[g_select_Stage].x -= 5;						// ボスの移動量
	}
	else if (teleportFlg == TRUE) {
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
		teleportFlg = FALSE;
	}
}

void BossMoveMotion_Pattern2(int* coolTime, int* moveFlg) {
	static int chanceTime = 0;
	static bool speedUpFlg = FALSE;
	// ボスの移動スピードをだんだんと落とす
	if (g_boss[g_select_Stage].x >= g_player.x + PLAYER_WIDTH && speedUpFlg == FALSE) {
		g_boss[g_select_Stage].x -= 2;
		if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {				// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない
			speedUpFlg = TRUE;
		}
	}
	else if(chanceTime++ >= 120 || BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE){	// プレイヤーの目の前に来たら、攻撃できるようにチャンスタイムを作る
		speedUpFlg = TRUE;			// 二秒立ったら、またはプレイヤーが攻撃をしたらボス２がスピードアップして元の位置まで戻る
	}
	if (speedUpFlg == TRUE && g_boss[g_select_Stage].x < 823) {
		g_boss[g_select_Stage].x += 2;	// ボスを最初の位置へと戻す
	}
	else if (g_boss[g_select_Stage].x >= 823) {
		g_boss[g_select_Stage].x = 823;	// 最初の場所に戻ったら座標を固定
		*coolTime = 0;					// クールタイム初期化
		*moveFlg = 0;					// moveFlg初期化
		speedUpFlg = FALSE;				// スピードアップフラグを初期化
	}
}
/*********************************************

* ボスの当たり判定	// 当たるとプレイヤーhp減少

*/////////////////////////////////////////////
void Boss_Knock_Down() {
	
	if (g_boss[g_select_Stage].hp <= 0) {
		StopSoundMem(g_sound[BGM_BATTLE]);
		SetCurrentPositionSoundMem(0, g_sound[BGM_BATTLE]);
		g_gameScene = GAME_STAGE_CLEAR;
		if (g_stageClearFlg[g_select_Stage] == FALSE) {
			g_select_MAX++;	// セレクトできるマップを増やす
			g_stageClearFlg[g_select_Stage] = TRUE;
		}
	}
	
}
/*********************************************

* ボスの攻撃関係

*/////////////////////////////////////////////
// ボスの攻撃の全体管理(表示)
void BossAttackDisp() {
	
	
	switch (g_boss[g_select_Stage].attackFlg) {
		case BOSSATTACK_ENEMY_DROP:
		
			BossEnemyDropDisp();	// 弱い敵を出す
			break;

		case BOSSATTACK_WATER_BULLET:
			BossWaterBulletDisp();	// 水弾の発射
			break;

		case BOSSATTACK_WAVE_ATTACK:
			BossGenerateWave();		// 津波の発生
			break;
		
		case BOSSATTACK_JUMPANDPOISON:
			BossJumpOrPoison_Disp();// ボスがジャンプして稀に毒を出す表示
			break;

		case BOSSATTACK_LONGTON:
			BossLongTon_Disp();		// ボスが舌を伸ばす攻撃
			break;

		case BOSSATTACK_MINISPIDER_DROP:
			Boss_MiniSpider_Drop_Disp();
			break;
		
		case BOSSATTACK_MINICLOUD_DROP:
			Boss_MiniCloud_Drop_Disp();
			break; 

		case BOSSATTACK_LIGHTNING:
			Boss_Lightning_Disp();
			break;

		case BOSSATTACK_TACKLE:
			Boss_Tackle_Disp();
			break;

		case BOSSATTACK_RUSH:
			Boss_Rush_Disp();		// ボスの突進攻撃
			break;

		case BOSSATTACK_LONG_RANGE:	// 遠距離攻撃
			Boss_LongRange_Disp();
			break;
		default:
			break;
	}
	

	
}
// ボスの攻撃の全体管理(動き)
void BossAttackMove() {

	switch (g_boss[g_select_Stage].attackFlg) {
		case BOSSATTACK_ENEMY_DROP:
			BossEnemyDropMove();	// 弱い敵を出す
			//g_boss[g_select_Stage].attackFlg = 0;
			break;

		case BOSSATTACK_WATER_BULLET:
			BossWaterBulletMove();	// 水弾の発射
			break;

		case BOSSATTACK_WAVE_ATTACK:
			BossGenerateWave();		// 津波の発生
			break;

		case BOSSATTACK_JUMPANDPOISON:
			BossJumpOrPoison_Move();// ボスがジャンプして稀に毒を出す動き
			break;

		case BOSSATTACK_LONGTON:
			BossLongTon_Move();
			break;

		case BOSSATTACK_MINISPIDER_DROP:
			Boss_MiniSpider_Drop_Move();
			break;

		case BOSSATTACK_MINICLOUD_DROP:
			Boss_MiniCloud_Drop_Move();
			break;

		case BOSSATTACK_LIGHTNING:
			Boss_Lightning_Move();
			break;

		case BOSSATTACK_TACKLE:
			Boss_Tackle_Move();
			break;

		case BOSSATTACK_RUSH:
			Boss_Rush_Move();		// ボスの突進攻撃
			break;

		case BOSSATTACK_LONG_RANGE:	// 遠距離攻撃
			Boss_LongRange_Move();
			break;
		default:
			break;
	}
	
}

/*********************************************

* ボス６遠距離攻撃

*/////////////////////////////////////////////
void Boss_LongRange_Disp() {
	const int animePoint[4] = { 15, 3, 5, 9 };		// 影と攻撃のアニメーションのポイント 0:ニュートラル 1:攻撃開始 2:攻撃振り終わり、エフェクト開始 3:エフェクト終了
	const int animeSpeedRate[2] = { 4, 8 };			// アニメーション速度	0:影本体	1:攻撃
	static int anime[2] = { animePoint[0], animePoint[2] * animeSpeedRate[1] };	// アニメーション変数	0:影本体	1:攻撃
	static bool attackInitFlg = FALSE;				// 攻撃開始時に初期化するフラグ
	static int transparent = 150;						// 影の透過率

	// 待機時間が過ぎたら攻撃開始
	if (g_boss_shadow.shadowDispFlg == TRUE
		&& (++g_boss_shadow.preparationCnt > 60)) {
		g_boss_shadow.attackDispFlg = TRUE;
		if (attackInitFlg == FALSE) {
			anime[0] = animePoint[1] * animeSpeedRate[0];
			attackInitFlg = TRUE;
		}
	}

#ifdef DEBUG_BOSS_ON
	DrawBox(g_boss_shadow.attackx, g_boss_shadow.attacky,
		g_boss_shadow.attackx + g_boss_shadow.attackw, g_boss_shadow.attacky + g_boss_shadow.attackh,
		0xFF0000, TRUE);

	DrawFormatString(500, 300, 0x000000, "anime[0] = %d\nanimeSpeedRate[0] = %d\nanime[0] / animeSpeedRate[0] = %d", anime[0], animeSpeedRate[0], anime[0] / animeSpeedRate[0]);
#endif

	// 影の表示フラグが真で影を表示
	// ボスの攻撃がプレイヤーに当たった時に攻撃モーションに切り替え
	if (g_boss_shadow.shadowDispFlg == TRUE
		&& (g_boss_shadow.attackDispFlg == FALSE)) {
		// 影本体の表示
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[anime[0]], TRUE, TRUE, FALSE);
	}
	else if (g_boss_shadow.attackDispFlg == TRUE) {
		// 影の攻撃モーション進行
		if (anime[0] < animePoint[2] * animeSpeedRate[0])anime[0]++;
		// 影本体の攻撃モーション表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparent);
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_2[anime[0] / animeSpeedRate[0]], TRUE, TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// 斬撃のアニメーション進行
		if (anime[1] < (animePoint[3] * animeSpeedRate[1]))anime[1]++;
		// 斬撃のアニメーション表示
		DrawRotaGraph2(g_boss_shadow.attackx, g_boss_shadow.attacky + 70 + 40, 30, 370, 1.0f, 0, g_pic.boss_6_3[anime[1] / animeSpeedRate[1]], TRUE, TRUE, FALSE);
	}

	// ボスが画面外に出たときの処理
	if (/*g_boss_shadow.shadowDispFlg == FALSE*/
		g_boss_shadow.attackx + g_boss_shadow.attackw + g_boss_shadow.attackw < 0) {
		transparent -= 15;
		if (transparent < 0) {
			transparent = 150;
			anime[0] = animePoint[0];
			anime[1] = animePoint[2] * animeSpeedRate[1];
			attackInitFlg = FALSE;
			g_boss_shadow.LongRangeInit(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, FALSE);
			g_boss[g_select_Stage].attackFlg = 0;		// attackフラグを初期化
		}
	}

}

void Boss_LongRange_Move() {
	static int noDamageTime = 30;		// ダメージを受け付けない時間

	// 待機時間が過ぎたら移動開始
	if ((g_boss_shadow.preparationCnt > 60))g_boss_shadow.attackx -= g_speedLevel + 1;

	if (++noDamageTime < 30);

	// プレイヤーにヒットしたら攻撃終了
	if (noDamageTime >= 40
		&& PlayerHitCheck(g_boss_shadow.attackx, g_boss_shadow.attacky, g_boss_shadow.attackw, g_boss_shadow.attackh) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;

		noDamageTime = 0;
	}

}

/*********************************************

* ボス６の突進

*/////////////////////////////////////////////
void Boss_Rush_Disp() {
	const int animePoint[4] = { 0, 8, 15, 2 };		// 影のアニメーションのポイント 0:攻撃開始 1:移動開始 2:移動ループ地点 3:攻撃終了
	const int attackAnimeMax = 4;					// 攻撃のアニメーションの最後尾
	static int animationStart = animePoint[1];		// アニメーションの開始点
	static int animationLast = animePoint[2];		// アニメーションのループ地点
	const int animeSpeedRate[2] = { 4, 8 };			// アニメーション速度	0:影本体	1:攻撃
	static int anime[2] = { animationStart * animeSpeedRate[0], 0 };	// アニメーション変数	0:影本体	1:攻撃
	//static bool animeStartFlag = FALSE;
	//static bool attackFlg = FALSE;

	if (g_boss_shadow.shadowDispFlg == TRUE
		&& ++g_boss_shadow.preparationCnt < 60) {
		/*if (anime[0] % animeSpeedRate[0] == 0)anime[0]++;
		if (anime[0] > animationLast)anime[0] = animationStart;*/
		//if (++anime[0] > animationLast * animeSpeedRate[0])anime[0] = animationStart;
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[anime[0] / animeSpeedRate[0]], TRUE, TRUE, FALSE);
	}
	// 影の表示フラグが真で影を表示
	// ボスの攻撃がプレイヤーに当たった時に攻撃モーションに切り替え
	else if (g_boss_shadow.shadowDispFlg == TRUE
		&& (g_boss_shadow.attackDispFlg == FALSE)) {
		// 影本体の表示
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[anime[0] / animeSpeedRate[0]], TRUE, TRUE, FALSE);
		if (++anime[0] > animationLast * animeSpeedRate[0]) {
			animationStart = animePoint[1];
			animationLast = animePoint[2];
			anime[0] = animationStart * animeSpeedRate[0];
		}
	}
	else if (g_boss_shadow.attackDispFlg == TRUE) {
		// 影本体の攻撃モーション表示
		if (anime[0] < animationLast * animeSpeedRate[0])anime[0]++;
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_2[anime[0] / animeSpeedRate[0]], TRUE, TRUE, FALSE);

		// 斬撃のアニメーション進行
		if (++anime[1] > attackAnimeMax * animeSpeedRate[1])anime[1] = animePoint[0];

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, anime[1] * 15);
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70 + 40, 90, 300, 1.0f, 0, g_pic.boss_6_3[anime[1] / animeSpeedRate[1]], TRUE, TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	// プレイヤーに当たったら攻撃アニメーション開始
	if (PlayerHitCheck(g_boss_shadow.x - g_boss_shadow.w / 2, g_boss_shadow.y + 70 + 40, g_boss_shadow.x, g_boss_shadow.h + 70) == TRUE) {
		//DrawBox(g_boss_shadow.x, g_boss_shadow.y + 70 + 40, g_boss_shadow.x + g_boss_shadow.w, g_boss_shadow.y + g_boss_shadow.h + 0, 0xF0000, TRUE);
			//animeStartFlag = TRUE;
		animationStart = animePoint[0];
		animationLast = animePoint[3];
		anime[0] = animationStart * animeSpeedRate[0];
	}

	// ボスが画面外に出たときの処理
	if (/*g_boss_shadow.shadowDispFlg == FALSE*/
		g_boss_shadow.x + g_boss_shadow.w < 0) {
		animationStart = animePoint[1];
		animationLast = animePoint[2];
		anime[0] = animationStart * animeSpeedRate[0];
		anime[1] = animePoint[0];
		g_boss_shadow.ShadowInit(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, FALSE);
		g_boss[g_select_Stage].attackFlg = 0;		// attackフラグを初期化
	}

#ifdef DEBUG_BOSS_ON

	DrawFormatString(500, 300, 0x000000,
		"animationStart = %d\nanimationLast = %d\nanime[0] = %d\nanimeSpeedRate[0] = %d\nanime[0] / animeSpeedRate[0] = %d",
		animationStart, animationLast, anime[0], animeSpeedRate[0], anime[0] / animeSpeedRate[0]);
#endif
}

void Boss_Rush_Move() {
	static int noDamageTime = 30;		// ダメージを受け付けない時間


	if ((g_boss_shadow.preparationCnt > 60))g_boss_shadow.x -= g_speedLevel + 2;

	if (++noDamageTime < 30);

	// プレイヤーに切られた時
	if ((noDamageTime >= 40)
		&& (g_player.attackFlg == TRUE)
		&& SkillMove[g_player.skillFlg - 1](g_boss_shadow.x, g_boss_shadow.y,
			BOSS_THREAD_WIDTH, g_boss_shadow.h + 50) == TRUE) {
		g_boss_shadow.ShadowInit(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, FALSE);
		g_boss[g_select_Stage].attackFlg = 0;		// attackフラグを初期化
	}

	// プレイヤーにヒットしたらもとのポジションへ移動して攻撃終了
	if ((noDamageTime >= 40)
		&& PlayerHitCheck(g_boss_shadow.x, g_boss[g_select_Stage].y + 70 + 40, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;

		g_boss_shadow.attackDispFlg = TRUE;
		noDamageTime = 0;
	}
	if (g_boss_shadow.shadowDispFlg == FALSE
		&& g_boss_shadow.attackDispFlg == FALSE) {
	}
}


/*********************************************

* ボス5のタックル

*/////////////////////////////////////////////
void  Boss_Tackle_Disp() {
	// 0,3:ボスのニュートラルモーションの最初と最後	4,7:ボスの攻撃モーションの最初と最後	8,9:ボスの攻撃予備動作の最初と最後
	const int bossAnime[6] = { 0, 3, 4, 7, 8, 9 };
	static int animationStart = bossAnime[4];	// アニメーション開始位置の初期化
	static int animationLast = bossAnime[5];	// アニメーションループの初期化
	static int animecnt = 0;					// アニメーションをする為のカウント

	if (g_boss5_Ex.attackFlg == FALSE) {

		if (g_boss5_Ex.anime < bossAnime[2]) {
			animationStart = bossAnime[4];
			animationLast = bossAnime[5];
			g_boss5_Ex.anime = animationStart;
		}

		if (animecnt++ % 15 == 0)g_boss5_Ex.anime++;	

		if (g_boss5_Ex.anime > bossAnime[5]) {
			animationStart = bossAnime[2];
			animationLast = bossAnime[3];
			g_boss5_Ex.anime = animationStart;
			g_boss5_Ex.animeFlg = TRUE;
		}	// アニメーションの進行

		if (g_boss5_Ex.anime > animationLast) {				// アニメーションのループ
			g_boss5_Ex.anime = animationStart;
		}

	}

	if (g_boss5_Ex.attackFlg == TRUE) {
		animationStart = bossAnime[0];
		animationLast = bossAnime[1];

		if (animecnt++ % 15 == 0)g_boss5_Ex.anime++;					// アニメーションの進行
		if (g_boss5_Ex.anime > animationLast)g_boss5_Ex.anime = animationStart;	// アニメーションのループ
	}

#ifdef DEBUG_BOSS_ON
	DrawFormatString(700, 400, 0x0000FF, "%d\n%d\n%d", animationStart, animationLast, g_boss5_Ex.anime);
#endif // DEBUG_BOSS_ON

}
void Boss_Tackle_Move() {
	int boss5fiestX = 808;
	static int returnFlg = FALSE;	// ボスが元の位置へ戻るフラグ TRUE;戻る FALSE:戻らない
	//static int animeFlg = FALSE;	// 攻撃アニメーション野順義が整っているかのフラグ　TRUE:攻撃可能  FALSE:攻撃不可

	// 攻撃開始のフラグ
	if (g_boss5_Ex.animeFlg == TRUE) {

		if (returnFlg == FALSE) {
			g_boss[g_select_Stage].x -= 10;
		}
		else if ((g_boss[g_select_Stage].x < boss5fiestX)	// ボスが最初の位置より左側にいたら右方向へ移動
			&& (returnFlg == TRUE)) {
			g_boss[g_select_Stage].x += 8;
		}
		else if ((g_boss[g_select_Stage].x >= boss5fiestX)
			&& (returnFlg == TRUE)) {
			returnFlg = FALSE;
			g_boss[g_select_Stage].x = boss5fiestX;
			g_boss[g_select_Stage].attackFlg = 0;		// attackフラグを初期化
			g_noDamageCnt = 0;
			g_boss5_Ex.attackFlg = FALSE;
			g_boss5_Ex.animeFlg = FALSE;
		}

		// プレイヤーにヒットしたらもとのポジションへ移動して攻撃終了
		if (PlayerHitCheck(g_boss[g_select_Stage].x + 5, g_boss[g_select_Stage].y, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE) {
			if (g_player.barrierFlg == FALSE) --g_player.hp;
			else g_player.barrierFlg = FALSE;
			returnFlg = TRUE;
			g_boss5_Ex.anime = 0;
			g_boss5_Ex.attackFlg = TRUE;
		}
		// ボスがダメージを受けたら強制的に元の位置に戻す
		if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {
			returnFlg = TRUE;
			g_boss5_Ex.anime = 0;
			g_boss5_Ex.attackFlg = TRUE;
		}
	}
}
/*********************************************

* 毒のトラップを設置

*/////////////////////////////////////////////
void Poison_Trap_Disp() {
	if (g_trap.dispFlg == TRUE) {
		DrawRotaGraph2(g_trap.x, g_trap.y, 0, 0, 0.3, 0.0, g_pic.trap, TRUE);
	}
}
void Poison_Trap_Move() {
	if (g_trap.dispFlg == TRUE) {
		g_trap.x -= g_speedLevel;														// トラップのX座標をスクロール速度と同じ値で加算させる

		if (g_trap.x + 100 < 0) {
			g_trap.Init();																// トラップが画面外に入った場合初期化
			g_trap.dispFlg = FALSE;
		}
	}
}
/*********************************************

* ミニ雲を出す

*/////////////////////////////////////////////
void Boss_MiniCloud_Drop_Disp() {
	static int coolTime = 0;
	static int enemyDropCnt = 0;
	static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // 
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++coolTime > 60) {
		// エネミーの出現フラグをオンにする

		if (g_enemy[enemy_cnt].cloud.flg == FALSE && enemy_cnt < 3) {
			g_enemy[enemy_cnt].cloud.flg = TRUE;
			coolTime = 0;

			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}

	// 雑魚敵の描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// アニメーションのカウント
		if (time++ % 8 == 0) {
			g_enemy[i].cloud.anime++;

		}

		// アニメーションの初期化
		if (g_enemy[i].cloud.anime > animation_Max)g_enemy[i].cloud.anime = 0;


		if (g_enemy[i].cloud.flg == TRUE)        // 雑魚敵の描画
			DrawRotaGraph2(g_enemy[i].cloud.x, g_enemy[i].cloud.y,
				0, 0, 0.2, 0.0, g_pic.enemy_fly[g_enemy[i].cloud.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 雑魚敵が倒されたかを確認
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].cloud.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// 出現した雑魚敵が全て倒されていたら攻撃終了
	if (enemyDropCnt >= 3) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			g_boss[g_select_Stage].attackFlg = 0;    // attackフラグを初期化
			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			enemy_dispFlg_Buf[1] = { FALSE };
			enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}
void Boss_MiniCloud_Drop_Move() {

	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // ミニ雲の最大数回す


		if (g_enemy[i].cloud.flg == TRUE) {
			g_enemy[i].cloud.x -= (g_speedLevel - 3);	   // ミニ雲を移動
			g_enemy[i].cloud.y = (GROUND - ENEMY_HEIGHT) - 200;
			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].cloud.x + ENEMY_WIDTH < 0) {		// ミニ雲が範囲外まで行くと初期化

			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			
		}
	}
}

/*********************************************

* ミニ蜘蛛を出す

*/////////////////////////////////////////////
// 表示
void Boss_MiniSpider_Drop_Disp() {
	static int coolTime = 0;
	static int enemyDropCnt = 0;
	static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE };
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++coolTime > 60) {
		// エネミーの出現フラグをオンにする

		if (g_enemy[enemy_cnt].spider.flg == FALSE && enemy_cnt < 3) {
			g_enemy[enemy_cnt].spider.flg = TRUE;
			coolTime = 0;

			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}

	// 雑魚敵の描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// アニメーションのカウント
		if (time++ % 8 == 0) {
			g_enemy[i].spider.anime++;

		}

		// アニメーションの初期化
		if (g_enemy[i].spider.anime > animation_Max)g_enemy[i].spider.anime = 0;


		if (g_enemy[i].spider.flg == TRUE)        // 雑魚敵の描画
			DrawRotaGraph2(g_enemy[i].spider.x, g_enemy[i].spider.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].spider.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 雑魚敵が倒されたかを確認
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].spider.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// 出現した雑魚敵が全て倒されていたら攻撃終了
	if (enemyDropCnt >= 3) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			g_boss[g_select_Stage].attackFlg = 0;    // attackフラグを初期化
			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			enemy_dispFlg_Buf[1] = { FALSE };
			enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}
// 動き
void Boss_MiniSpider_Drop_Move() {


	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // ミニ蜘蛛の最大数回す


		if (g_enemy[i].spider.flg == TRUE) {
			g_enemy[i].spider.x -= (g_speedLevel - 3);		// ミニ蜘蛛の移動

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].spider.x + ENEMY_WIDTH < 0) {		// 画面外にいくと初期化

			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			//g_enemy[i].walk.flg = TRUE;
		}
	}
}
/*********************************************

* カエルのボスが舌を伸ばす攻撃

*/////////////////////////////////////////////

void BossLongTon_Disp() {
	static int plas = 0;			// 長くしていく
	g_boss4_JumpAnime = 4;
	// ボスの舌の座標の初期化
	g_boss3_Ton.Boss3_TonInit(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y + BOSS_STAGE3_HEIGHT / 2);
	// ボスの舌の幅と高さの初期化
	int tonW = g_boss3_Ton.x + plas;
	int tonH = g_boss3_Ton.y + BOSS_TON_HEIGHT;

#ifdef DEBUG_BOSS_ON
	DrawFormatString(500, 500, 0x0000FF, "plas=%d\tonH=%d", plas, tonH);
#endif // DEBUG_BOSS_ON

	// 舌の画像
	DrawModiGraph(tonW, g_boss3_Ton.y,	// 左上
		g_boss3_Ton.x, g_boss3_Ton.y,					// 右上
		g_boss3_Ton.x, tonH,			// 右下
		tonW, tonH,		// 左下
		g_pic.bossTongue, TRUE);
	//DrawBox(g_boss3_Ton.x, g_boss3_Ton.y, tonW, tonH, 0xFFFF00, TRUE);

	// 舌の画像を引き延ばす処理
	if (tonW > -100) {
		plas -= 5;
	}
	else {
		tonW = 0;
	}

	if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {		// ボスが攻撃されたら攻撃中断してジャンプして逃げる
		g_boss[BOSS_STAGE3].attackFlg = 0;		// attackフラグを初期化
		plas = 0;

		//boss_JumpFlg = BOSS_3_JUMPON;
	}														   // ボスがプレイヤーに当たったら、ダメージを与えて逃げる
	else if (PlayerHitCheck(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, BOSS_STAGE3_WIDTH, BOSS_STAGE3_HEIGHT) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		g_noDamageCnt = 0;
		g_boss[BOSS_STAGE3].attackFlg = 0;		// attackフラグを初期化
		plas = 0;
	}

	// ボスの舌がプレイヤーに当たったら、ダメージを与えて逃げる		* 横幅で -10 しているのはプレイヤーに当たらない為の調整
	if (PlayerHitCheck(g_boss3_Ton.x + plas, g_boss3_Ton.y, (plas * -1), BOSS_TON_HEIGHT - 10) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		g_noDamageCnt = 0;
		g_boss[BOSS_STAGE3].attackFlg = 0;		// attackフラグを初期化
		plas = 0;
	}	
}

void BossLongTon_Move() {

	g_boss[BOSS_STAGE3].x -= 2;

	//if (Boss_3_Jump(&coolTime, &boss_JumpFlg, 1) == TRUE) {
	//	g_boss[BOSS_STAGE3].attackFlg = 0;	// attackフラグをオフへ
	//}
}

/*********************************************

* ボス３のジャンプする動き

*/////////////////////////////////////////////
bool Boss_3_Jump(int *coolTime, int *boss_JumpFlg, int jumpType) {
	int boss_MaxUp = 150;									// ボス３がジャンプしていけるY座標最高度
	int boss_MaxDown = GROUND - BOSS_STAGE3_HEIGHT;			// ボス３の落下した際のY地点
	int boss_startX = 822;									// ボス３のX座標の初期値



	if (*boss_JumpFlg == BOSS_3_JUMPON) {					// 上昇
		if (g_boss[BOSS_STAGE3].y >= boss_MaxUp) {			// ボスを特定地点まで上に上げる
			
			if (jumpType == 1) {							// 受けたジャンプフラグが攻撃中なのかどうかを確認して１なら横に飛ばす
				if (g_boss[BOSS_STAGE3].x < boss_startX) {
					g_boss[BOSS_STAGE3].x += 6;				// ボスが横に吹っ飛ぶ
					g_boss[BOSS_STAGE3].y -= 2;				// 若干上に上がりながら
				}
				else {
					*boss_JumpFlg = BOSS_3_DOWN;			// 下降させる
				}
			}
			else {
				g_boss4_JumpAnime = 1;
				g_boss[BOSS_STAGE3].y -= 2;					// 真上にジャンプする
			}
		}
		else if (g_boss[BOSS_STAGE3].y < boss_MaxUp) {		// 特定地点まで来たら座標を固定
			//g_boss4_JumpAnime = 2;
			g_boss[BOSS_STAGE3].y = boss_MaxUp;
			*boss_JumpFlg = BOSS_3_DOWN;					// 下降させる

		}
	}
	else if (*boss_JumpFlg == BOSS_3_DOWN) {				// 下降
		if (g_boss[BOSS_STAGE3].y < boss_MaxDown) {			// ボスを特定地点まで上に上げる
			g_boss4_JumpAnime = 3;
			g_boss[BOSS_STAGE3].y += 2;
		}
		else if (g_boss[BOSS_STAGE3].y >= boss_MaxDown) {	// 特定地点まで来たら座標を固定
			//g_boss[BOSS_STAGE3].x = boss_startX;
			g_boss[BOSS_STAGE3].y = boss_MaxDown;
			g_boss4_JumpAnime = 0;
			*boss_JumpFlg = BOSS_3_JUMPOFF;	// ジャンプフラグをオフへ
			*coolTime = 0;		// クールタイムを初期化
			return TRUE;
		}


	}

	return FALSE;


}
/*********************************************

* ボスがジャンプして稀に毒を出す処理

*/////////////////////////////////////////////
void BossJumpOrPoison_Disp() {

}

void BossJumpOrPoison_Move() {

}
/*********************************************

* ボスが弱い敵を出す攻撃をする関数

*/////////////////////////////////////////////
// 歩く弱い敵を出す(表示)
void BossEnemyDropDisp() {
	
	BossAreaEnemyDisp();
}
// 弱い敵を出す(動き(当たり判定など))
void BossEnemyDropMove() {

	BossAreaEnemyMove();
}

// 
void BossAreaEnemyDisp() {
	static int coolTime = 0;
	static int enemyDropCnt = 0;
	static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // 
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++coolTime > 60) {
		// エネミーの出現フラグをオンにする
		
		if (g_enemy[enemy_cnt].walk.flg == FALSE && enemy_cnt < 3) {
			g_enemy[enemy_cnt].walk.flg = TRUE;
			coolTime = 0;
				
			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}
	
	// 雑魚敵の描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// アニメーションのカウント
		if (time++ % 8 == 0) {
			g_enemy[i].walk.anime++;
			
		}

		// アニメーションの初期化
		if (g_enemy[i].walk.anime > animation_Max)g_enemy[i].walk.anime = 0;


		if (g_enemy[i].walk.flg == TRUE)        // 雑魚敵の描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE); 
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	
	// 雑魚敵が倒されたかを確認
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].walk.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// 出現した雑魚敵が全て倒されていたら攻撃終了
	if (enemyDropCnt >= 3) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			g_boss[g_select_Stage].attackFlg = 0;    // attackフラグを初期化
			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			enemy_dispFlg_Buf[1] = { FALSE };
			enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}
// 
void BossAreaEnemyMove() {


	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // 歩く雑魚敵の最大数回す
		
		
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= (g_speedLevel - 3);		// 歩く雑魚敵の移動

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}
			
		if (g_enemy[i].walk.x + ENEMY_WIDTH < 0) {			// 画面外へいくと初期化

			g_enemy[i].walk.BossArea_WlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			//g_enemy[i].walk.flg = TRUE;
		}

		
	}
}

/*********************************************

* ボスが水弾で攻撃をする関数

*/////////////////////////////////////////////
// 水弾の描画
void BossWaterBulletDisp() {
	static int animationMax = 3;			// アニメーション
	static int anime = 0;				// アニメ推移
	static int time = 0;				// 経過時間
	static int startX = g_boss[BOSS_STAGE1].x + 100,
				startY = g_boss[BOSS_STAGE1].y + 200;	// 水弾の初期位置
	static int moveX = 0, moveY = 0;	// 水弾の移動量
	static int noDamegeCnt = 60;		// ダメージを受け付けない時間
	static bool attackFlg = FALSE;		// 攻撃判断フラグ	 treu:攻撃済  false:未攻撃

	// フレーム単位の被弾数の調整
	noDamegeCnt++;

	// プレイヤーに水弾が当たった時の処理
	if (noDamegeCnt >= 60
		&& (PlayerHitCheck(startX + moveX - 40, startY + moveY + 0,
			startX + moveX + 40, startY + moveY - 20) == TRUE)) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 200) {
			g_boss[BOSS_STAGE1].attackFlg = 0;
		}
	}

	// 水弾が画面外に出たときの処理
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}

	// 水弾が切られた時の処理
	if( (g_player.attackFlg == TRUE)
		&& (noDamegeCnt >= 30)
		&& (* SkillMove[g_player.skillFlg])(startX + moveX - 40, startY + moveY - 20, 65, 55) == TRUE){
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 20) {
			g_boss[BOSS_STAGE1].attackFlg = 0;
		}

	}

	// 水弾のアニメーション
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// 水弾の表示
	if (attackFlg == FALSE) {
		moveX -= 7.5;
		moveY += 2.5;
		/*moveX -= 3.0;
		moveY += 1.0;*/
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[anime], TRUE, FALSE);
		/*DrawBox(startX + moveX - 40, startY + moveY - 20,
			startX + moveX + 25, startY + moveY + 35, 0xFF0000, FALSE);*/
	}
	else if (attackFlg == TRUE) {
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[animationMax], TRUE, FALSE);
	}

	// 座標とフラグの初期化
	if (attackFlg == TRUE
		&& noDamegeCnt >= 20) {
		moveX = 0;
		moveY = 0;
		anime = 0;
		animationMax = 3;
		attackFlg = FALSE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}



	// デバッグ
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
}
// 水弾の内部的な動き
void BossWaterBulletMove() {

}

/***********************************************************

// ボスがダメージを食らったときのアニメーション

***********************************************************/
void Boss_Damage_Disp(bool *boss_damage, int bx, int by, int GrHandle, double magnification){

	bx += InputRand(50, -50, 30);
	by += InputRand(50, -50, -30);
	// ボスの残像
	SetDrawBright(255, 99, 71);
	DrawRotaGraph2(bx, by, 0, 0, magnification, 0.0, GrHandle, TRUE);
	SetDrawBright(255, 255, 255);
	static int cnt = 0;

	if (cnt++ > 30) {
		*boss_damage = FALSE;
		cnt = 0;
	}

}
void Boss_Damage_Disp2(bool* boss_damage, int bx, int by, int GrHandle, double magnification) {

	bx += InputRand(50, -50, 30);
	by += InputRand(50, -50, -30);
	// ボスの残像
	SetDrawBright(255, 99, 71);
	DrawRotaGraph2(bx, by, 0, 0, magnification, 0.0, GrHandle, TRUE);
	SetDrawBright(255, 255, 255);
	static int cnt = 0;

	if (cnt++ > 30) {
		*boss_damage = FALSE;
		cnt = 0;
	}

}
void Boss_Damage_Disp3(bool* boss_damage, int bx, int by, int GrHandle, double magnification) {

	bx += InputRand(50, -50, 30);
	by += InputRand(50, -50, -30);
	// ボスの残像
	SetDrawBright(255, 99, 71);
	DrawRotaGraph2(bx, by, 0, 0, magnification, 0.0, GrHandle, TRUE);
	SetDrawBright(255, 255, 255);
	static int cnt = 0;

	if (cnt++ > 30) {
		*boss_damage = FALSE;
		cnt = 0;
	}

}
/***********************************************************

// 数字を引数として三つ取り、その中の一つをランダムで返す

***********************************************************/
int InputRand(int rand1, int rand2, int rand3) {
	int num = GetRand(3);
	switch (num)
	{
	case 0: return rand1; break;
	case 1: return rand2; break;
	case 2: return rand3; break;
	default: return 0;	  break;
	}

}/***********************************************************

// 数字を引数として八つ取り、その中の一つをランダムで返す

***********************************************************/
int InputHyperRand(int rand1, int rand2, int rand3, int rand4, int rand5, int rand6, int rand7, int rand8) {
	int num = GetRand(8);
	switch (num)
	{
	case 0: return rand1; break;
	case 1: return rand2; break;
	case 2: return rand3; break;
	case 3: return rand4; break;
	case 4: return rand5; break;
	case 5: return rand6; break;
	case 6: return rand7; break;
	case 7: return rand8; break;
	default: return 0;	  break;
	}
}

/***********************************************************

// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない

***********************************************************/
bool BossDamageCheck(int bossHp) {
	static int bossHpBuf = bossHp;

	if (bossHp <= bossHpBuf) {
		if (bossHp < bossHpBuf) {
			bossHpBuf = bossHp;
			return TRUE;
		}
	}

	bossHpBuf = bossHp;
	return FALSE;
}
/***********************************************************

// ボスが攻撃を終えたかを調べる関数TRUE: ボスの攻撃終了 FALSE: ボスは攻撃中、または終了してしばらくたっている

***********************************************************/
bool BossNoAttackCheck(int bossAttackFlg) {
	static int bossAttackBuf = bossAttackFlg;

	if (bossAttackFlg == 0 && bossAttackBuf != 0) {		
		bossAttackBuf = bossAttackFlg;
		return TRUE;
	}

	bossAttackBuf = bossAttackFlg;
	return FALSE;
}
/***********************************************************

// ボスが違う攻撃をするたびエネミードロップを初期化する関数TRUE: ボスの攻撃開始 FALSE: ボスは攻撃中、または終了してしばらくたっている

***********************************************************/
bool BossDropAttackCheck(int bossAttackFlg) {
	static int bossAttackBuf = bossAttackFlg;

	/*if (bossAttackFlg != 0 && bossAttackBuf == 0) {*/
	if (bossAttackFlg != bossAttackBuf) {
		bossAttackBuf = bossAttackFlg;
		return TRUE;
	}

	bossAttackBuf = bossAttackFlg;
	return FALSE;
}
/***********************************************************

// ボスの初期化

***********************************************************/
void BossInit() {
	for (int i = BOSS_STAGE1; i < BOSS_MAX; i++) {
		g_boss[i].Init_Stage(i);		// 全ステージのボスの初期化
	}
	g_boss4_JumpAnime = 0;	// アニメーションの初期化
	g_boss3_Ton.Boss3_TonInit(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y + BOSS_STAGE3_HEIGHT / 2);// ステージ３のボスの舌の初期化
	Boss_Stage4_Init();	// ボスステージ４の雲の初期化
	Boss5_Init();		// ボス５の初期化
	Boss6_Init();		// ボス６の初期化
	LastBossInit();     // ラスボス前の７体の蛇の初期化
}