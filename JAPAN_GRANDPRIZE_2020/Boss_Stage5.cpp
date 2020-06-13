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
struct barrier : public picInfo {
	bool flg;	// 出現フラグ
	int cnt;	// 出現カウント

	// barriarを初期化するメソッド
	void barrierInit() {
		x = 654;	// X座標の初期位置
		y = g_boss[g_select_Stage].y + 10;	// Y座標の初期位置

		flg = FALSE;	// 出現フラグを初期化	
		cnt = 0;		// 出現カウントを初期化
	}
};
//
barrier g_barrier;		// バリアの情報
/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
/*********************************************

* ステージ５のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage5() {
	// 0,3:ボスのニュートラルモーションの最初と最後	4,7:ボスの攻撃モーションの最初と最後	8,9:ボスの攻撃予備動作の最初と最後
	const int bossAnime[6] = { 0, 3, 4, 7, 8, 9 };
	static int animationStart = bossAnime[0];	// アニメーション開始位置の初期化
	static int animationLast = bossAnime[1];	// アニメーションループの初期化
	static int animecnt = 0;					// アニメーションをする為のカウント

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

	if (g_boss[g_select_Stage].attackFlg != BOSSATTACK_TACKLE) {
		if (animecnt++ % 10 == 0)g_boss5_Ex.anime++;					// アニメーションの進行
		if (g_boss5_Ex.anime > animationLast)g_boss5_Ex.anime = animationStart;	// アニメーションのループ
	}


	// ボスの表示
	//DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	DrawRotaGraph2(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, 0, 0, 1.0f, 0, g_pic.boss_5_1[g_boss5_Ex.anime], TRUE, FALSE);

	if (g_barrier.cnt++ >= 300 && g_barrier.flg == TRUE) {
		// シールド
		DrawGraph(g_barrier.x, g_barrier.y, g_pic.boss6_sield, TRUE);
		//DrawBox(g_barrier.x, g_barrier.y, g_barrier.x + 30, g_barrier.y + BOSS_STAGE5_HEIGHT, 0x000000, TRUE);
	}

	// ミニクラゲの表示
	Boss_MiniKurage_Drop_Disp();

	// 攻撃表示
	if (g_boss[BOSS_STAGE5].attackFlg == BOSSATTACK_TACKLE) {						// ボスが攻撃していれば
		BossAttackDisp();	// ボスの攻撃
	}
}

// 動き
void BossMove_Stage5() {
	//static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	//static int attackSelect = 0;							// ボスの攻撃選択
	//static int attackFlgBuf = g_boss[BOSS_STAGE5].attackFlg;// １フレーム前のボスのattackフラグを記憶する


	Boss_MiniKurage_DropFlg();		// ミニクラゲを出すフラグ管理
	Boss_MiniKurage_Drop_Move();	// ミニクラゲの動きや攻撃


	if (g_boss[BOSS_STAGE5].coolTime++ > 600 && g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {		// 硬直時間
		g_boss[BOSS_STAGE5].attackFlg = InputRand(BOSSATTACK_MINIKURAGE_AIR, BOSSATTACK_MINIKURAGE_AIR, BOSSATTACK_MINIKURAGE_AIR);
	}
	else if (g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {
		g_boss[BOSS_STAGE5].attackFlg = 0;
	}

	// 攻撃
	if (g_boss[BOSS_STAGE5].attackFlg == BOSSATTACK_TACKLE) {						// ボスが攻撃していれば

		BossAttackMove();	// ボスの攻撃
	}

	if (g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {
		g_barrier.flg = TRUE;
		if (BossDamageCheck(g_boss[BOSS_STAGE5].hp) == TRUE && g_barrier.cnt >= 300) {
			g_boss[BOSS_STAGE5].hp++;
			g_barrier.cnt = 0;
		}
	}
	else {
		g_barrier.flg = FALSE;
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
		if (g_enemy[i].kurage.flg == FALSE) {	// ４体のミニクラゲが全ていなくなったかどうかチェック
			cnt++;
		}

	}
	if (cnt >= KURAGE_MAX) {


		if (g_boss[g_select_Stage].attackFlg != BOSSATTACK_TACKLE) {	// タックルが終わったらミニクラゲを補充
			for (int i = 0; i < KURAGE_MAX; i++) {
				g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
				g_enemy[i].kurage.flg = TRUE;
				g_boss[BOSS_STAGE5].coolTime = 0;
			}
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
	/*for (int i = 0; i < KURAGE_MAX; i++) {
		DrawBox(g_enemy[i].kurage.x, g_enemy[i].kurage.y, g_enemy[i].kurage.x + ENEMY_WIDTH, g_enemy[i].kurage.y + ENEMY_HEIGHT, 0x00FF00, TRUE);
	}*/
}

void Boss_MiniKurage_Drop_Move() {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// ミニクラゲの配置される位置
	static bool ataackFlg_AirKurage = FALSE;									// 空中で飛んでくるクラゲの攻撃フラグ TRUE:攻撃する FALSE:攻撃しない
	static bool attackFlg_GroundKurage = FALSE;									// 地上で飛んでくるクラゲの攻撃フラグ TRUE:攻撃する FALSE:攻撃しない
	// 表示されていて、初期ポジションにいない雑魚敵を初期ポジに移動させる
	for (int i = 0; i < KURAGE_MAX; i++) {
		if ((g_enemy[i].kurage.flg == TRUE)			// 敵の出現フラグがオンの時
			&& (ataackFlg_AirKurage == FALSE)			// クラゲが攻撃していないとき
			&& (attackFlg_GroundKurage == FALSE)) {

			float angle;
			angle = atan2((g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x));
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);


		}
	}


	int cnt = 0;			// クラゲの配列を制御する用のカウント(攻撃したあとのクラゲは初期化するのでその次のクラゲをセットする処理をするため)
	static int cntBuf_Air;		// 空中クラゲに決定された要素番号を格納する
	static int cntBuf_Ground;	// 地上クラゲに決定された要素番号を格納する


	for (cnt = 0; cnt < KURAGE_MAX; cnt++) {	// 出現している配列番号が小さい順で添え字をbreakして渡す
		if (g_enemy[cnt].kurage.flg == TRUE)
			break;
	}
	if ((g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)	// ミニクラゲが空中攻撃をする時
		&& (ataackFlg_AirKurage != TRUE)) {	// 空中での攻撃をしてない時
		ataackFlg_AirKurage = TRUE;		// 空中クラゲの攻撃フラグをオンに
		cntBuf_Air = cnt;				// 配列の要素番号を格納してカウントにプラス１をする
	}

	for (cnt = 0; cnt < KURAGE_MAX; cnt++) {	// 出現している配列番号が小さい順で添え字をbreakして渡す
		if (g_enemy[cnt].kurage.flg == TRUE)
			break;
	}
	if ((g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)	// ミニクラゲが地上で攻撃をする時
		&& (attackFlg_GroundKurage != TRUE)) {	// 地上での攻撃をしてない時
		attackFlg_GroundKurage = TRUE;			// 地上クラゲの攻撃フラグをオンに
		cntBuf_Ground = cnt;					// 配列の要素番号を格納してカウントにプラス１をする
	}


	static int flgcnt = 0;
	if (ataackFlg_AirKurage == TRUE && cntBuf_Air < KURAGE_MAX) {
		BossMiniKurage_Attack_Air(cntBuf_Air, &ataackFlg_AirKurage);
		if (ataackFlg_AirKurage == FALSE) {
			flgcnt++;
		}

	}

	if (attackFlg_GroundKurage == TRUE && cntBuf_Ground < KURAGE_MAX) {
		BossMiniKurage_Attack_Ground(cntBuf_Ground, &attackFlg_GroundKurage);
		if (attackFlg_GroundKurage == FALSE) {
			flgcnt++;
		}
	}

	if (flgcnt >= 4) {
		g_boss[g_select_Stage].attackFlg = BOSSATTACK_TACKLE;	// ４体のクラゲがいなくなっていたらボス本体がタックル実行
	}
	if (g_boss[g_select_Stage].attackFlg == BOSSATTACK_TACKLE) {
		flgcnt = 0;
	}

	/*
		//static bool ataackFlg_AirKurage = FALSE;									// 空中で飛んでくるクラゲの攻撃フラグ
		//static bool attackFlg_GroundKurage = FALSE;									// 地上で飛んでくるクラゲの攻撃フラグ
		//static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// クラゲが攻撃で使われていないか TRUE:使われている FALSE:使われていない
		//static int attackKurageBuf_Air;												// 攻撃で使われていなクラゲの要素番号を記憶させる(空中攻撃用)
		//static int attackKurageBuf_Ground;											// 攻撃で使われていなクラゲの要素番号を記憶させる(地上攻撃用)

		//// ボスがミニクラゲで攻撃すると判断した(地上で)
		//if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)
		//&&  (ataackFlg_AirKurage != TRUE) ){	// 空中での攻撃をしてない時
		//
		//	for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// ミニクラゲが攻撃を行えるかチェック
		//		if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
		//			ataackFlg_AirKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
		//			attackKurageCheck[attackKurageBuf_Air] = TRUE;										// 攻撃中のフラグをオンにする
		//			break;																				//使えるクラゲの要素番号を吐き出す
		//		}
		//	}
		//}
		////else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_AIR){
		////	ataackFlg_AirKurage = FALSE;
		////}

		//// ボスがミニクラゲで攻撃すると判断した(空中で)
		//if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)
		//&&  (attackFlg_GroundKurage != TRUE) ){	// 地上での攻撃をしてない時
		//	for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// ミニクラゲが攻撃を行えるかチェック
		//		if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
		//			attackFlg_GroundKurage = TRUE;														// 攻撃が行えるならフラグをオンにする
		//			attackKurageCheck[attackKurageBuf_Ground] = TRUE;									// 攻撃中のフラグをオンにする
		//			break;																				//使えるクラゲの要素番号を吐き出す
		//		}
		//	}
		//}
		////else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
		////	attackFlg_GroundKurage = FALSE;
		////}
		//static int attackCnt = 0;	// 攻撃が終了した回数を数える

		//// 空中でミニクラゲが攻撃をする
		//if (ataackFlg_AirKurage) {
		//	BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
		//	if (ataackFlg_AirKurage == FALSE) {
		//		attackCnt++;
		//	}
		//}

		//if (attackFlg_GroundKurage) {
		//	BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
		//	if (attackFlg_GroundKurage == FALSE) {
		//		attackCnt++;
		//	}
		//}

		//if (attackCnt >= 4) {	// 四回攻撃をしていたら、クラゲアタックチェックが全部オンになっているので初期化
		//	for (int i = 0; i < KURAGE_MAX; i++) {
		//		attackKurageCheck[i] = FALSE;
		//	}
		//}
		//

	*/
	// ミニクラゲとの当たり判定
	KurageHit();	// ヒットするとプレイヤーのHp減少
}

// ミニクラゲの空中攻撃
void BossMiniKurage_Attack_Air(int cntBuf_Air, bool* ataackFlg_AirKurage) {
	int moveY = 5, moveX = 16;

	if (g_enemy[cntBuf_Air].kurage.x <= 0) {
		g_enemy[cntBuf_Air].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);	// ミニクラゲの初期化
		//g_boss[g_select_Stage].attackFlg = 0;										// ボスの攻撃フラグをオフに
		g_boss[g_select_Stage].coolTime = 500;										// ボスのクールタイム初期化
		*ataackFlg_AirKurage = FALSE;												// ボスの攻撃フラグバッファーを初期化
	}
	else {
		if (g_enemy[cntBuf_Air].kurage.y < (GROUND - ENEMY_HEIGHT) - 200) {
			g_enemy[cntBuf_Air].kurage.y += moveY;
		}
		else {
			g_enemy[cntBuf_Air].kurage.y = (GROUND - ENEMY_HEIGHT) - 200;
			g_enemy[cntBuf_Air].kurage.x -= moveX;
		}
	}
}
// ミニクラゲの地上攻撃
void BossMiniKurage_Attack_Ground(int cntBuf_Ground, bool* attackFlg_GroundKurage) {
	int moveY = 5, moveX = 16;
	if (g_enemy[cntBuf_Ground].kurage.x <= 0) {
		g_enemy[cntBuf_Ground].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);// ミニクラゲの初期化
		//g_boss[g_select_Stage].attackFlg = 0;										// ボスの攻撃フラグをオフに
		g_boss[cntBuf_Ground].coolTime = 500;										// ボスのクールタイム初期化
		*attackFlg_GroundKurage = FALSE;											// ボスの攻撃フラグバッファーを初期化
	}
	else {
		if (g_enemy[cntBuf_Ground].kurage.y < GROUND - ENEMY_HEIGHT) {
			g_enemy[cntBuf_Ground].kurage.y += moveY;
		}
		else {
			g_enemy[cntBuf_Ground].kurage.y = GROUND - ENEMY_HEIGHT;
			g_enemy[cntBuf_Ground].kurage.x -= moveX;
		}
	}
}

void KurageHit() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if ((g_enemy[i].kurage.flg == TRUE)
			&& (g_noDamageCnt > 60)) {		//地上の敵の当たり判定
			if (PlayerHitCheck(g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {

				if (g_player.barrierFlg == FALSE) --g_player.hp;
				else g_player.barrierFlg = FALSE;
				g_noDamageCnt = 0;		// 無敵時間発動
			}
		}
	}
}

void Boss5_Init() {

	g_barrier.barrierInit();
	g_boss5_Ex.AnimtionInit();
}