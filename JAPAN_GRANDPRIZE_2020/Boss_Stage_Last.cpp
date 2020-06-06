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
#define LAST_BOSSDISP_MAX (2)	// １画面に出てくる蛇の最大数
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
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON || g_boss_Yamatano[i].popflg == LASTBOSS_MINION) {
			DrawBox(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h, 0x00FFFF, TRUE);

		}
	}

	// レイヤー的な意味合いでマップを再描画
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}

	DrawFormatString(300, 500, 0xFF00000, "flg = %d", g_boss_Yamatano[2].popflg);
	DrawFormatString(300, 500, 0xFF00000, "\nflg = %d", g_boss_Yamatano[3].popflg);
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

	for (int i = 0; i < YAMATANO_NECK; i++) {	// 蛇追加シーン
		if(g_boss_Yamatano[i].attackFlg == 0)	// 何もしていなかったら
			if (g_boss_Yamatano[i].popflg == LASTBOSS_MINION) {
				static bool upFlg[YAMATANO_NECK] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};	// 上に上がるフラグ
				int moveX = 2;					// ボスのX軸揺らし用
				int moveY = 8;					// ボスの首の落下速度
				/*if (cnt++ > 5 && cnt <= 10) {
					moveX = -2;
				}
				else if (cnt > 10) {
					cnt = 0;
				}*/
				if( (g_boss_Yamatano[i].y > (BOSS_UPMAX - 50)) 
				&&  (upFlg[i] == TRUE) ){
					g_boss_Yamatano[i].y -= moveY;			// 上に上がっていく
				}
				else if (g_boss_Yamatano[i].y <= (BOSS_UPMAX - 50)) {
					upFlg[i] = FALSE;
				}
				if ((g_boss_Yamatano[i].y <  BOSS_UPMAX )
					&& (upFlg[i] == FALSE)) {
					g_boss_Yamatano[i].y += moveY / 2;			// 下に下がっていく(ゆっくり)

				}
				else if( (upFlg[i] == FALSE )					// 所定の位置まで来たら
				&&		 (g_boss_Yamatano[i].y >= BOSS_UPMAX) ){
					
					for (int i = 0; i < YAMATANO_NECK; i++) {	// アップフラグを初期化して
						upFlg[i] = TRUE;
					}
					g_boss_Yamatano[i].popflg = LASTBOSS_ON;	// 出現フラグをステンバイ状態へ

				}
			}

	}

	// 7体の蛇出現フラグを管理
	Last_Boss_SnakeDispFlg_Managar();
	

	// 蛇が倒される処理
	Boss_Snake_Knockdown();
}
/*********************************************

* 蛇の出現フラグ管理

*/////////////////////////////////////////////
void Last_Boss_SnakeDispFlg_Managar() {
	if (g_lastBoss_StartAnimeFlg != TRUE) {
		int cnt = 0;		// 表示されているボスのカウント
		int killCnt = 0;	// 倒されているボスのカウント
		int offCnt = 0;	// 表示されていないボスのカウント
		int tagBuf = 0;			// 表示されている蛇のタグを確認
		for (int i = 0; i < YAMATANO_NECK; i++) {
			if( (g_boss_Yamatano[i].popflg == LASTBOSS_ON) 
			|| (g_boss_Yamatano[i].popflg == LASTBOSS_MINION) ){
				cnt++;			// 表示されているボスのカウント
				tagBuf = g_boss_Yamatano[i].tag;	// タグを記憶
			}
			if (g_boss_Yamatano[i].popflg == LASTBOSS_KILL) {
				killCnt++;		// 倒されたボスのカウント
			}
			// 表示されていないボスのカウント
			offCnt = YAMATANO_NECK - (cnt + killCnt);
		}

		if (cnt < 2) {
			int disp = LAST_BOSSDISP_MAX - cnt;	// 出現させる蛇の数を計算

			for (int i = 0; i < disp; i++) {
				int next = YAMATANO_NECK - offCnt;	// 次のボスの添え字

				if (disp == 1) {
					if (tagBuf == TAG_BOSS_LEFT) {
						g_boss_Yamatano[next].lasbossInit(2);	// 左側に設置
					}
					else {
						g_boss_Yamatano[next].lasbossInit(3);	// 右側に設置
					}
					g_boss_Yamatano[next].popflg = LASTBOSS_MINION;
				}
				else if (disp == 2) {

					g_boss_Yamatano[next].lasbossInit(i + 2);	// 左右に設置 2は、添え字合わせ(Y座標を地面と同じ座標に初期化するので)
					g_boss_Yamatano[next].popflg = LASTBOSS_MINION;
				}
				offCnt--;

			}

			// ７体の蛇が倒されていたらラスボスを召喚
			if (killCnt >= YAMATANO_NECK) {
				g_boss[BOSS_LASTBOSS].popflg = TRUE;
			}

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
/*********************************************

* 蛇の出現アニメーション	// ゲームプレイの最上レイヤーで置いてます！

*/////////////////////////////////////////////
void LastBossRightNingAnime() {
	if (g_select_Stage == BOSS_LASTBOSS) {

		if (g_lastBoss_StartAnimeFlg == TRUE) {
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
					g_lastBoss_StartAnimeFlg = FALSE;	// ボスがよく見えるようになったらアニメーション終了

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
			x = 998;				// X座標の初期位置
			y = 183;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			w = 230;				// 幅の初期位置
			h = 490;				// 高さの初期位置
			tag = TAG_BOSS_RIGHT;	// 左にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		case 1:
			x = 718;				// X座標の初期位置
			y = 183;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			w = 230;				// 幅の初期位置
			h = 490;				// 高さの初期位置
			tag = TAG_BOSS_LEFT;	// 右にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		case 2:
			x = 998;				// X座標の初期位置
			y = GROUND;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			w = 230;				// 幅の初期位置
			h = 490;				// 高さの初期位置
			tag = TAG_BOSS_RIGHT;	// 左にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		case 3:
			x = 718;				// X座標の初期位置
			y = GROUND;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			w = 230;				// 幅の初期位置
			h = 490;				// 高さの初期位置
			tag = TAG_BOSS_LEFT;	// 右にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		//case 2:
		//	x = 438;				// X座標の初期位置
		//	y = 183;				// Y座標の初期位置
		//	//y = 0;				// Y座標の初期位置
		//	w = 230;				// 幅の初期位置
		//	h = 490;				// 高さの初期位置
		//	//popflg = TRUE;		// 出現フラグをオン
		//	break;					// ブレイク
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