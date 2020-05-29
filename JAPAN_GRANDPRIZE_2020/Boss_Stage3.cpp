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


/*********************************************

* ステージ３のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage3() {
	// ボスの大きさ測るメーター
	/*static int bw = 0;
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
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);*/

	//DrawRotaGraph(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, 0.9f, 0.0, g_pic.enemy_walk[0], FALSE, TRUE);

	DrawBox(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, g_boss[BOSS_STAGE3].x + BOSS_STAGE3_WIDTH, g_boss[BOSS_STAGE3].y + BOSS_STAGE3_HEIGHT, 0x00FF00, TRUE);

	if (g_boss[BOSS_STAGE3].attackFlg != 0) {						// ボスが攻撃していれば
		BossAttackDisp();	// ボスの攻撃
	}
}


// 動き(これクラスのがよくね？?ね？)メモ：ブラッシュアップでボスが円を描くようにジャンプさせる
void BossMove_Stage3() {
	static int coolTime = 0;						// 硬直時間
	int boss_MaxDown = 290;							// ボス３の落下した際のY地点
	static int boss_JumpFlg = BOSS_3_JUMPOFF;		// ボスのジャンプをするフラグ0: 下降する地面なら座標変わらずそのまま　1:ジャンプする 2: 下降する
	int boss_startX = 822;							// ボス３のX座標の初期値


	int num = GetRand(2);
	if (BossAttackCheck(g_boss[BOSS_STAGE3].attackFlg) == TRUE)	// ボスが前フレームで攻撃をしていたかを確認
		num = 1;	// していれば、座標調整のため強制ジャンプ

	//	ボスがジャンプをするのか攻撃をするのかを判断する(乱数で決定)
	if( (g_boss[BOSS_STAGE3].y >= boss_MaxDown) 
	&&  (coolTime++ >= 15) 
	&& (boss_JumpFlg == BOSS_3_JUMPOFF) 
	&& (g_boss[BOSS_STAGE3].attackFlg == 0) ) {	// 地面にいるとき クールタイムが一定時間たっているとき ボスがジャンプしている時　ボスが攻撃していないとき
			
		if (num == 0) {
			g_boss[BOSS_STAGE3].attackFlg = BOSSATTACK_LONGTON;	// 舌を伸ばす攻撃
		}
		else {
			boss_JumpFlg = BOSS_3_JUMPON;
		}

	}
	//coolTime = 0;
	int jumpTypeflg = 0;	// 0なら真上 1ならX座標を修正しながら戻る
	if (g_boss[BOSS_STAGE3].x < boss_startX) {
		jumpTypeflg = 1;
	}
	else {
		g_boss[BOSS_STAGE3].x = boss_startX;
		jumpTypeflg = 0;
	}
	Boss_3_Jump(&coolTime, &boss_JumpFlg, jumpTypeflg);

	if (g_boss[BOSS_STAGE3].attackFlg != 0) {						// ボスが攻撃していれば
		BossAttackMove();	// ボスの攻撃
		
	}
	
	Boss_Knock_Down();
}