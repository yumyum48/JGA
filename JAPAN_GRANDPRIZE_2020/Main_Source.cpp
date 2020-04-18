#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Init.h"
#include "Map.h"
#include "GameScene.h"
#include "Controler.h"
#include "Select.h"
#include "enemy.h"
#include "Dynadelete.h"

#define DEBUG_TEXT_ON


/*********************************************

* メモ
	
	PAD_INPUT_A	// □ボタン
	PAD_INPUT_B // ×ボタン
	PAD_INUPT_C	// 〇ボタン
	PAD_INPUT_D	// Rスティック押し込み！？
	PAD_INPUT_F	// Lスティック押し込み
	PAD_INPUT_H	// パッド押し込み
	
	PAD_INPUT_1 // □ボタン
	PAD_INPUT_2 // ×ボタン
	PAD_INPUT_3 // 〇ボタン
	PAD_INPUT_4 // △ボタン

*/////////////////////////////////////////////

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
mouse g_mouseInfo;				// マウスの状態管理
image g_pic;					// 画像の管理
key g_keyInfo;					// キーボードの状態管理
int g_gameScene;				// 画面のシーンの制御	// 0:ゲームタイトル 1:ステージセレクト 2:ゲームプレイ3:ゲームオーバー4:ゲームクリア

DINPUT_JOYSTATE g_controler;
controler g_button;

int g_game_stage;				//ステージをセレクト
enemyType g_enemy[ENEMY_MAX];	// 敵の情報

int g_speedLevel;				// スクロールレベルの設定を保存

bossType g_boss[MAP_MAX];		//ボスの情報

int g_enemybeat;				// エネミーを倒した数をカウントする
/*********************************************

* 関数のプロトタイプ宣言

*/////////////////////////////////////////////
// ゲームのメインプログラム
int Main(void);					// ゲームのメイン処理
void GameScene(int gameScene);	// 画面のシーン管理

/**************************************************************************

* WinMain関数

**************************************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// フルスクリーンにしないかどうか TRUE:しない FALSE:する
	ChangeWindowMode(TRUE);

	// ウィンドウ画面の大きさ
	SetGraphMode(1280, 768, 32);
	
	// DXライブラリの初期化
	if (DxLib_Init() == -1) return  -1;
	if (LoadPicture() == -1)return  -1;

	// メイン関数を呼ぶ
	Main();

	// DXライブラリの後始末
	DxLib_End();

	// 終了
	return 0;
}
/**************************************************************************

*  ゲームのメインプログラム

**************************************************************************/
int Main(void) {

	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームの初期化
	GameInit();

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		// 画面のクリア	※描画類はこの関数の下へ！
		ClearDrawScreen();

		// マウス、キーボードの座標取得や、入力情報の取得
		ControlInfo(&g_mouseInfo, &g_keyInfo);

		//コントローラーチェック
		ControlerCheck();

		// ゲームシーンの中を見て適当なゲーム画面を描画
		GameScene(g_gameScene);
		
		// デバッグモード(変数の中の文字を描画)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0xffff00, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0xFFFF00, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
#endif // DEBUG_TEXT_ON

		//DynaDelete();		// 動的配列をメモリ解放

		// 画面の更新
		ScreenFlip();
	}
	// 終了
	return 0;
}

// ゲームシーンの管理
void GameScene(int gameScene) {
	
	switch (gameScene){
	case GAME_TYTLE:	StageSelect();  break;	 // ゲームタイトル
	case GAME_SELECT:					break;	 // ゲームセレクト
	case GAME_PLAY:	    GamePlay();		break;	 // ゲームプレイ	
	case GAME_OVER:						break;	 // ゲームオーバー
	case GAME_CLEAR:					break;	 // ゲームクリア
	case GAME_STAGE_CLEAR:				break;	 // ゲームステージクリア
	}
}

	

