#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"

#define DEBUG_TEXT_ON
/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
extern mouse g_mouseInfo;	// マウスの状態管理
extern image g_pic;			// 画像の管理
extern key g_keyInfo;		// キーボードの状態管理
extern int g_gameScene = 0;		// 画面のシーンの制御	// 0:ゲームタイトル 1:ステージセレクト 2:ゲームプレイ3:ゲームオーバー4:ゲームクリア

extern DINPUT_JOYSTATE g_controler;
extern controler g_button; 

enum {
	GAME_TYTLE,
	GAME_SELECT,
	GAME_PLAY,
	GAME_OVER,
	GAME_CLEAR,
};
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

	ChangeWindowMode(TRUE);

	// ウィンドウ画面の大きさ
	SetGraphMode(1088, 768, 32);
	
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

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		// 画面のクリア	※描画類はこの関数の下へ！
		ClearDrawScreen();

		// マウス、キーボードの座標取得や、入力情報の取得
		ControlInfo(&g_mouseInfo, &g_keyInfo);
		GameScene(g_gameScene);
		
		// デバッグモード(変数の中の文字を描画)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0xffff00, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0xFFFF00, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
#endif // DEBUG_TEXT_ON

		// 画面の更新
		ScreenFlip();
	}
	// 終了
	return 0;
}

void GameScene(int gameScene) {
	
	switch (gameScene){
	case GAME_TYTLE:	GamePlay();  break;	 // ゲームの描画
	case GAME_SELECT:				 break;
	case GAME_PLAY:	    GamePlay();	 break;
	}
}

	

