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

	// レイヤー的な意味合いでマップを再描画
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}
	// ボスの表示
	//DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);

}

// 動き
void BossMove_Stage_Last() {

}