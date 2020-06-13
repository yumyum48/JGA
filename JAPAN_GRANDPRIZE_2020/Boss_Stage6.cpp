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

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
/*********************************************

* ステージ６のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage6() {
	const int animations[4] = { 0, 7, 8, 15 };	// アニメーションの始点と終点
	static int anime = 0;							// プレイヤーの画像を変える
	static int time = 0;							// 画像を切り替えるタイミング調整
	static int animeStart = animations[0];			// アニメーションの開始位置
	static int animeLast = animations[1];			// アニメーションの終了位置（ループ位置
	static int shadowNoDispCnt = 0;					// 影を表示していない時間
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

	// アニメーションの進行
	if (++time % 4 == 0) anime++;
	if (anime > animeLast)anime = animeStart;

	// 間をおいてボスを表示
	if (g_boss_shadow.shadowDispFlg == FALSE
		&& ++shadowNoDispCnt > 60) {
		g_boss_shadow.shadowDispFlg = TRUE;
		shadowNoDispCnt = 0;
	}

#ifdef DEBUG_MODE_ON
	// 影の射程
	DrawBox(g_boss_shadow.x - g_boss_shadow.w / 2, g_boss_shadow.y + 70 + 40, g_boss_shadow.x, g_boss_shadow.y + g_boss_shadow.h + 70, 0x0000FF, FALSE);
	// 影の当たり判定
	DrawBox(g_boss_shadow.x, g_boss_shadow.y + 70 + 40, g_boss_shadow.x + g_boss_shadow.w, g_boss_shadow.y + g_boss_shadow.h + 0, 0xFFFFFF, TRUE);
	if (g_boss_shadow.shadowDispFlg == TRUE) {
		// 影の表示
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[0], TRUE, TRUE, FALSE);
	}
#endif // DEBUG_MODE_ON


#ifdef DEBUG_MODE_ON
	// ボスの当たり判定
	//DrawBox(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, g_boss[BOSS_STAGE6].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE6].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y + 70, g_boss[BOSS_STAGE6].x + PLAYER_WIDTH, GROUND, 0xFF0000, FALSE);
#endif // DEBUG_MODE_ON
	// ボスの表示
	DrawRotaGraph2(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[anime], TRUE, FALSE);


	// 攻撃表示
	if (g_boss[BOSS_STAGE6].attackFlg != 0) {						// ボスが攻撃していれば
		BossAttackDisp();	// ボスの攻撃
	}

}

// 動き
void BossMove_Stage6() {
	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	static int attackSelect = 0;							// ボスの攻撃選択
	//static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// １フレーム前のボスのattackフラグを記憶する

	if ((coolTime++ > 60)												// 硬直時間
		&& (g_boss[BOSS_STAGE6].attackFlg == 0)							// ボスが攻撃していなければ
		&& (moveFlg == BOSSMOVE_NOMOTION)) {							// ボスが移動していなけれ
		attackSelect = InputRand(0, 0, BOSSATTACK_LONG_RANGE);//乱数で攻撃するか移動をするかを決定


		if (attackSelect != 0) {
			g_boss[BOSS_STAGE6].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;												// クールタイム初期化
		}
		else {	// 攻撃をしないとき 

		}
	}
	//// 攻撃無しで行動
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	//	BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	//}

	// 攻撃
	if (g_boss[BOSS_STAGE6].attackFlg != 0) {						// ボスが攻撃していれば

		BossAttackMove();	// ボスの攻撃
	}

	
	Boss_Knock_Down();	// ボスが倒されてる処理

}

// ボスの初期化
void Boss6_Init() {

	g_boss_shadow.ShadowInit(g_boss[BOSS_STAGE6].x);	// 影本体の初期化
	g_boss_shadow.LongRangeInit(g_boss[BOSS_STAGE6].x);	// 遠距離攻撃の初期化
}