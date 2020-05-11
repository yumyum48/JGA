#include "DxLib.h" 
#include "Struct.h"
#include "control.h"
#include "Select.h"
#include "Trap.h"
#include "Picture.h"

								

/*********************************************

* トラップの表示
	
*/////////////////////////////////////////////
void TrapDisp() {
	
	
	if (GetRand(10) == 1) g_trap.dispFlg = TRUE;										// ランダムでトラップを出現させるフラグをオンにする
	
	if (g_trap.dispFlg == TRUE) {
		DrawFormatString(500, 0, 0xFF00FF, "トラップ出てますよ！");
		DrawRotaGraph2(g_trap.x, g_trap.y, 0, 0, 0.3, 0.0, g_pic.trap, TRUE);	// トラップを表示
	}
}


/*********************************************

* トラップの動き

*/////////////////////////////////////////////
void TrapMove() {
	if (g_trap.dispFlg) {
		g_trap.x -= g_speedLevel;														// トラップのX座標をスクロール速度と同じ値で加算させる

		if (g_trap.x + 100 < 0) {
			g_trap.Init();																// トラップが画面外に入った場合初期化
			g_trap.dispFlg = FALSE;
		}
	}
}	

/*********************************************

* トラップの初期化

*/////////////////////////////////////////////
void TrapInit() {
	g_trap.Init();
}