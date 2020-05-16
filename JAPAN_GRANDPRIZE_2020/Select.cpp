#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"
#include "Picture.h"
#include "SkillCustom.h"
#include "Change_ScReen_Animation.h"
#include "Init.h"
#include "Save.h"

/******************************************************
// マクロの定義
*******************************************************/
#define STAGE_NUMBER 7

#define MENU_SELECT_WIDTH 320	// メニュー画面の中の選択するメニュー一覧の横幅
#define MENU_SELECT_HEIGHT 84	// メニュー画面の中の選択するメニュー一覧の縦幅
/******************************************************
// グローバル変数の宣言
*******************************************************/
picInfo g_menuBox;		// メニューウィンドウの情報
picInfo g_saveBox;		// セーブウィンドウの情報
int g_menuFlg;		// メニューウィンドウを出現させるフラグ  0:出現させない 1:メニュー画面を出現させる 2:セーブ画面を出現させる
int g_menuSelect;			// 今選択しているメニューを取得する
/******************************************************
// 列挙体の宣言
*******************************************************/
enum {
	MENU_OFF,
	MENU_ON,
	MENU_SAVE,
};
/******************************************************
// セレクト画面の管理
*******************************************************/
void StageSelect() {
	
	SpeedSelect();
	SelectMove();
	SelectDisp();
}
/******************************************************
// セレクト画面の表示
*******************************************************/
void SelectDisp(void) {
	picInfo stage[8];
	
	// セレクト画面の背景
	DrawGraph(0, 0, g_pic.selectBack, TRUE);

	// セレクト画面のマップ
	for (int i = 0; i < MAP_MAX; i++) {
		stage[i].SelectStageInit(i);
		DrawBox(stage[i].x, stage[i].y, stage[i].x + 100, stage[i].y + 100, 0x00FF00, TRUE);
		if (i == 7) {
			DrawBox(stage[i].x, stage[i].y, stage[i].x + 200, stage[i].y + 200, 0x00FF00, TRUE);
		}
	}
	
	// セレクト画面の選択中のウィンドウを表示
	DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 100, stage[g_select_Stage].y + 100, 0xFF0000, FALSE);
	if (g_select_Stage == 7) {
		DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 200, stage[g_select_Stage].y + 200, 0xFF0000, FALSE);
	}


	int menuSelect_X = g_menuBox.x + 122;												// セレクトウィンドウのメニュー欄のX座標
	int menuSelect_Y[3] = { g_menuBox.y + 79, g_menuBox.y + 320, g_menuBox.y + 571 };	// セレクトウィンドウのメニュー欄のY座標

	// メニュー画面の表示
	DrawBox(g_menuBox.x, g_menuBox.y, g_menuBox.x + 625, g_menuBox.y + 700, 0xFFFFFF, TRUE);
	// メニュー画面の項目
	DrawBox(menuSelect_X, menuSelect_Y[0], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[1], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[2], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	
	// セーブ画面の表示
	DrawBox(g_saveBox.x, g_saveBox.y, g_saveBox.x + 625, g_saveBox.y + 700, 0x808080, TRUE);
	int saveSelect_X = g_saveBox.x + 122;												// セレクトウィンドウのセーブ欄のX座標
	int saveSelect_Y[3] = { g_saveBox.y + 79, g_saveBox.y + 320, g_saveBox.y + 571 };	// セレクトウィンドウのセーブ欄のY座標
	DrawBox(saveSelect_X, saveSelect_Y[0], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[1], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[2], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);

	// メニュー画面の機能
	{
		// メニュー画面が出てないとき
		if (g_menuFlg == MENU_OFF) {
			if (g_keyInfo.keyFlg & PAD_INPUT_A) {

				Get_NowDisp(GAME_PLAY, 2);
				//g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

			}
			
		}
		// メニュー画面が出ているとき
		else if (g_menuFlg == MENU_ON) {
			DrawBox(menuSelect_X, menuSelect_Y[g_menuSelect], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
			
		}
		// メニュー画面で保存が押された場合
		else if (g_menuFlg == MENU_SAVE) {
			if (g_saveBox.x == 724) {	// 座標が固定されたら操作可能
				DrawBox(saveSelect_X, saveSelect_Y[g_menuSelect], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
				
			}
			//SaveModeDisp();
		}
	}

}
/******************************************************
// セレクト画面の動き
*******************************************************/
void SelectMove() {
	

	if (g_menuFlg == MENU_OFF) {	// メニュー画面が出てないときの処理(マップセレクト)
		// メニュー画面を横にスクロールアウト
		MenuScrollOut();

		// ステージの決定のためのカーソルを操作させる
		StageSelectOper();
		// 決定したステージに移動しながらシーンをゲームプレイに変える
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {

			//Get_NowDisp(GAME_PLAY, 2);
			g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

		}
	}
	else if(g_menuFlg == MENU_ON){	// メニュー画面を表示する時
		// メニュー画面を見えるように画面中央付近まで移動させ、セーブ画面があれば、下げる
		MenuScrollIn();
		
		
		// メニューカーソル制御処理
		MenuSelectOper();

		// 決定ボタンを押すと対象のメニューへと接続
		MenuSelect();
		
		
	}
	else if (g_menuFlg == MENU_SAVE) {	// セーブ画面が出るとき
		bool saveflg = FALSE;
		// メニューカーソル制御処理
		MenuSelectOper();

		if (g_menuBox.x < 1280) {		// メニュー画面をスクロールアウト
			g_menuBox.x += 10;
		}
		else {
			g_menuBox.x = 1280;
			saveflg = TRUE;				// スクロールアウトさせたら
		}

		if (saveflg == TRUE) {			
			if (g_saveBox.x > 724) {	// セーブ画面をスクロールインさせる
				g_saveBox.x -= 10;
			}
			else {
				g_saveBox.x = 724;		// 目的の座標までセーブ画面が来たら座標を固定

				// 決定ボタンを押すと選択されたファイルに今の情報を保存
				switch (g_menuSelect) {
				case 0: ; break;	// ファイル１に保存
				case 1: ; break;	// ファイル２に保存
				case 2: ; break;	// ファイル３に保存
				default:  break;	// 違う数字がくると何もしない
				}

				if (g_keyInfo.keyFlg & PAD_INPUT_B) {	// Bボタンを押すと、メニュー選択画面に戻す
					g_menuFlg = MENU_ON;
					g_menuSelect = 0;
				}
			}
		}

	}


	// △ボタンを押すとメニューが開く
	if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == FALSE) {
		g_menuFlg = MENU_ON;
	}
	else if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == TRUE) {
		g_menuFlg = MENU_OFF;
	}

	
}
/******************************************************
// 決定ボタンを押すと対象のメニューへと接続
*******************************************************/
void MenuSelect() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		switch (g_menuSelect) {
		case 0: g_menuFlg = MENU_SAVE;		g_menuSelect = 0;		   break;	// データのセーブ
		case 1: g_gameScene = GAME_SKILLCUSTOM;   g_menuSelect = 0;     break;	// スキルカスタマイズ
		case 2: GameInit(); g_menuFlg = MENU_OFF; g_gameScene = GAME_TITLE; break;	// タイトルへ移動
		default:
			break;
		}
	}
}
/******************************************************
// メニュー画面を見えるように画面中央付近まで移動させる
*******************************************************/
void MenuScrollIn() {
	if (g_saveBox.x < WINDOW_WIDTH) {	// セーブメニューをスクロールアウト
		g_saveBox.x += 10;
	}
	else {
		g_saveBox.x = WINDOW_WIDTH;		// セーブメニューが目標地点に来たら座標を固定
		// セーブ画面が移動しきってから
		// メニュー画面を見えるようにスクロール
		if (g_menuBox.x > 724) {
			g_menuBox.x -= 10;
		}
		else {
			g_menuBox.x = 724;
		}
	}
}
/******************************************************
// メニュー画面を画面端付近に移動させる
*******************************************************/
void MenuScrollOut() {
	if (g_menuBox.x < 1182) {
		g_menuBox.x += 10;
	}
	else {
		g_menuBox.x = 1182;
	}
}
/******************************************************
// ステージを決定させるカーソルを操作させる
*******************************************************/
void StageSelectOper() {
	//メニューカーソル移動処理
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_select_Stage > g_select_MAX) g_select_Stage = 0;
	}
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_select_Stage < g_select_MAX) g_select_Stage = g_select_MAX;
	}
}
/******************************************************
// メニュー一覧のカーソルを操作させる
*******************************************************/
void MenuSelectOper() {
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (++g_menuSelect > 2) g_menuSelect = 0;
	}
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (--g_menuSelect < 0) g_menuSelect = 2;
	}
}
/******************************************************
// スクロール速度の選択
*******************************************************/
void SpeedSelect() {
	static int speedSelect = 0;
	static bool StickFlg = FALSE;

	DrawFormatString(100, 10, 0xffff00, "%d", speedSelect);

	// プレイヤーの操作
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (++speedSelect > 2) speedSelect = 0;
	}
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (--speedSelect < 0) speedSelect = 2;
	}
	// スクロール速度の決定
	if (speedSelect == 0) {
		g_speedLevel = SPEED_EASY;
	}
	if (speedSelect == 1) {
		g_speedLevel = SPEED_NORMAL;
	}
	if (speedSelect == 2) {
		g_speedLevel = SPEED_HARD;
	}
	//// スクロール速度の決定
	//if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 0)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_EASY;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 1)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_NORMAL;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0)*/
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 2)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_HARD;
	//}
}
/******************************************************
// セレクトシーンの初期化
*******************************************************/
void SelectInit() {
	g_menuBox.MenuWindowInit();
	g_saveBox.MenuSaveWindowInit();
	//g_menuFlg = FALSE;
}
