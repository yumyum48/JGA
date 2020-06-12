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
#include "Skill.h"

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

//bool g_lastBoss_SevenSnakeAttackFlg[YAMATANO_NECK];	// ラスボス前の７体の蛇の攻撃フラグ TRUE: 攻撃中 FALSE:攻撃していない
/*********************************************

* ラスボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage_Last() {
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

	// ボス本体の表示
	//DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);

	// ボスの本体を除いた7体の表示
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg != LASTBOOS_OFF && g_boss_Yamatano[i].popflg != LASTBOSS_KILL) {
			DrawBox(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h, 0x00FFFF, TRUE);

		}
	}

	// ラスボス本体の描画
	if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGELAST_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGELAST_HEIGHT, 0x00FFFF, TRUE);
	}
	// レイヤー的な意味合いでマップを再描画
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}

	// ラスボスの本体がいなかったら
	if (g_boss[BOSS_LASTBOSS].popflg == FALSE) {
		YmatanoSeven_Disp();
	}
	// ラスボスの本体がいたら
	else if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		LastBoss_Disp();
	}
																											
	DrawFormatString(300, 500, 0xFF00000, "coolTime = %d\nattackFlg = %d", g_boss[BOSS_LASTBOSS].coolTime, g_boss[BOSS_LASTBOSS].attackFlg);
}

// 動き
void BossMove_Stage_Last() {	

	// ボスがいなかったら
	if (g_boss[BOSS_LASTBOSS].popflg == FALSE) {
		YmatanoSeven_Move();
	}
	// ボスがいたら
	else if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		LastBoss_Move();
	}

}
/*********************************************

* ヤマタノオロチ本体

*/////////////////////////////////////////////
// 表示 // レイヤーの関係で攻撃のみ
void LastBoss_Disp() {
	if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {
		Last_Boss_Attack_Disp[g_boss[BOSS_LASTBOSS].attackFlg](g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, &g_boss[BOSS_LASTBOSS].attackFlg, &g_boss[BOSS_LASTBOSS].coolTime);	// ラスボス前蛇の攻撃}
	}
}

// 動き
void LastBoss_Move() {

	if ((g_boss[BOSS_LASTBOSS].coolTime++ > 120)									// 硬直時間
		&& (g_boss[BOSS_LASTBOSS].attackFlg == 0)) {								// ボスが攻撃していない

		g_boss[BOSS_LASTBOSS].attackFlg = 1 + InputHyperRand(LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_SHADOW);							//乱数で攻撃するか移動をするかを決定　+ １は０を使わないため
	

		if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {	// ボスの攻撃 添え字のー１は添え字合わせ
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_ENEMY_DROP + 1) {		// 歩く雑魚敵を召喚する時、情報を初期化
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].walk.BossArea_WlakInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}

			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINISPIDER_DROP + 1) {	// ミニスパイダーを召喚する際、情報を初期化
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].spider.BossArea_SpiderInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINICLOUD_DROP + 1) {	// ミニスパイダーを召喚する際、情報を初期化
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].cloud.BossArea_CloudInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINIKURAGE + 1) {	// ミニクラゲを召喚する際、情報を初期化
				for (int i = 0; i < KURAGE_MAX; i++) {
					g_enemy[i].kurage.BossArea_KurageInit(g_boss[BOSS_LASTBOSS].y);
					g_enemy[i].kurage.flg = TRUE;
				}
			}
		}
		
	}
	// 攻撃
	if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {
		Last_Boss_Attack_Move[g_boss[BOSS_LASTBOSS].attackFlg](g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, &g_boss[BOSS_LASTBOSS].attackFlg, &g_boss[BOSS_LASTBOSS].coolTime);	// ラスボス前蛇の攻撃}

	}

}
/*********************************************

* ヤマタノオロチ本体以外の7体

*/////////////////////////////////////////////
// 表示 // レイヤーの関係で攻撃の表示のみ
void YmatanoSeven_Disp() {
	// ラスボス前蛇の攻撃の表示
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].sevenAttackFlg == TRUE) {
			Last_Yamatano_Boss_Attack_Disp[g_boss_Yamatano[i].attackFlg](g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, &g_boss_Yamatano[i].sevenAttackFlg, &g_boss_Yamatano[i].coolTime);	// ラスボス前蛇の攻撃
		}
	}
}
// 動き
void YmatanoSeven_Move() {
	//	0 リュウグウ
		//	1 雑魚変異
		//	3 カエル
		//	4 蜘蛛
		//	5 雲
		//	6 クラゲ
		//	7 分身
		//	8 黒い水

		// 7体の蛇出現フラグを管理
	Last_Boss_SnakeDispFlg_Managar();

	// 蛇が倒される処理
	Boss_Snake_Knockdown();

	// ７体の蛇の攻撃抽選
	{

		static int attackFlg[YAMATANO_NECK] = { 0, 0, 0, 0, 0, 0, 0 };							// attackフラグを初期化
		int bossAttackSet[][3] = { {LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_WATER_BULLET},	// 一体目の蛇
								   {LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_ENEMY_DROP},		// ２体目の蛇
								   {LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_LONGTON},					// ３体目の蛇
								   {LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINISPIDER_DROP},	// ４体目の蛇
								   {LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINICLOUD_DROP},	// ５体目の蛇
								   {LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_MINIKURAGE},				// ６体目の蛇
								   {LAST_BOSSATTACK_SHADOW, LAST_BOSSATTACK_SHADOW, LAST_BOSSATTACK_SHADOW} };							// ７体目の蛇
		for (int i = 0; i < YAMATANO_NECK; i++) {
			if ((g_boss_Yamatano[i].popflg == LASTBOSS_ON)
				&& (g_boss_Yamatano[i].sevenAttackFlg == FALSE)) {
				if (g_boss_Yamatano[i].coolTime++ > 360) {	// 硬直時間一定以上


					attackFlg[i] = InputRand(bossAttackSet[i][0], bossAttackSet[i][1], bossAttackSet[i][2]);			//乱数でどの攻撃をするかを決定


					if (attackFlg[i] == LAST_BOSSATTACK_ENEMY_DROP) {		// 歩く雑魚敵を召喚する時、情報を初期化
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].walk.BossArea_WlakInit(g_boss_Yamatano[1].x, g_boss_Yamatano[1].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINISPIDER_DROP) {	// ミニスパイダーを召喚する際、情報を初期化
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].spider.BossArea_SpiderInit(g_boss_Yamatano[3].x, g_boss_Yamatano[3].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINICLOUD_DROP) {	// ミニスパイダーを召喚する際、情報を初期化
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].cloud.BossArea_CloudInit(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINIKURAGE) {	// ミニクラゲを召喚する際、情報を初期化
						for (int i = 0; i < KURAGE_MAX; i++) {
							g_enemy[i].kurage.BossArea_KurageInit(g_boss_Yamatano[i].y);
							g_enemy[i].kurage.flg = TRUE;
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_SHADOW) {	// 影を召喚する際、情報を初期化
						g_boss_shadow.ShadowInit(g_boss_Yamatano[i].x, (GROUND - g_boss_Yamatano[i].h), TRUE);
					}

					g_boss_Yamatano[i].attackFlg = attackFlg[i];														// 攻撃する場合、フラグに対応した数字を入れる
					g_boss_Yamatano[i].sevenAttackFlg = TRUE;															// 添え字で蛇の攻撃フラグをつないでいる攻撃フラグをオンに

				}
			}
		}
	}

	// ラスボス前の７体の蛇の攻撃
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].sevenAttackFlg == TRUE) {
			Last_Yamatano_Boss_Attack_Move[g_boss_Yamatano[i].attackFlg](g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, &g_boss_Yamatano[i].sevenAttackFlg, &g_boss_Yamatano[i].coolTime);	// ラスボス前蛇の攻撃
		}
	}
	// 蛇追加シーン
	Snake_Add_To_Anime();
	// ボスが倒される
	Boss_Knock_Down();
}
/*********************************************

* 蛇追加シーン

*/////////////////////////////////////////////
void Snake_Add_To_Anime() {
	for (int i = 0; i < YAMATANO_NECK; i++) {	// 蛇追加シーン
		if (g_boss_Yamatano[i].attackFlg == 0)	// 何もしていなかったら
			if (g_boss_Yamatano[i].popflg == LASTBOSS_MINION) {
				static bool upFlg[YAMATANO_NECK] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };	// 上に上がるフラグ
				int moveX = 2;					// ボスのX軸揺らし用
				int moveY = 8;					// ボスの首の落下速度
				/*if (cnt++ > 5 && cnt <= 10) {
					moveX = -2;
				}
				else if (cnt > 10) {
					cnt = 0;
				}*/
				if ((g_boss_Yamatano[i].y > (BOSS_UPMAX - 50))
					&& (upFlg[i] == TRUE)) {
					g_boss_Yamatano[i].y -= moveY;			// 上に上がっていく
				}
				else if (g_boss_Yamatano[i].y <= (BOSS_UPMAX - 50)) {
					upFlg[i] = FALSE;
				}
				if ((g_boss_Yamatano[i].y < BOSS_UPMAX)
					&& (upFlg[i] == FALSE)) {
					g_boss_Yamatano[i].y += moveY / 2;			// 下に下がっていく(ゆっくり)

				}
				else if ((upFlg[i] == FALSE)					// 所定の位置まで来たら
					&& (g_boss_Yamatano[i].y >= BOSS_UPMAX))
				{

					for (int i = 0; i < YAMATANO_NECK; i++) {	// アップフラグを初期化して
						upFlg[i] = TRUE;
					}
					g_boss_Yamatano[i].popflg = LASTBOSS_ON;	// 出現フラグをステンバイ状態へ
				}
			}
	}
}
/*********************************************

* 蛇の出現フラグ管理

*/////////////////////////////////////////////
void Last_Boss_SnakeDispFlg_Managar() {
	if (g_lastBoss_StartAnimeFlg != TRUE) {
		int cnt = 0;		// 表示されているボスのカウント
		int killCnt = 0;	// 倒されているボスのカウント
		int offCnt = 0;		// 表示されていないボスのカウント
		int tagBuf = 0;		// 表示されている蛇のタグを確認
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
				if (next >= 7) {
					break;
				}
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
					//if()
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
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON /*|| g_boss_Yamatano[i].popflg == LASTBOSS_MINIKILL*/) {
			if (g_boss_Yamatano[i].damageFlg == TRUE) {
				// 被弾モーション終わったらフラグをFALSE
				g_boss_Yamatano[i].damageFlg = FALSE;
			}
			else if (g_boss_Yamatano[i].hp <= 0) {		// hpが０だった場合、ボスの首を落として次に入れ替える準備をする
				
				if (g_boss_Yamatano[i].y < GROUND) {
					//g_boss_Yamatano[i].popflg = LASTBOSS_MINIKILL;	// 倒したけど、まだ画面にいる状態
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

/*********************************************

* ラスボス前の７体の蛇の情報の初期化

*/////////////////////////////////////////////
void lasbossInfo::lasbossInit(int num) {					// ラスボスの本体以外(7体の初期化)
		hp = 1;						 // Hpの初期化
		attackFlg = 0;				 // なんの攻撃をしているかのフラグ
		popflg = LASTBOOS_OFF;       // 画面にいるかいないか、とどめを刺せるかどうかのフラグ
		coolTime = 0;				 // 硬直時間
		damageFlg = FALSE;			 // ダメージを食らっているかどうかのフラグ
		sevenAttackFlg = FALSE;
		w = 230;					// 幅の初期位置
		h = 490;					// 高さの初期位置
		switch (num)
		{
		case 0:
			x = 998;				// X座標の初期位置
			y = 183;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			tag = TAG_BOSS_RIGHT;	// 左にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		case 1:
			x = 718;				// X座標の初期位置
			y = 183;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
			tag = TAG_BOSS_LEFT;	// 右にいる
			popflg = LASTBOOS_OFF;		// 出現フラグをオン
			break;					// ブレイク
		case 2:
			x = 998;				// X座標の初期位置
			y = GROUND;				// Y座標の初期位置
			//y = 0;				// Y座標の初期位置
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

/*********************************************

* ラスボスの初期化

*/////////////////////////////////////////////
void LastBossInit() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		g_boss_Yamatano[i].lasbossInit(i);
	}
}
/**************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
**********************************************														   ********************************************
*********************************					ラスボスの攻撃手段!!!!!!←見づらいじゃんかああああ！			*******************************
**********************************************														   ********************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
**************************************************************************************************************************************************/


/**************************************************************************************************************************************************

* ボスが水弾で攻撃をする関数

*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 水弾の描画
void Last_Boss_Attack_WaterBullet_Disp(int bx, int by, int*boss_AttackFlg, int* coolTime) {
	static int animationMax = 3;				// アニメーション
	static int anime = 0;						// アニメ推移
	static int time = 0;						// 経過時間
	static int startX = bx,
		startY = by + 100;	// 水弾の初期位置
	static int moveX = 0, moveY = 0;			// 水弾の移動量
	static int noDamegeCnt = 60;				// ダメージを受け付けない時間
	static bool attackFlg = FALSE;				// 攻撃判断フラグ	 treu:攻撃済  false:未攻撃

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
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}
	}

	// 水弾が画面外に出たときの処理
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		*boss_AttackFlg = FALSE;
		*coolTime = 120;
	}

	// 水弾が切られた時の処理
	if ((g_player.attackFlg == TRUE)
		&& (noDamegeCnt >= 30)
		&& (*SkillMove[g_player.skillFlg - 1])(startX + moveX - 40, startY + moveY - 20, 65, 55) == TRUE) {
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 20) {
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}

	}

	// 水弾のアニメーション
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// 水弾の表示
	if (attackFlg == FALSE) {
	/*	moveX -= 7.5;
		moveY += 2.5;*/
		moveX -= 10.5;
		moveY += 4.5;
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
		*boss_AttackFlg = FALSE;
		*coolTime = 120;
	}
	// デバッグ
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
}

// 水弾の内部的な動き
void Last_Boss_Attack_WaterBullet_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

}
/****************************************************************************************************************************************************

* ボスが弱い敵を出す攻撃をする関数

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 歩く弱い敵を出す(表示)

void Last_Boss_Attack_BossEnemyDrop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// 一回に出てくるエネミーの最大数
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++stayTime > 60) {
		// エネミーの出現フラグをオンにする

		if (g_enemy[enemy_cnt].walk.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].walk.flg = TRUE;
			stayTime = 0;

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
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 320;

			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}
// 弱い敵を出す(動き(当たり判定など))
void Last_Boss_Attack_BossEnemyDrop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // 歩く雑魚敵の最大数回す


		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= (g_speedLevel - 3);		// 歩く雑魚敵の移動

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].walk.x + ENEMY_WIDTH < 0) {			// 画面外へいくと初期化

			g_enemy[i].walk.BossArea_WlakInit(bx, by);
			//g_enemy[i].walk.flg = TRUE;
		}


	}
}
/****************************************************************************************************************************************************

* ボスが津波を出す

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Last_Boss_Attack_GenerateWave_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
//	const float gravity = 1;				// ジャンプに掛かる重力
//	const int rise = 3;						// ジャンプ時の上昇力
//	static int animationMax[2] = { 0, 0 };	// アニメーション最後尾	0:ボスジャンプ	1:津波
//	static int anime[2] = { 0, 0 };			// 現在表示している画像	0:ジャンプ  1:津波
//	//static int g_noDamegeCnt = 60;			// ダメージを受け付けない時間
//	static int time = 0;					// アニメーション用時間変数
//	static float moveY = 0;					// 重力の加算用変数
//	static bool jumpFlg = FALSE;			// ボスがジャンプ済みかの判断用変数	TRUE:ジャンプ済み 
//
//	// ボスがジャンプするアニメーション
//	if (g_wave.dispFlg == FALSE) {
//
//		// アニメーションの加算
//		if (time++ % 12 == 11)anime[0]++;
//		if (anime[0] > animationMax[0])anime[0] = 0;
//
//		if (anime[0] < 1
//			&& jumpFlg == FALSE) {
//			g_boss[BOSS_STAGE2].x -= g_speedLevel;
//		}
//		else {
//			jumpFlg = TRUE;
//		}
//
//		// ジャンプ中の挙動
//		if (jumpFlg == TRUE) {
//			moveY += gravity;
//
//			if (g_boss[BOSS_STAGE2].y <= 397) {
//				g_boss[BOSS_STAGE2].x += g_speedLevel;
//				g_boss[BOSS_STAGE2].y -= rise + moveY;
//			}
//			if (g_boss[BOSS_STAGE2].y > 397) {
//				g_boss[BOSS_STAGE2].y = 397;
//				g_wave.dispFlg = TRUE;			// 津波を発生
//			}
//		}
//
//	}
//
//	// 津波のアニメーション
//	if (g_wave.dispFlg == TRUE) {
//		g_wave.x -= g_speedLevel;
//
//		// 津波の描画
//		DrawBox(g_wave.x, g_wave.y,
//			g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT, 0x0000FF, TRUE);
//
//		// 津波がプレイヤーに当たった際の処理
//		if (g_noDamageCnt >= 60
//			&& PlayerHitCheck(g_wave.x, g_wave.y,
//				g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT) == 1) {
//
//			g_noDamageCnt = 0;
//			if (g_player.barrierFlg == FALSE) --g_player.hp;
//			else g_player.barrierFlg = FALSE;
//			g_boss[BOSS_STAGE2].attackFlg = 0;
//		}
//
//		// 津波が画面外に出る処理
//		if (g_wave.x + BOSS_WAVE_WIDTH < 0) {
//			jumpFlg = FALSE;
//			g_wave.dispFlg = FALSE;
//			g_boss[BOSS_STAGE2].attackFlg = 0;
//		}
//	}
//
//}
//void Last_Boss_Attack_GenerateWave_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
//	
//}
/*********************************************

* カエルのボスが舌を伸ばす攻撃

*/////////////////////////////////////////////
void Last_Boss_Attack_BossLongTon_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int plas = 0;			// 長くしていく

	// ボスの舌の座標の初期化
	g_boss3_Ton.Boss3_TonInit(bx, by + g_boss_Yamatano[2].h / 2);
	// ボスの舌の幅と高さの初期化
	int tonW = g_boss3_Ton.x + plas;
	int tonH = g_boss3_Ton.y + BOSS_TON_HEIGHT;

	DrawFormatString(500, 500, 0x0000FF, "plas=%d\tonH=%d", plas, tonH);
	// 舌の画像
	DrawModiGraph(tonW, g_boss3_Ton.y,	// 左上
		g_boss3_Ton.x, g_boss3_Ton.y,					// 右上
		g_boss3_Ton.x, tonH,			// 右下
		tonW, tonH,		// 左下
		g_pic.bossTongue, TRUE);
	//DrawBox(g_boss3_Ton.x, g_boss3_Ton.y, tonW, tonH, 0xFFFF00, TRUE);

	static bool tonFlg = TRUE;	// 舌を伸ばすフラグ

	// 舌の画像を引き延ばす処理
	if (tonW > -100 && tonFlg == TRUE) {
		plas -= 5;							// 舌を伸ばす
	}
	else if(tonFlg == TRUE){

		tonW = 0;							// 舌を固定
		tonFlg = FALSE;
	}
	if (plas < 0 && tonFlg == FALSE) {
		plas += 10;							// 舌を戻す
	}
	else if(tonFlg == FALSE){
		*boss_AttackFlg = FALSE;		// attackフラグを初期化
		*coolTime = 0;					// クールタイムの初期化
		plas = 0;
		tonFlg = TRUE;
	}

	if (BossDamageCheck(g_boss_Yamatano[2].hp) == TRUE) {		// ボスが攻撃されたら攻撃中断してジャンプして逃げる
		*boss_AttackFlg = FALSE;		// attackフラグを初期化
		*coolTime = 0;					// クールタイムの初期化
		plas = 0;
		tonFlg = TRUE;

		
	}														   // ボスがプレイヤーに当たったら、ダメージを与えて逃げる
	//else if (PlayerHitCheck(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, BOSS_STAGE3_WIDTH, BOSS_STAGE3_HEIGHT) == TRUE) {
	//	if (g_player.barrierFlg == FALSE) --g_player.hp;
	//	else g_player.barrierFlg = FALSE;
	//	g_noDamageCnt = 0;
	//	g_boss[BOSS_STAGE3].attackFlg = 0;		// attackフラグを初期化
	//	plas = 0;
	//}

	// ボスの舌がプレイヤーに当たったら、ダメージを与えて逃げる		* 横幅で -10 しているのはプレイヤーに当たらない為の調整
	if (PlayerHitCheck(g_boss3_Ton.x + plas, g_boss3_Ton.y, (plas * -1), BOSS_TON_HEIGHT - 10) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		g_noDamageCnt = 0;
		*boss_AttackFlg = FALSE;		// attackフラグを初期化
		*coolTime = 0;					// クールタイムの初期化
		plas = 0;
	}
}

void Last_Boss_Attack_BossLongTon_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	//g_boss[BOSS_STAGE3].x -= 2;

	//if (Boss_3_Jump(&coolTime, &boss_JumpFlg, 1) == TRUE) {
	//	g_boss[BOSS_STAGE3].attackFlg = 0;	// attackフラグをオフへ
	//}
}

/*********************************************

* ミニ蜘蛛を出す

*/////////////////////////////////////////////
// 表示
void Last_Boss_Attack_MiniSpider_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// 一回に出てくるエネミーの最大数
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++stayTime > 60) {
		// エネミーの出現フラグをオンにする

		if (g_enemy[enemy_cnt].spider.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].spider.flg = TRUE;
			stayTime = 0;

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
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 300;
			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}

// 動き
void Last_Boss_Attack_MiniSpider_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {


	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // ミニ蜘蛛の最大数回す


		if (g_enemy[i].spider.flg == TRUE) {
			g_enemy[i].spider.x -= (g_speedLevel - 3);		// ミニ蜘蛛の移動

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].spider.x + ENEMY_WIDTH < 0) {		// 画面外にいくと初期化

			g_enemy[i].spider.BossArea_SpiderInit(bx, by);
			//g_enemy[i].walk.flg = TRUE;
		}
	}
}
/*********************************************

* ミニ雲を出す

*/////////////////////////////////////////////
void Last_Boss_Attack_MiniCloud_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// 一回に出てくるエネミーの最大数
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// 出現したエネミーの要素番号
	// クールタイム
	if (++stayTime > 60) {
		// エネミーの出現フラグをオンにする

		if (g_enemy[enemy_cnt].cloud.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].cloud.flg = TRUE;
			stayTime = 0;

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
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 300;
			enemyDropCnt = 0;                        // エネミーを出した回数を初期化
			enemy_cnt = 0;							 // エネミーの出現した回数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };        // エネミーの出現フラグバッファーを初期化
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// 敵の蒸発アニメーション
	EnemyEvaporation();
}
// 動き
void Last_Boss_Attack_MiniCloud_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // ミニ雲の最大数回す


		if (g_enemy[i].cloud.flg == TRUE) {
			g_enemy[i].cloud.x -= (g_speedLevel - 3);	   // ミニ雲を移動
			g_enemy[i].cloud.y = (GROUND - ENEMY_HEIGHT) - 200;
			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].cloud.x + ENEMY_WIDTH < 0) {		// ミニ雲が範囲外まで行くと初期化

			g_enemy[i].cloud.BossArea_CloudInit(bx, by);

		}
	}
}

/*********************************************

* 雷撃による攻撃

*/////////////////////////////////////////////
void Last_Boss_Attack_Lightning_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	//static int stopCnt = 0;	// 雷撃を表示させる時間


	//if (g_rightning.cnt <= 0) {
	//	DrawBox(g_rightning.x, g_rightning.y, g_rightning.x + 526, g_rightning.y + 488, 0x00FFFF, TRUE);
	//	g_rightning.cnt = 0;
	//	stopCnt++;
	//}

	//if (stopCnt >= 90) {
	//	g_rightning.cnt = 0;					 // 雷撃までのカウントを初期化
	//	g_boss[g_select_Stage].attackFlg = 0;    // attackフラグを初期化
	//	stopCnt = 0;							 // 雷撃の表示カウントを初期化
	//}
}

void Last_Boss_Attack_Lightning_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	/*g_rightning.cnt -= 50;*/
}

/*********************************************

* ミニクラゲによる攻撃

*/////////////////////////////////////////////
void Last_Boss_MiniKurage_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {

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

void Last_Boss_MiniKurage_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// ミニクラゲの配置される位置
	int cnt = 0;						// 雑魚敵が倒された数をカウント
	for (int i = 0; i < KURAGE_MAX; i++) {
		
		if (g_enemy[i].kurage.flg == FALSE) {
			cnt++;						// 倒された数をカウント
			
		}
		if (cnt >= KURAGE_MAX) {		// カウントが一定数以上なら攻撃終了
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}
	}
	
	// 表示されていて、初期ポジションにいない雑魚敵を初期ポジに移動させる
	for (int i = 0; i < KURAGE_MAX; i++) {
		if (g_enemy[i].kurage.flg == TRUE) {
			//g_enemy[buf].kurage.x = position[buf].x;
			//g_enemy[buf].kurage.y = position[buf].y;
			float angle;
			angle = atan2((g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x));
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);


		}
	}


	static bool ataackFlg_AirKurage = FALSE;	// 空中で飛んでくるクラゲの攻撃フラグ
	static bool attackFlg_GroundKurage = FALSE;	// 地上で飛んでくるクラゲの攻撃フラグ
	static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// クラゲが攻撃で使われていないか TRUE:使われている FALSE:使われていない
	static int attackKurageBuf_Air;											// 攻撃で使われていなクラゲの要素番号を記憶させる(空中攻撃用)
	static int attackKurageBuf_Ground;											// 攻撃で使われていなクラゲの要素番号を記憶させる(地上攻撃用)

	
	// クラゲの攻撃をセット
	int attckSet = InputRand(BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_AIR);

	for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// ミニクラゲが攻撃を行えるかチェック
		if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
			ataackFlg_AirKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
			attackKurageCheck[attackKurageBuf_Air] == TRUE;										// 攻撃中のフラグをオンにする
			break;																				//使えるクラゲの要素番号を吐き出す
		}
	}


	// ボスがミニクラゲで攻撃すると判断した(地上で)
	if ((attckSet == BOSSATTACK_MINIKURAGE_AIR)
		&& (ataackFlg_AirKurage != TRUE)) {	// 空中での攻撃をしてない時

		for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// ミニクラゲが攻撃を行えるかチェック
			if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
				ataackFlg_AirKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
				attackKurageCheck[attackKurageBuf_Air] = TRUE;										// 攻撃中のフラグをオンにする
				break;																				//使えるクラゲの要素番号を吐き出す
			}
		}
	}

	// ボスがミニクラゲで攻撃すると判断した(空中で)
	if ((attckSet == BOSSATTACK_MINIKURAGE_GROUND)
		&& (attackFlg_GroundKurage != TRUE)) {	// 地上での攻撃をしてない時
		for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// ミニクラゲが攻撃を行えるかチェック
			if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
				attackFlg_GroundKurage = TRUE;															// 攻撃が行えるならフラグをオンにする
				attackKurageCheck[attackKurageBuf_Ground] = TRUE;										// 攻撃中のフラグをオンにする
				break;																				//使えるクラゲの要素番号を吐き出す
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
	//	attackFlg_GroundKurage = FALSE;
	//}

	// 空中でミニクラゲが攻撃をする
	if (ataackFlg_AirKurage) {
		Last_BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
	}

	if (attackFlg_GroundKurage) {
		Last_BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
	}

	// ミニクラゲとの当たり判定
	KurageHit();	// ヒットするとプレイヤーのHp減少
}

// ミニクラゲの空中攻撃
void Last_BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage) {


	if (g_enemy[attackKurageBuf_Air].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Air].kurage.BossArea_KurageInit(g_boss_Yamatano[5].y);

		//g_boss_Yamatano[5].attackFlg = 0;
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
void Last_BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage) {

	if (g_enemy[attackKurageBuf_Ground].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Ground].kurage.BossArea_KurageInit(g_boss_Yamatano[5].y);
		//g_boss_Yamatano[5].attackFlg = 0;
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

/*********************************************

* 影分身による攻撃

*/////////////////////////////////////////////
void Last_Boss_Shadow_Attack_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {


	//static int anime = 0;							// プレイヤーの画像を変える
	//static int time = 0;							// 画像を切り替えるタイミング調整


	//if (++time % 4 == 0) anime++;
	//if (anime < g_shadowMotionReset || anime > g_shadowMaxMotion) anime = g_shadowMotionReset;

	// 影
	//DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime], TRUE, TRUE);
	DrawBox(g_boss_shadow.x, g_boss_shadow.y, g_boss_shadow.x + g_boss_shadow.w, g_boss_shadow.y + g_boss_shadow.h, 0x00F0F0, TRUE);
}

// 

void Last_Boss_Shadow_Attack_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	if (g_boss_shadow.x + g_boss_shadow.w <= 0) {
		*boss_AttackFlg = FALSE;
		*coolTime = 300;
	}
	else {
		g_boss_shadow.x -= 3;
	}
}

/*********************************************

* 黒い炎の攻撃

*/////////////////////////////////////////////
struct flame : picInfo {
	void flameInit(int bx, int by) {
		x = bx;
		y = by;
		w = 100;
		h = 100;
		
	}
};

void Last_Boss_BrackFire_Disp() {
	
}

void Last_Boss_BrackFire_Move() {

}

/*********************************************

* 関数ポインタ合わせ(仮)

*/////////////////////////////////////////////
// 攻撃をしない
void Last_Boss_Attack_Null_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	*boss_AttackFlg = 0;
	*coolTime = 300;
}
// 攻撃をしない
void Last_Boss_Attack_Null_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	*boss_AttackFlg = 0;
	*coolTime = 300;
}
