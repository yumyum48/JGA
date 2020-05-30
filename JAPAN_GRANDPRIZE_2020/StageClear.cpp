//// プレイヤーの中心から円がでる
//DrawCircle(g_player.x + 102, g_player.y + 111, 10, TRUE);

#include "DxLib.h"
#include "Struct.h"
#include "StageClear.h"
#include "GameScene.h"
#include "control.h"
#include "Rain.h"
#include "Player.h"
#include "Macro.h"
#include "Map.h"
#include "Struct.h"
#include "Init.h"
#include "Picture.h"
#include "Boss.h"
#include "Select.h"

bool g_animationScene = FALSE;	// アニメーションを終了させてテキストを表示させるフラグ	TRUE:テキストの表示ON	FALSE:ボスを撃破するアニメーション中

picInfo g_clearText;			// クリアした時の「討伐完了！！」の画像
void StageClear() {
	StageClearMove();		// ステージクリアの動き
	StageClearDisp();		// ステージクリアの表示
}


void StageClearDisp() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationDisp();
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		MapDisp();				// マップの表示
		PlayerDisp();			// プレイヤーの表示
		RainDisp();				// 雨の表示
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph2(g_clearText.x, g_clearText.y, 0, 0, 0.6, 0.0, g_pic.stageClearText, TRUE);


		DrawString(g_mouseInfo.mouseX, g_mouseInfo.mouseY, "Aボタンを押すとメニュー画面へ戻ります", 0xFF0000); // Aボタンを押すとセレクト画面に戻ります
		//DrawModiGraph
		//DrawBox(clearText.x, clearText.y)
	}
}

void StageClearMove() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationMove();
	}
	else {
		RainMove();				// 雨の動き

		if (Player_StageClearMove() == 1) {
			if (ClearTextMove() == 1) {
				SetFontSize(39);

				if (g_keyInfo.keyFlg & PAD_INPUT_A) {

					GameInit();
					g_gameScene = GAME_SELECT;
				}
			}
		}
	}
}

int ClearTextMove() {
	if (g_clearText.y < 298) {
		g_clearText.y += 25;
	}
	else {
		g_clearText.y = 298;
		return 1;
	}

	return 0;
}
int Player_StageClearMove() {
	
	if (g_player.y > GROUND) {	// 主人公が浮いていたら地面に落とす
		g_player.y += 10;
	}
	else {
		g_player.y = GROUND;
	}

	if (g_player.x < 500) {	// 主人公のX座標を移動させて固定
		g_player.x += 10;
	}
	else {
		g_player.x = 500;
		
		// プレイヤー静止モーション
		return 1;
	}

	if (g_player.attackFlg == TRUE) g_player.attackFlg = FALSE;
	if (g_player.swordFlg == TRUE) g_player.swordFlg = FALSE;
	
	return 0;
}

// ボス撃破時のアニメーション　描画
void BossDefeatAnimationDisp() {
	MapDisp();						// マップの表示

	(*BossDisp[g_select_Stage])();	// ボスの表示
	PlayerDisp();					// プレイヤーの表示

	RainDisp();						// 雨の表示
}

// ボス撃破時のアニメーション　内部処理
void BossDefeatAnimationMove() {
	static int animationDelay = 0;		// 討伐完了のテキスト表示までのアニメーション時間
	static bool animationFlg = FALSE;	// ボス撃破のアニメを起動させるフラグ	TRUE:アニメの開始	FALSE:権を振りきる猶予時間
	
	animationDelay++;

	// プレイヤーが刀を振り切る猶予時間
	if (animationFlg == FALSE) {
		if (animationDelay % 15 == 0) {
			RainMove();		// 雨の動き
		}
	}
	// ボスを撃破するアニメーション
	else {

	}

	// アニメーション時間の管理
	if (animationDelay > 200) {			// アニメーション終了時の初期化処理
		g_animationScene = TRUE;
		animationDelay = 0;
	}
}

void StageClearInit() {
	g_clearText.x = 279;
	g_clearText.y = -237;

}