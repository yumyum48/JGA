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
#include "HP.h"
#include "StageClear.h"
#include "GameClear.h"
#include "GameTitle.h"
#include "GameOver.h"
#include "Change_ScReen_Animation.h"
#include "SkillCustom.h"
#include "Save.h"
#include "Sounds.h"
#include "Load.h"
#include "Boss.h"
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

//定数の宣言

const int ENEMY_BEAT_MAX[MAP_MAX] = { 1,1,1,1,1,1,1,1 };	//各ステージの雑魚敵を倒す数です

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
mouse g_mouseInfo;				// マウスの状態管理
image g_pic;					// 画像の管理
key g_keyInfo;					// キーボードの状態管理
int g_gameScene;				// 画面のシーンの制御	// 0:ゲームタイトル 1:ステージセレクト 2:ゲームプレイ3:ゲームオーバー4:ゲームクリア

DINPUT_JOYSTATE g_controler;
controler g_button;

int g_select_Stage;				//ステージをセレクト
enemyType g_enemy[ENEMY_MAX];	// 敵の情報

int g_speedLevel;				// スクロールレベルの設定を保存

bool g_skillswitch;

bossInfo g_boss[MAP_MAX];		//ボスの情報

int g_enemybeat;				// エネミーを倒した数をカウントする

playerInfo g_player;			// プレイヤーの情報

int g_noDamageCnt;				// プレイヤーの無敵時間

trapInfo g_trap;				// トラップの情報

int g_playTime;					// プレイ時間

int g_select_MAX;				// 今プレイヤーがいけるステージを制御する

int g_sound[BGM_MAX];			// BGMの変数

enemyInfo g_enemyBuffer[ENEMY_MAX];	// 撃破した敵の情報を格納する変数

ChoiceInfo g_choice;			//

mapInfo g_map[SCROLL_MAX];		// マップの情報

boss4_parts g_boss4_Thread;		// ボス４の糸の情報
boss4_parts g_boss4_Cloud;		// ボス４の雲の情報
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

	SetMainWindowText("アメニモマケズ");
	// ウィンドウ画面の大きさ
	SetGraphMode(1280, 768, 32);
	
	// DXライブラリの初期化
	if (DxLib_Init() == -1) return  -1;
	if (LoadPicture() == -1)return  -1;

	// フォントを変える
	ChangeFont("HG行書体");

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

	// ゲームモードをタイトルへ
	g_gameScene = GAME_TITLE;

	
	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && g_gameScene != GAME_END) {
		// 画面のクリア	※描画類はこの関数の下へ！
		ClearDrawScreen();

		// マウス、キーボードの座標取得や、入力情報の取得
		ControlInfo(&g_mouseInfo, &g_keyInfo);

		//コントローラーチェック
		ControlerCheck();

		// ゲームシーンの中を見て適当なゲーム画面を描画
		GameScene(g_gameScene);
		//SaveData_CL();
		// デバッグモード(変数の中の文字を描画)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0x0000FF, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0x0000DF, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
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
	case GAME_TITLE:	GameTitle();				break;	 // ゲームタイトル
	case GAME_SELECT:	StageSelect();				break;	 // ゲームセレクト
	case GAME_PLAY:	    GamePlay();					break;	 // ゲームプレイ	
	case GAME_OVER:		GameOver();					break;	 // ゲームオーバー
	case GAME_CLEAR:	GameClear();				break;	 // ゲームクリア
	case GAME_STAGE_CLEAR:	StageClear();			break;	 // ゲームステージクリア
	case GAME_SAVE:									break;	 // ゲームのセーブ
	case GAME_LOAD:		GameLoad();							break;	 // ゲームデータのロード
	case GAME_CHANGE_SCREEN_ANIMATION:	ChangeScreen_Animation();				break;	 // シーン切り替え時のアニメーションシーン
	case GAME_SKILLCUSTOM:	SkillCustom();			break;	 // スキルカスタマイズ
	}
}

	

