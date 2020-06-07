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
#include "Trap.h"
#include "HP.h"

#include <math.h>
/*********************************************

* 定数の宣言

*/////////////////////////////////////////////
const int KURAGE_MAX = 4;	// 出現するクラゲの最大数
/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////

/*********************************************

* ステージ５のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage5() {
	//// ボスの大きさ測るメーター
	//static int bw = 0;
	//static int bh = 0;
	//if (g_keyInfo.nowKey & PAD_INPUT_UP) {
	//	bh--;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
	//	bw++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
	//	bh++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
	//	bw--;
	//}

	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);


	DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// ボスが攻撃していれば
	//	BossAttackDisp();	// ボスの攻撃
	//}
	Boss_MiniKurage_Drop_Disp();
}

// 動き
void BossMove_Stage5() {
	static int coolTime = 0;								// 硬直時間
	//static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	//static int attackSelect = 0;							// ボスの攻撃選択
	//static int attackFlgBuf = g_boss[BOSS_STAGE5].attackFlg;// １フレーム前のボスのattackフラグを記憶する



	if (coolTime++ > 600) {		// 硬直時間
		g_boss[BOSS_STAGE5].attackFlg = InputRand(BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND);
	}

	Boss_MiniKurage_DropFlg();
	Boss_MiniKurage_Drop_Move();

	if (BossNoAttackCheck(g_boss[BOSS_STAGE5].attackFlg) == TRUE) {
		coolTime = 480;
	}
	//	&& (g_boss[BOSS_STAGE5].attackFlg == 0)							// ボスが攻撃していなければ
	//	&& (moveFlg == BOSSMOVE_NOMOTION)) {							// ボスが移動していなければ


	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// ボスが攻撃しないときに召喚する雑魚敵の初期化
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}

	//	attackSelect = InputRand(0, 0, 0);			//乱数で攻撃するか移動をするかを決定

	//	if (attackSelect != 0) {
	//		g_boss[BOSS_STAGE5].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
	//		coolTime = 0;												// クールタイム初期化
	//	}
	//	else {	// 攻撃をしないとき
	//		

	//	}
	//}
	////// トラップを生成する時にトラップを初期化
	////if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
	////	g_trap.WaveInit(g_boss[BOSS_STAGE5].x);
	////}
	//// バッファーと比べて雑魚敵生成してないときは雑魚敵を初期化

	//// バッファーと比べて雑魚敵生成する時雑魚敵を初期化
	//if (BossDropAttackCheck(g_boss[BOSS_STAGE5].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// 攻撃無しで行動
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	//	BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	//}

	//// 攻撃
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// ボスが攻撃していれば

	//	BossAttackMove();	// ボスの攻撃
	//}

	//Poison_Trap_Move();	// 毒のトラップの動き
	//if (g_boss4_Rightning_Cnt >= 1800) {		// カウントを１の差でDispの部分を制御
	//	g_boss4_Rightning_Cnt = 1799;
	//}

	
	Boss_Knock_Down();	// ボスが倒されてる処理
}

/*********************************************

* ミニクラゲがいなかったらフラグをオンにしてクラゲを補充

*/////////////////////////////////////////////
void Boss_MiniKurage_DropFlg() {
	//static int coolTime = 0;
	//static int enemyDropCnt = 0;
	//static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // 
	//static int enemy_cnt = 0;	// 出現したエネミーの要素番号

	int cnt = 0;	// 使われたミニクラゲの数を数える
	for (int i = 0; i < KURAGE_MAX; i++) {
		if(g_enemy[i].kurage.flg == FALSE) {	// ４体のミニクラゲが全ていなくなったかどうかチェック
			cnt++;
		}
	
	}
	if (cnt >= KURAGE_MAX) {					// ４体のミニクラゲが全ていなくなっていたらミニクラゲを補充 // 本当はボスがタックルしたあとに補充
		for (int i = 0; i < KURAGE_MAX; i++) {
			g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
			g_enemy[i].kurage.flg = TRUE;
		}
	}

}

void Boss_MiniKurage_Drop_Disp() {
	
	// 雑魚敵の描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		
			const int animation_Max = 3;
			static int time = 0;

			// アニメーションのカウント
			if (time++ % 8 == 0) {
				g_enemy[i].kurage.anime++;

			}

			// アニメーションの初期化
			if (g_enemy[i].kurage.anime > animation_Max)g_enemy[i].kurage.anime = 0;

			if (g_enemy[i].kurage.flg == TRUE) {
				// 雑魚敵の描画
				DrawRotaGraph2(g_enemy[i].kurage.x, g_enemy[i].kurage.y,
					0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].kurage.anime], TRUE);
			}
	}
	// 敵の蒸発アニメーション
	EnemyEvaporation();
}

void Boss_MiniKurage_Drop_Move() {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// ミニクラゲの配置される位置

	// 表示されていて、初期ポジションにいない雑魚敵を初期ポジに移動させる
	for (int i = 0; i < KURAGE_MAX; i++) {
		if (g_enemy[i].kurage.flg == TRUE) {
			//g_enemy[buf].kurage.x = position[buf].x;
			//g_enemy[buf].kurage.y = position[buf].y;
			float angle;
			angle =  atan2( (g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x) );
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);

			
		}
	}


	static bool ataackFlg_AirKurage = FALSE;	// 空中で飛んでくるクラゲの攻撃フラグ
	static bool attackFlg_GroundKurage = FALSE;	// 地上で飛んでくるクラゲの攻撃フラグ
	static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// クラゲが攻撃で使われていないか TRUE:使われている FALSE:使われていない
	static int attackKurageBuf_Air;											// 攻撃で使われていなクラゲの要素番号を記憶させる(空中攻撃用)
	static int attackKurageBuf_Ground;											// 攻撃で使われていなクラゲの要素番号を記憶させる(地上攻撃用)

	// ボスがミニクラゲで攻撃すると判断した(地上で)
	if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)
	&&  (ataackFlg_AirKurage != TRUE) ){	// 空中での攻撃をしてない時
	
		for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// ミニクラゲが攻撃を行えるかチェック
			if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
				ataackFlg_AirKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
				attackKurageCheck[attackKurageBuf_Air] == TRUE;										// 攻撃中のフラグをオンにする
				break;																				//使えるクラゲの要素番号を吐き出す
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_AIR){
	//	ataackFlg_AirKurage = FALSE;
	//}

	// ボスがミニクラゲで攻撃すると判断した(空中で)
	if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)
	&&  (attackFlg_GroundKurage != TRUE) ){	// 地上での攻撃をしてない時
		for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// ミニクラゲが攻撃を行えるかチェック
			if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
				attackFlg_GroundKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
				attackKurageCheck[attackKurageBuf_Ground] == TRUE;										// 攻撃中のフラグをオンにする
				break;																				//使えるクラゲの要素番号を吐き出す
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
	//	attackFlg_GroundKurage = FALSE;
	//}

	// 空中でミニクラゲが攻撃をする
	if (ataackFlg_AirKurage) {
		BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
	}

	if (attackFlg_GroundKurage) {
		BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
	}

	// ミニクラゲとの当たり判定
	KurageHit();	// ヒットするとプレイヤーのHp減少
}

// ミニクラゲの空中攻撃
void BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage) {

	
	if (g_enemy[attackKurageBuf_Air].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Air].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
		g_boss[g_select_Stage].attackFlg = 0;
		*ataackFlg_AirKurage = 0;
	}
	else {
		if (g_enemy[attackKurageBuf_Air].kurage.y > (GROUND - ENEMY_HEIGHT) - 200) {
			g_enemy[attackKurageBuf_Air].kurage.y -= 5;
		}
		else {
			g_enemy[attackKurageBuf_Air].kurage.y = (GROUND - ENEMY_HEIGHT) - 200;
			g_enemy[attackKurageBuf_Air].kurage.x -= 10;
		}
	}
}
// ミニクラゲの地上攻撃
void BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage) {

	if (g_enemy[attackKurageBuf_Ground].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Ground].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
		g_boss[attackKurageBuf_Ground].attackFlg = 0;
		*attackFlg_GroundKurage = 0;
	}
	else {
		if (g_enemy[attackKurageBuf_Ground].kurage.y < GROUND - ENEMY_HEIGHT) {
			g_enemy[attackKurageBuf_Ground].kurage.y += 2;
		}
		else {
			g_enemy[attackKurageBuf_Ground].kurage.y = GROUND - ENEMY_HEIGHT;
			g_enemy[attackKurageBuf_Ground].kurage.x -= 10;
		}
		
		

	}
}

void KurageHit() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if( (g_enemy[i].kurage.flg == TRUE)
		&&  (g_noDamageCnt > 60) ){		//地上の敵の当たり判定
			if (PlayerHitCheck(g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {
				
				if (g_player.barrierFlg == FALSE) --g_player.hp;
				else g_player.barrierFlg = FALSE;
				g_noDamageCnt = 0;		// 無敵時間発動
			}
		}
	}
}