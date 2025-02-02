
#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "HP.h"
#include "Skill.h"
#include "Select.h"
#include "Sounds.h"

#define G                (0.5F)		// 重力
#define JUMP_POWER       (15.0F)	// ジャンプ力



float g_speed = 0.0F;	//落ちる速度
int g_resetMotion = 0;	//アニメーション始点
int g_maxMotion = 7;	//終点
int g_attackTime = 0;	//攻撃のクールタイム
bool g_skillFlg;		// スキル中かどうかのフラグ
int g_SkillSelectAicon = 0; //スキルのアイコン移動
//bool g_swordFlg = FALSE; //TRUE = 抜刀, FALSE = 納刀
int g_cloneDamage = 0;		//スキル7のダメージ変化

void PlayerDisp() {
	static int anime = 0;							// プレイヤーの画像を変える
	static int time = 0;							// 画像を切り替えるタイミング調整
	static float skillTime[3] = { 0 };				// スキルクールタイム
	static int skill7Anime = 0;						//スキル7アニメーション
	static int skill6Anime[2] = { 0 };				//スキル6アニメーション
	static int skill5Anime = 0;					//スキル5アニメーション
	static int lifeBox = 3;						//ライフを一時的に保存

	if (++time % 4 == 0) anime++;
	if (anime < g_resetMotion || anime > g_maxMotion) anime = g_resetMotion;

	if (g_player.hp != lifeBox) {//ダメージを受けたらスキル7解除
		PlaySoundMem(g_sound[VOICE_DAMAGE], DX_PLAYTYPE_BACK, TRUE);			//ダメージSE再生
		if (g_player.cloneFlg == TRUE)g_player.cloneFlg = FALSE;
		lifeBox = g_player.hp;
	}

	if (g_player.barrierFlg == TRUE) {
		//スキル6バリア表示
		if (skill6Anime[0] < 150 && skill6Anime[1] == 0) skill6Anime[0] += 5;
		if (skill6Anime[0] > 50 && skill6Anime[1] == 1) skill6Anime[0] -= 5;
		if (skill6Anime[0] >= 150) skill6Anime[1] = 1;
		if (skill6Anime[0] <= 50) skill6Anime[1] = 0;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 + skill6Anime[0]);
		DrawGraph(g_player.x - 80, g_player.y - 300, g_pic.skillEffect[25], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - skill6Anime[0]);
		DrawGraph(g_player.x - 80, g_player.y - 300, g_pic.skillEffect[26], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// 残像
	PlayerAfterimage(anime);
	//プレイヤーの描画
	if (g_player.attackFlg == FALSE && g_noDamageCnt > 60) {
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime], TRUE);
	}
	else if (g_player.powerUpFlg == TRUE && g_player.powerUpTime == 0) {//スキル５突進
		skill5Anime++;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (skill5Anime * 10));
		DrawRotaGraph((g_player.x) - skill5Anime * 25, g_player.y - 190, 2, 0.0, g_pic.skillEffect[20 + (skill5Anime / 5)], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.SkillMotion[13], TRUE);
	}
	else if (g_noDamageCnt < 60 && g_player.powerUpTime > 0) {
		if (g_noDamageCnt % 12 == 0) //無敵時間発生時
			DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[48], TRUE);
	}

	if (g_player.powerUpFlg == TRUE) {//スキル5　仮
		//DrawBox(g_player.x, g_player.y, g_player.x + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0x00ffff, TRUE);
		//DrawRotaGraph(g_player.x + 100, g_player.y + 70, 2, 0.0, g_pic.Life[1], TRUE);
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.skill5Effect[(skill5Anime / 5) % 4], TRUE);
		skill5Anime++;

		if (g_player.powerUpTime > 0) g_player.powerUpTime--;
		else {
			if (g_player.jumpFlg == FALSE) {
				PlaySoundMem(g_sound[SKILL5_SE], DX_PLAYTYPE_BACK, FALSE);			//スキル5SE再生
				g_noDamageCnt = 0;
				if (g_player.x < 900) g_player.x += 50, g_player.jumpFlg == FALSE, EnemyCut();
				else g_player.powerUpTime = SKILL5_TIME, g_player.powerUpFlg = FALSE, skill5Anime = 0;
			}
		}
	}
	//スキル7の分身
	if (g_player.cloneFlg == TRUE) {
		DrawRotaGraph2(g_player.x - 40, g_player.y + 2, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.skill7_Effect[anime], TRUE);
		DrawGraph(g_player.x - 200, g_player.y - 220, g_pic.skillEffect[30 + (skill7Anime / 10) % 2], TRUE);
		skill7Anime++;
	}

#ifdef DEBUG_SKILL_ON
DrawFormatString(500, 0, 0xff0000, "%d", g_attackTime);
	DrawFormatString(600, 0, 0xffffff, "%d", g_boss[g_select_Stage].hp);
	DrawFormatString(0, 400, 0xFF0000, "%d", g_player.skillFlg);
	DrawFormatString(0, 600, 0xFFFF00, "%f", g_player.skillCoolTime[g_player.skillNo]);
	DrawFormatString(0, 700, 0x00FFFF, "%d", g_player.skillNo);
	DrawFormatString(0, 750, 0x0000FF, "%d", g_player.powerUpTime);
	DrawFormatString(100, 750, 0xFF00FF, "%d", g_noDamageCnt);
#endif // DEBUG_SKILL_OFF
	

	if (g_player.skillFlg != 0) {
		SkillDisp[g_player.skillFlg - 1](g_maxMotion, g_resetMotion);
	}

	//仮
	//static float gauge = 320;
	DrawGraph(20, -40, g_pic.PlayerUI, TRUE);					//アイコン
	//DrawBox(80, 120, 80 + gauge, 130, 0xFF0000, TRUE);
	DrawRectGraph(75, -40, 0, 0, g_player.gauge, 240, g_pic.gauge, TRUE, FALSE); //ゲージ
	if (g_player.swordFlg == TRUE) {
		if (g_player.gauge > 0) g_player.gauge -= 0.1;
	}
	else {
		if (g_player.gauge < 265 && g_player.useSkillGage <= 0) g_player.gauge += 0.5;
	}
	if (g_player.cloneFlg == TRUE) {
		if (g_player.gauge > 0) g_player.gauge -= 0.4;
	}

	//スキル使用時のゲージ減少
	//if (g_player.attackFlg == TRUE) g_player.gauge -= 2;
	if (g_player.useSkillGage > 0) {
		g_player.useSkillGage -= g_player.skillFlg;
		g_player.gauge -= g_player.skillFlg;
	}

	if (g_player.gauge < 0) g_player.gauge = 0;

	//スキルの再使用までのクールタイム
	for (int i = 0; i < 3; i++) {
		if ((g_keyInfo.keyFlg & PAD_INPUT_B) && skillTime[i] <= 0) {
			if (g_player.swordFlg == FALSE) {
				skillTime[i] = g_player.skillCoolTime[i];
			}
			else {
				g_player.skillCoolTime[i] = g_player.skillCoolTime[i] / 2;
				skillTime[i] = g_player.skillCoolTime[i];
			}
		}
		if (g_player.skillCoolTime[i] > 0) g_player.skillCoolTime[i] -= 0.1F;
		if (g_player.skillCoolTime[i] < 0) g_player.skillCoolTime[i] = 0.0F, skillTime[i] = 0;
	}

	//スキル光表示
	DrawRotaGraph(WINDOW_WIDTH / 2 + g_SkillSelectAicon, WINDOW_HEIGHT - 70, 1, -time / 8, g_pic.skillRing[0], TRUE);
	//装備しているスキル表示
	DrawGraph(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[0]], TRUE);
	DrawGraph(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[1]], TRUE);
	DrawGraph(WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[2]], TRUE);

	//クールタイム
	SetDrawBright(255, 0, 0);
	DrawCircleGauge(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[0] / skillTime[0]) * float(100), g_pic.skillAicon[g_player.skillcustom[0]]);
	DrawCircleGauge(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[1] / skillTime[1]) * float(100), g_pic.skillAicon[g_player.skillcustom[1]]);
	DrawCircleGauge(WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[2] / skillTime[2]) * float(100), g_pic.skillAicon[g_player.skillcustom[2]]);
	SetDrawBright(255, 255, 255);

	//勾玉表示
	DrawRotaGraph(WINDOW_WIDTH / 2 + g_SkillSelectAicon, WINDOW_HEIGHT - 70, 1, time / 8, g_pic.skillRing[1], TRUE);

}

void PlayerMove() {
	PlayerJump();		// プレイヤーのジャンプ処理
	PlayerControl();	// プレイヤーを操作する関数
	PlayerAnimation();
	//if (g_player.skillFlg != 0) {
	//	SkillMove[g_player.skillFlg - 1]();
	//}
}

// プレイヤーの残像
void PlayerAfterimage(int anime) {
	static int resetMotion_Buf[3] = { 0, 0, 0 };		// マイフレームのプレイヤーのアニメーションを格納
	static int maxMotion_Buf[3] = { 0, 0, 0 };		// マイフレームのプレイヤーのアニメーションを格納
	if (g_player.swordFlg == TRUE) {
		int anime_Buf = anime - 1;					// 過去のプレイヤーアニメーションを格納する
		resetMotion_Buf[2] = resetMotion_Buf[1];
		resetMotion_Buf[1] = resetMotion_Buf[0];
		resetMotion_Buf[0] = g_resetMotion;

		maxMotion_Buf[2] = maxMotion_Buf[1];
		maxMotion_Buf[1] = maxMotion_Buf[0];
		maxMotion_Buf[0] = g_maxMotion;

		for (int i = 0; i < 3; i++) {
			if (anime_Buf < resetMotion_Buf[i] || anime_Buf > maxMotion_Buf[i]) anime_Buf = resetMotion_Buf[i];
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			// 残像プレイヤー表示
			//g_player.y = g_mouseInfo.mouseY;
			DrawRotaGraph2(g_player.x - ((i + 1) * 30), g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime_Buf], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

//プレイヤーのアニメーション
void PlayerAnimation() {
	//static int time = 0;	//抜刀、納刀の切り替え
	if (g_player.swordFlg == FALSE) {
		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_player.timecount = 10;
		}
	} else {
		if (g_keyInfo.keyFlg & PAD_INPUT_4){
			g_player.timecount = 10;
		}
	}

	//納刀状態のアニメーション
	if (g_player.swordFlg == FALSE) {
		if (g_player.jumpFlg == TRUE) {		//ジャンプ
			if (g_speed < 0) {
				g_resetMotion = CLOSE_JUMP_UP;
				g_maxMotion = CLOSE_JUMP_UP;
			}
			else {
				g_resetMotion = CLOSE_JUMP_DOWN_S;
				g_maxMotion = CLOSE_JUMP_DOWN_E;
			}
		}
		else {
			g_resetMotion = CLOSE_MOVE_S;
			g_maxMotion = CLOSE_MOVE_E;
		}
		if (g_player.attackFlg == TRUE) {//スキル攻撃(仮)
			g_resetMotion = 32;
			g_maxMotion = 32;
		}
	}

	//抜刀状態のアニメーション
	if (g_player.swordFlg == TRUE) {
		if (g_player.jumpFlg == TRUE) {		//ジャンプ
			if (g_speed < 0) {
				g_resetMotion = OPEN_JUMP_UP;
				g_maxMotion = OPEN_JUMP_UP;
			}
			else {
				g_resetMotion = OPEN_JUMP_DOWN_S;
				g_maxMotion = OPEN_JUMP_DOWN_E;
			}
		}
		else {
			g_resetMotion = OPEN_MOVE_S;
			g_maxMotion = OPEN_MOVE_E;
		}
		if (g_player.attackFlg == TRUE) {//スキル攻撃(仮)
			g_resetMotion = 32;
			g_maxMotion = 32;
		}
	}
	if (g_player.timecount <= 10 && g_player.swordFlg == FALSE) {//通常時の抜刀
		if (--g_player.timecount > 0) g_resetMotion = SWORD_OPEN_S, g_maxMotion = SWORD_OPEN_E;
	}
	if (g_player.timecount == 0 && g_player.swordFlg == FALSE) {
		g_player.swordFlg = TRUE;
		if(g_player.useSkillFlg == TRUE) g_player.attackFlg = TRUE;
	}
	if (g_player.timecount <= 10 && g_player.swordFlg == TRUE) {//納刀
		if (--g_player.timecount > 0) g_resetMotion = SWORD_CLOSE_S, g_maxMotion = SWORD_CLOSE_E;
	}
	if (g_player.timecount == 0 && g_player.swordFlg == TRUE) {
		g_player.swordFlg = FALSE;
		g_player.useSkillFlg = FALSE;
	}

	if (g_boss[g_select_Stage].hp <= 0) {
		g_resetMotion = CLOSE_MOVE_S;
		g_maxMotion = CLOSE_MOVE_E;
	}
}

// ジャンプ処理
void PlayerJump() {
	//ジャンプ処理(×ボタン)
	if (g_player.jumpFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_A && g_player.powerUpTime > 0) {
		PlaySoundMem(g_sound[SE_JUMP], DX_PLAYTYPE_BACK, FALSE);			//ジャンプSE再生
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;

	if (g_player.y >= GROUND - PLAYER_HEIGHT) {
		if (g_player.jumpFlg == TRUE) {
			PlaySoundMem(g_sound[SE_TYAKUTI], DX_PLAYTYPE_BACK, FALSE);			//着地SE再生
		}
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
		g_player.y = GROUND - PLAYER_HEIGHT;
		PlaySoundMem(g_sound[SE_STEP], DX_PLAYTYPE_BACK, FALSE);			//歩くSE再生
	}
}
// ボタンを押した時の処理
void PlayerControl() {
	//攻撃(〇ボタン)
	//if (g_player.attackFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if ((g_player.attackFlg == FALSE && g_skillFlg == TRUE) && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if(g_skillFlg == TRUE){
		//g_player.x += 500.0F;
		//g_player.attackFlg = TRUE;
	//}

	//if (g_keyInfo.keyFlg & PAD_INPUT_3) {
	//	g_player.attackFlg = TRUE;
	//}

	if (g_player.attackFlg == TRUE) {
		g_attackTime++;
	}
	if (g_attackTime > 20) {
		g_attackTime = 0;
		g_player.attackFlg = FALSE;
		if(g_player.useSkillFlg == TRUE)g_player.timecount = 10;

	}
	if (g_player.x > 100 && g_player.attackFlg == FALSE) {
		g_player.x -= 5.0F;
	}

	if (g_player.x < 100) g_player.x = 100;


	//通常攻撃
	/*if (g_player.skillFlg == 0 && (g_keyInfo.keyFlg & PAD_INPUT_3)) {
		//g_player.attackFlg = TRUE;
		EnemyCut();		// エネミーを倒す処理
	}*/


	//(□ボタン??)
	if (g_button.squareButton == true) {

	}
	
	static int cnt = 0;
	// スキルオンオフ
	SkillChange();
	/*
	if (g_player.skillFlg != 0) {
		if (g_keyInfo.keyFlg & PAD_INPUT_4)
			g_player.skillFlg = 0;
	}
	else {

		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_player.skillFlg = SkillChange();

		}
	}*/
	g_player.skillFlg = SkillChange();

}

int SkillChange() {
	static int skillNum = 0; //配列
	static int useSkill = 1; //使うスキル

	if (g_player.attackFlg == FALSE) {
		// スキル選択
		if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
			if (++skillNum > 2) skillNum = 0,SkillInit();
		}
		if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
			if (--skillNum < 0) skillNum = 2, SkillInit();
		}
	}

	if (skillNum == 0) g_SkillSelectAicon = 0;
	if (skillNum == 1) g_SkillSelectAicon = -100;
	if (skillNum == 2) g_SkillSelectAicon = 100;

#ifdef DEBUG_SKILL_ON
	// skillNumの中身
	DrawFormatString(0, 500, 0xFEFFFF, "%d", skillNum);
#endif // DEBUG_SKILL_ON
	
	g_player.skillNo = skillNum;

	useSkill = g_player.skillcustom[skillNum];

	return useSkill;
}


// 敵を間合いに入ったらロックオンをする処理
void EnemyLockOn() {

#ifdef DEBUG_SKILL_ON
	DrawBox(g_player.x + PLAYER_WIDTH, g_player.y, g_player.x + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0xFF0000, 0);
#endif // DEBUG

	EnemyCut();		// エネミーを倒す処理
}

// プレイヤーの間合いに入っている敵を倒す処理
void EnemyCut() {
	static int enemyNum = 0;	// 同時に倒した敵をカウントする変数
	static int noDamageCnt = 61;// ボスの無敵時間

	if (g_player.cloneFlg == FALSE) g_cloneDamage = 1;
	else g_cloneDamage = 2;

	for (int i = 0; i < ENEMY_MAX; i++) {
		// 歩く敵
		if ((g_enemy[i].walk.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
			|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// レティクル表示
			//DrawRotaGraph2(g_enemy[i].walk.x + (ENEMY_WIDTH / 3), g_enemy[i].walk.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// 敵を倒す処理
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].walk.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].walk.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].walk.x, g_enemy[i].walk.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].walk.WalkInit();
					PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
				}
				else {
					g_enemy[i].walk.BossArea_WlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
				}
				//g_player.attackFlg = TRUE;
			}
		}
		// 飛んでいる敵
		if ((g_enemy[i].fly.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
			|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// レティクル表示

#ifdef DEBUG_SKILL_ON
			DrawRotaGraph2(g_enemy[i].fly.x + (ENEMY_WIDTH / 3), g_enemy[i].fly.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
#endif // DEBUG_SKILL_ON

			// 敵を倒す処理
			if (g_player.skillFlg == 2) {
				//g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].fly.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].fly.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				/*if (g_skillFlg == TRUE) g_player.x = g_enemy[i].fly.x - PLAYER_WIDTH;
				g_player.y = g_enemy[i].fly.y - PLAYER_HEIGHT;*/
				//g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].fly.x, g_enemy[i].fly.y);
				g_enemy[i].fly.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
				//g_player.attackFlg = TRUE;
			}
		}
		// ミニ蜘蛛
		if ((g_enemy[i].spider.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].spider.x, g_enemy[i].spider.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
				|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].spider.x, g_enemy[i].spider.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// レティクル表示
			DrawRotaGraph2(g_enemy[i].spider.x + (ENEMY_WIDTH / 3), g_enemy[i].spider.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// 敵を倒す処理
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].spider.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].spider.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].spider.x, g_enemy[i].spider.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].spider.WalkInit();
					PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生																// 倒されたら初期化
				}
				else {
					g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	// ボスエリアで倒された場合初期化方法を変える
				}
				//g_player.attackFlg = TRUE;
			}
		}
		// ミニ雲
		if ((g_enemy[i].cloud.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].cloud.x, g_enemy[i].cloud.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
				|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].cloud.x, g_enemy[i].cloud.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// レティクル表示
			DrawRotaGraph2(g_enemy[i].cloud.x + (ENEMY_WIDTH / 3), g_enemy[i].cloud.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// 敵を倒す処理
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].cloud.FlyInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].cloud.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].cloud.x, g_enemy[i].cloud.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].cloud.WalkInit();
					PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生															// 倒されたら初期化
				}
				else {	
					g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	// ボスエリアで倒された場合初期化方法を変える
				}
				//g_player.attackFlg = TRUE;
			}
		}
		// ミニクラゲ
		if ((g_enemy[i].kurage.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
				|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// レティクル表示
			DrawRotaGraph2(g_enemy[i].kurage.x + (ENEMY_WIDTH / 3), g_enemy[i].kurage.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// 敵を倒す処理
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].kurage.FlyInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemy[i].kurage.WalkInit();
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// エネミーを倒した数をカウント
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].kurage.x, g_enemy[i].kurage.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
					PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//killSE再生						// 倒されたら初期化
				}
				else {
					g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);	// ボスエリアで倒された場合初期化方法を変える
				}
				//g_player.attackFlg = TRUE;
			}
		}
	}
	//boss
	if (g_enemybeat >= ENEMY_BEAT_MAX[g_select_Stage]) {
		if (PlayerInterval(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE
			|| (SkillMove[g_player.skillFlg - 1](g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE)) {
			if (++noDamageCnt > 60 && g_boss[g_select_Stage].hp > 0) {
				if (g_player.skillFlg == 2) {
					g_boss[g_select_Stage].hp -= 1 * g_cloneDamage;
					g_boss[g_select_Stage].damageFlg = TRUE;
					noDamageCnt = 0;
				}
				//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
				if (g_player.attackFlg == TRUE) {
					//if (g_skillFlg == TRUE) g_player.x = g_boss[0].x - PLAYER_WIDTH;
					if (g_player.skillFlg == 1) g_boss[g_select_Stage].hp -= 2 * g_cloneDamage;
					if (g_player.skillFlg == 3) g_boss[g_select_Stage].hp -= 3 * g_cloneDamage;
					if (g_player.powerUpFlg == TRUE) g_boss[g_select_Stage].hp -= 1 * g_cloneDamage;
					g_boss[g_select_Stage].damageFlg = TRUE;
					noDamageCnt = 0;
				}

				if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
					g_boss[g_select_Stage].hp -= 5 * g_cloneDamage;
					g_boss[g_select_Stage].damageFlg = TRUE;
					noDamageCnt = 0;
				}
			}
		}
		// 糸
		if (PlayerInterval(g_boss4_Thread.x, g_boss4_Thread.y, (g_boss4_Thread.w - g_boss4_Thread.x), (g_boss4_Thread.h - g_boss4_Thread.y)) == TRUE
			|| (SkillMove[g_player.skillFlg - 1](g_boss4_Thread.x, g_boss4_Thread.y, (g_boss4_Thread.w - g_boss4_Thread.x), (g_boss4_Thread.h - g_boss4_Thread.y)) == TRUE)) {
			if (++noDamageCnt > 60 && g_boss4_Thread.hp <= 0) {
#ifdef DEBUG_MODE_ON
				DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, TRUE);
#endif // DEBUG

			}
		}

		// ラスボス前の７体の蛇
		for (int i = 0; i < YAMATANO_NECK; i++) {
			if (g_select_Stage == BOSS_LASTBOSS) {
				if (g_boss_Yamatano[i].popflg == LASTBOSS_ON) {
					if (PlayerInterval(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h) == TRUE
						|| (SkillMove[g_player.skillFlg - 1](g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h) == TRUE)) {

						if (++noDamageCnt > 60 && g_boss_Yamatano[i].hp > 0) {
							if (g_player.skillFlg == 2) {
								g_boss_Yamatano[i].hp -= 1 * g_cloneDamage;
								g_boss_Yamatano[i].damageFlg = TRUE;
								noDamageCnt = 0;
							}
							//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
							if (g_player.attackFlg == TRUE) {
								//if (g_skillFlg == TRUE) g_player.x = g_boss[0].x - PLAYER_WIDTH;
								if (g_player.skillFlg == 1) g_boss_Yamatano[i].hp -= 2 * g_cloneDamage;
								if (g_player.skillFlg == 3) g_boss_Yamatano[i].hp -= 3 * g_cloneDamage;
								if (g_player.powerUpFlg == TRUE) g_boss_Yamatano[i].hp -= 1 * g_cloneDamage;
								g_boss_Yamatano[i].damageFlg = TRUE;
								noDamageCnt = 0;
							}

							if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
								g_boss_Yamatano[i].hp -= 5 * g_cloneDamage;
								g_boss_Yamatano[i].damageFlg = TRUE;
								noDamageCnt = 0;
							}
						}
					}
				}
			}
		}
	}
	enemyNum = 0;
}
// プレイヤーの画像と敵の画像の当たり判定 (TRUE: 当たった | FALSE: 当たらなかった)
bool PlayerInterval(int ex, int ey, int ew, int eh) {
	//通常攻撃判定
	if (g_player.skillFlg == 0) {
		if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
			&& ((long int)g_player.x + (long int)PLAYER_WIDTH /*+ (long int)PLAYER_WIDTH*/ >= ex)
			&& ((long int)g_player.y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
			&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
			return TRUE;
		}
	}

	if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {

		if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
			&& ((long int)g_player.x + (long int)PLAYER_WIDTH + PLAYER_WIDTH >= ex)
			&& ((long int)g_player.y - (long int)PLAYER_HEIGHT <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
			&& ((long int)g_player.y + (long int)PLAYER_HEIGHT >= ey)) {
			return TRUE;
		}
	}
	////間合いが伸びるスキル判定
	//if (g_player.skillFlg == 1) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	////飛ぶ斬撃攻撃判定（未完）
	////DrawBox(skill_X + g_skillAnime, skill_Y, skill_X + PLAYER_WIDTH + PLAYER_WIDTH + g_skillAnime, skill_Y + PLAYER_HEIGHT, 0x0000ff, true);
	//if (g_player.skillFlg == 2) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	////上方向に伸びる攻撃判定（未完）
	//if (g_player.skillFlg == 3) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH <= ex + ew)		// 敵のX座標が、プレイヤーのX座標内だったら真
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// 敵のY座標が、プレイヤーのY座標内だったら真
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	return FALSE;
}

// プレイヤーの剣の部分の判定を抜きに、プレイヤー自身の当たり判定(主にエネミーとの衝突に使う)(当たった:TRUE  当たっていなかった:FALSE)
bool PlayerHitCheck(int ex, int ey, int ew, int eh) {
	if( (g_player.x  <= ex + ew)
	&&	(g_player.x + (PLAYER_WIDTH / 2) >= ex)
	&&	(g_player.y  <= ey + eh)
	&&	(g_player.y + (PLAYER_HEIGHT) >= ey) ){
		
		return TRUE;
	}

	return FALSE;
}

// プレイヤーの初期化処理
void playerInfo::Init() {
	x = 100 * PLAYER_REDUCTION;
	y = GROUND - PLAYER_HEIGHT;
	hp = 3;
	attackFlg = FALSE;
	jumpFlg = FALSE;
	skillFlg = 0;
	skillGage = 100;
	skill_MAX = 3;
	gauge = 265;
	swordFlg = FALSE;
	useSkillFlg = FALSE;
	barrierFlg = FALSE;
	powerUpFlg = FALSE;
	powerUpTime = SKILL5_TIME;
	useSkillGage = 0;
	timecount = 0;
	//skillcustom[0] = 1;
	//skillcustom[1] = 0;
	//skillcustom[2] = 0;
	skillCoolTime[0] = 0;
	skillCoolTime[1] = 0;
	skillCoolTime[2] = 0;
	skillNo = 0;
}
// プレイヤーの初期化処理
void PlayerInit() {
	g_player.Init();
}