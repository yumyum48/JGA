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
#include "Rain.h"
#include <math.h>
/*********************************************

* マクロの宣言

*/////////////////////////////////////////////
#define BOSS_UPMAX		  (183)	// ボスの最大高度のY座標
#define LAST_BOSSDISP_MAX (2)	// 人画面に出てくる蛇の最大数
/*********************************************

* 列挙体の宣言

*/////////////////////////////////////////////

/*********************************************

* 構造体の宣言

*/////////////////////////////////////////////


/*********************************************

* 定数の宣言

*/////////////////////////////////////////////

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////

/*********************************************

* ラスボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage_Last() {
	// ボスの大きさ測るメーター
	static int bw = 0;
	static int bh = 0;
	if (g_keyInfo.nowKey & PAD_INPUT_UP) {
		bh--;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
		bw++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
		bh++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
		bw--;
	}

	DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);

	// ボス本体の表示
	//DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);

	// ボスの本体を除いた7体の表示
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON) {
			DrawBox(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h, 0x00FFFF, TRUE);

		}
	}

	// レイヤー的な意味合いでマップを再描画
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}

	
}

// 動き
void BossMove_Stage_Last() {

	//	0 リュウグウ
	//	1 雑魚変異
	//	3 カエル
	//	4 蜘蛛
	//	5 雲
	//	6 クラゲ
	//	7 分身
	//	8 黒い水

	// 蛇が倒される処理
	Boss_Snake_Knockdown();
}
/*********************************************

* 蛇の出現アニメーション	// ゲームプレイの最上レイヤーで置いてます！

*/////////////////////////////////////////////
void LastBossRightNingAnime() {
	if (g_select_Stage == BOSS_LASTBOSS) {
		static bool startFlg = TRUE;	// 出現アニメーション用のフラグ　TRUE:出現アニメーションをする FALSE:出現アニメーションをしない

		if (startFlg == TRUE) {
			//RainDisp();
			static int trans = 0;	// 雷撃の透明度
			static int cnt = 0;		// アニメーションのカウント
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);	// 透明度をいじる
			DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, true);	// 雷撃
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 透明度を戻す
			if (cnt < 3) {				// ３回雷撃が落ちたら抜ける
				if (trans++ == 50) {	// だんだんと光ってきて
					trans = 230;		// 一気にぴかーんと光らせる
				}
				if (trans >= 240) {		// ぴーかんと光らせて少したったら　
					trans = 0;			// まただんだんと光らせるように初期化
					cnt++;				// 雷撃が落ちた回数を記録
				}
			}
			else if (cnt != 99) {			// でっかい雷撃が落ちていなかったら処理
				trans = 255;			// でっかい雷撃を落とす
				cnt = 99;				// カウントを９９固定に
			}
			if (cnt == 99) {			// カウントが９９固定の時(雷撃を打ち終えた時)
				trans -= 1;				// 透明度を上げていく
				for (int i = 0; i < LAST_BOSSDISP_MAX; i++) {	// ボスの出現フラグをオンへ
					g_boss_Yamatano[i].popflg = LASTBOSS_ON;
				}
				if (trans <= 0) {
					startFlg = FALSE;	// ボスがよく見えるようになったらアニメーション終了

				}
			}
		}
		else {
			/*	if (g_boss[BOSS_LASTBOSS].hp <= 0) {	// 出現アニメーション初期化
					startFlg = TRUE;
				}*/
		}
	}
}
/*********************************************

* 蛇が倒される処理

*/////////////////////////////////////////////
void Boss_Snake_Knockdown() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON) {
			if (g_boss_Yamatano[i].damageFlg == TRUE) {
				// 被弾モーション終わったらフラグをFALSE
				g_boss_Yamatano[i].damageFlg = FALSE;
			}
			else if (g_boss_Yamatano[i].hp <= 0) {		// hpが０だった場合、ボスの首を落として次に入れ替える準備をする
				if (g_boss_Yamatano[i].y < GROUND) {
					static int cnt;					// 揺らしで使うフレーム用カウント
					int moveX = 2;					// ボスのX軸揺らし用
					int moveY = 5;					// ボスの首の落下速度
					if (cnt++ > 5 && cnt <= 10) {
						moveX = -2;
					}
					else if (cnt > 10) {
						cnt = 0;
					}

					g_boss_Yamatano[i].y += moveY;			// 下に落ちていく
					g_boss_Yamatano[i].x += moveX;	// 左右に揺れながら
				}
				else {
					g_boss_Yamatano[i].popflg = LASTBOSS_KILL;		// 落下しきったボスのフラグをオフへ
				}
			}
		}
	}
}
void lasbossInfo::lasbossInit(int num) {// ラスボスの本体以外(7体の初期化)
		hp = 1;				  // Hpの初期化
		attackFlg = 0;		  // なんの攻撃をしているかのフラグ
		popflg = LASTBOOS_OFF;       // 画面にいるかいないか、とどめを刺せるかどうかのフラグ
		coolTime = 0;		  // 硬直時間
		damageFlg = FALSE;	  // ダメージを食らっているかどうかのフラグ
		switch (num)
		{
		case 0:
			x = 998;		// X座標の初期位置
			y = 183;		// Y座標の初期位置
			//y = 0;			// Y座標の初期位置
			w = 230;		// 幅の初期位置
			h = 490;		// 高さの初期位置
			//popflg = TRUE;	// 出現フラグをオン
			break;			// ブレイク
		case 1:
			x = 718;		// X座標の初期位置
			y = 183;		// Y座標の初期位置
			//y = 0;			// Y座標の初期位置
			w = 230;		// 幅の初期位置
			h = 490;		// 高さの初期位置
			//popflg = TRUE;	// 出現フラグをオン
			break;			// ブレイク
		case 2:
			x = 438;		// X座標の初期位置
			y = 183;		// Y座標の初期位置
			//y = 0;			// Y座標の初期位置
			w = 230;		// 幅の初期位置
			h = 490;		// 高さの初期位置
			//popflg = TRUE;	// 出現フラグをオン
			break;			// ブレイク
		default:

			break;
		}
	
}
// ラスボスの初期化
void LastBossInit() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		g_boss_Yamatano[i].lasbossInit(i);
	}
}