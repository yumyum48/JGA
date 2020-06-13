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
#include "Sounds.h"

/******************************************************
// マクロの定義
*******************************************************/
#define STAGE_NUMBER			 (7)
#define MENU_SAVE_BOX_XPOINT_MAX (724)	// メニュー画面とセーブ画面の背景が移動して表示されるX座標
#define MENU_SAVE_BOX_MOBE		 (10)	// メニュー画面とセーブ画面の背景が移動するスピード
#define MENU_BOX_XPOINT_MIN		 (1182)	// メニュー画面が隠れている時のX座標
#define SAVE_BOX_XPOINT_MIN		 (1280)	// セーブ画面が隠れている時のX座標
/******************************************************
// グローバル変数の宣言
*******************************************************/
picInfo g_menuBox;		// メニューウィンドウの情報
picInfo g_saveBox;		// セーブウィンドウの情報
int g_menuFlg;			// メニューウィンドウを出現させるフラグ  0:出現させない 1:メニュー画面を出現させる 2:セーブ画面を出現させる
int g_menuSelect;		// 今選択しているメニューを取得する
int g_saveSelect;		// 今選択しているセーブフォルダを取得する

int g_cursorAnime = 0;	//メニューのカーソルアニメーション
/******************************************************
// 列挙体の宣言
*******************************************************/
enum {
	MENU_OFF,	// メニュー画面がオフ
	MENU_ON,	// メニュー画面がオン
	MENU_SAVE,	// セーブ画面がオン
};
/******************************************************
// セレクト画面の管理
*******************************************************/
void StageSelect() {
	PlaySoundMem(g_sound[BGM_SELECT], DX_PLAYTYPE_LOOP, FALSE);            //セレクトBGM再生
	SpeedSelect();	// ゲームのスクロールスピードを変更
	SelectMove();	// セレクト画面の操作や動き
	SelectDisp();	// セレクト画面の表示
}
/******************************************************
// セレクト画面の表示
*******************************************************/
void SelectDisp(void) {
	picInfo stage[8];

	// セレクト画面の背景
	//DrawGraph(0, 0, g_pic.selectBack, TRUE);
	DrawRotaGraph2(0, 0, 0, 0, 8.0, 0.0, g_pic.selectBack, TRUE);		// タイトルの背景

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


	int menuSelect_X = g_menuBox.x + 61;												// セレクトウィンドウのメニュー欄のX座標
	int menuSelect_Y[3] = { g_menuBox.y + 57, g_menuBox.y + 57 + 250, g_menuBox.y + 57 + 500 };	// セレクトウィンドウのメニュー欄のY座標

	// メニュー画面の表示
	//DrawBox(g_menuBox.x, g_menuBox.y, g_menuBox.x + 625, g_menuBox.y + 700, 0xFFFFFF, TRUE);
	//DrawRotaGraph(g_menuBox.x + 200, g_menuBox.y + 350, 3.8, -3.14 / 2, g_pic.selectUI[4], TRUE);
	//DrawModiGraph(g_menuBox.x + 200, g_menuBox.y + 350,		// 左上
	//	g_menuBox.x + 625, g_menuBox.y + 350,				// 右上
	//	g_menuBox.x + 200, g_menuBox.y + 700,				// 左下
	//	g_menuBox.x + 625, g_menuBox.y + 700,				// 右下
	//	g_pic.selectUI[4], TRUE
	//);
	DrawModiGraph(g_menuBox.x, g_menuBox.y,			// 左上
		g_menuBox.x + 625, g_menuBox.y,				// 右上
		g_menuBox.x + 625, g_menuBox.y + 700,		// 右下
		g_menuBox.x, g_menuBox.y + 700,				// 左下
		g_pic.selectUI[4], TRUE
	);
	// メニュー画面の項目
	//DrawBox(menuSelect_X, menuSelect_Y[0], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	//DrawBox(menuSelect_X, menuSelect_Y[1], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	//DrawBox(menuSelect_X, menuSelect_Y[2], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[0] + 10, g_pic.selectUI[1], TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[1] + 10, g_pic.selectUI[3], TRUE);
	DrawGraph(menuSelect_X + 50, menuSelect_Y[2] + 10, g_pic.selectUI[2], TRUE);


	// Yボタンの表示
	int yButtonX = menuSelect_X - 64;
	int yButtonY = 75;
	DrawGraph(yButtonX, yButtonY, g_pic.button[0], TRUE);


	// セーブ画面の表示
	//DrawBox(g_saveBox.x, g_saveBox.y, g_saveBox.x + 625, g_saveBox.y + 700, 0x808080, TRUE);
	//DrawRotaGraph(g_saveBox.x + 200, g_saveBox.y + 350, 3.8, -3.14 / 2, g_pic.selectUI[4], TRUE);
	DrawModiGraph(g_saveBox.x, g_saveBox.y,		// 左上
		g_saveBox.x + 625, g_saveBox.y,				// 右上
		g_saveBox.x + 625, g_saveBox.y + 700,		// 右下
		g_saveBox.x, g_saveBox.y + 700,				// 左下
		g_pic.selectUI[4], TRUE
	);
	int saveSelect_X = g_saveBox.x + 61;												// セレクトウィンドウのセーブ欄のX座標
	int saveSelect_Y[3] = { g_saveBox.y + 65, g_saveBox.y + 55 + 250, g_saveBox.y + 55 + 500 };	// セレクトウィンドウのセーブ欄のY座標
	/*DrawBox(saveSelect_X, saveSelect_Y[0], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[1], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[2], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);*/

	// Yボタンの表示
	int yButtonX2 = saveSelect_X - 64;
	int yButtonY2 = 75;
	DrawGraph(yButtonX2, yButtonY2, g_pic.button[0], TRUE);

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
			if (g_cursorAnime < 200) g_cursorAnime += 10;
			//DrawBox(menuSelect_X, menuSelect_Y[g_menuSelect], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, FALSE);
			//DrawGraph(menuSelect_X + 20, menuSelect_Y[g_menuSelect] + 60, g_pic.bossTongue, TRUE);
			DrawExtendGraph(menuSelect_X + 20, menuSelect_Y[g_menuSelect] + 80,
				menuSelect_X + 76 + g_cursorAnime, menuSelect_Y[g_menuSelect] + 100, g_pic.bossTongue, TRUE);
			//DrawGraph(menuSelect_X + 50, menuSelect_Y[g_menuSelect] - 45, g_pic.gauge, TRUE);
			DrawRotaGraph(menuSelect_X + 10 + g_cursorAnime, menuSelect_Y[g_menuSelect] + 50, 0.5, 0, g_pic.skillEffect[9], TRUE);
			DrawGraph(menuSelect_X, menuSelect_Y[g_menuSelect], g_pic.Life[1], TRUE);
		}
		// メニュー画面で保存が押された場合
		else if (g_menuFlg == MENU_SAVE) {
			if (g_cursorAnime < 400) g_cursorAnime += 20;
			if (g_saveBox.x == MENU_SAVE_BOX_XPOINT_MAX) {	// 座標が固定されたら操作可能
				//DrawBox(saveSelect_X, saveSelect_Y[g_saveSelect], saveSelect_X + MENU_SELECT_WIDTH - 100, saveSelect_Y[g_saveSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
				SaveModeDisp(saveSelect_X, saveSelect_Y);	// セーブデータ表示

				// セレクトしているものを視覚化
				DrawExtendGraph(saveSelect_X + 20, saveSelect_Y[g_saveSelect] + 80,
					saveSelect_X + 76 + g_cursorAnime, saveSelect_Y[g_saveSelect] + 100, g_pic.bossTongue, TRUE);
				DrawRotaGraph(saveSelect_X + 10 + g_cursorAnime, saveSelect_Y[g_saveSelect] + 50, 0.5, 0, g_pic.skillEffect[9], TRUE);
				DrawGraph(saveSelect_X, saveSelect_Y[g_saveSelect], g_pic.Life[1], TRUE);
			}
		}
	}

}
/******************************************************
// セレクト画面の動き
*******************************************************/
void SelectMove() {


	if (g_menuFlg == MENU_OFF) {				// メニュー画面が出てないときの処理(マップセレクト)

		MenuScrollOut();						// メニュー画面を横にスクロールアウト

		StageSelectOper();						// ステージの決定のためのカーソルを操作させる

		if (g_keyInfo.keyFlg & PAD_INPUT_A) {	// 決定したステージに移動しながらシーンをゲームプレイに変える

			//Get_NowDisp(GAME_PLAY, 2);
			HyperStop(g_sound[BGM_SELECT]);		//すべて止める最強関数
			g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

		}
	}
	else if (g_menuFlg == MENU_ON) {	// メニュー画面を表示する時

		MenuScrollIn();		// メニュー画面を見えるように画面中央付近まで移動させ、セーブ画面があれば、下げる

		MenuSelectOper();	// メニューカーソル制御処理

		MenuSelect();		// 決定ボタンを押すと対象のメニューへと接続
	}
	else if (g_menuFlg == MENU_SAVE) {	// セーブ画面が出るとき

		bool saveflg = FALSE;			// セーブ画面を表示させるかどうか FALSE:表示させない TRUE:表示させる

		SaveSelectOper();				// セーブメニューカーソル制御処理

		saveflg = SaveMenu_MenuScrollOut(saveflg);			// メニュー画面を画面外までスクロールアウトさせ、させきったらセーブ画面を表示させるフラグをオンにする
		if (saveflg == TRUE) {

			SaveMenu_ScrollIn();							// セーブ画面を画面中央付近まで動かす
			if (g_saveBox.x == MENU_SAVE_BOX_XPOINT_MAX) {	// セーブ画面が中央まで来たら操作可能
				if (g_keyInfo.keyFlg & PAD_INPUT_A) {		// 決定ボタンを押すと
					SaveMenu_Save();
					g_cursorAnime = 0;						// 選択されたファイルにセーブを実行する
				}
				if (g_keyInfo.keyFlg & PAD_INPUT_B) {		// Bボタンを押すと、メニュー選択画面に戻す
					g_menuFlg = MENU_ON;
					g_cursorAnime = 0;
					//g_menuSelect = 0;
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
// 選択されたファイルにセーブを実行する
*******************************************************/
void SaveMenu_Save() {
	Save(g_saveSelect);
	//switch (g_saveSelect) {
	//case 0: ; break;	// ファイル１に保存
	//case 1:; break;	// ファイル２に保存
	//case 2:; break;	// ファイル３に保存
	//default:  break;	// 違う数字がくると何もしない
	//}
}
/******************************************************
// セーブ画面を画面中央付近まで動かす
*******************************************************/
void SaveMenu_ScrollIn() {
	if (g_saveBox.x > MENU_SAVE_BOX_XPOINT_MAX) {	// セーブ画面をスクロールインさせる
		g_saveBox.x -= MENU_SAVE_BOX_MOBE;
	}
	else {
		g_saveBox.x = MENU_SAVE_BOX_XPOINT_MAX;		// 目的の座標までセーブ画面が来たら座標を固定
	}
}
/******************************************************
// メニュー画面を画面外までスクロールアウトさせ、させきったらセーブ画面を表示させるフラグをオンにする
*******************************************************/
bool SaveMenu_MenuScrollOut(bool saveFlg) {

	if (g_menuBox.x < WINDOW_WIDTH) {	// メニューを画面外へスクロールアウト
		g_menuBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_menuBox.x = WINDOW_WIDTH;
		saveFlg = TRUE;				// スクロールアウトさせたら
	}
	return saveFlg;
}
/******************************************************
// 決定ボタンを押すと対象のメニューへと接続
*******************************************************/
void MenuSelect() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		PlaySoundMem(g_sound[SE_KETTEI], DX_PLAYTYPE_BACK, TRUE);			//決定SE再生
		switch (g_menuSelect) {
		case 0: g_menuFlg = MENU_SAVE;		g_menuSelect = 0;		   break;	// データのセーブ
		case 1: g_gameScene = GAME_SKILLCUSTOM;   g_menuSelect = 0;     break;	// スキルカスタマイズ
		case 2: GameInit(); g_menuFlg = MENU_OFF; g_gameScene = GAME_TITLE; HyperStop(g_sound[BGM_SELECT]); break;    // タイトルへ移動
		default:
			break;
		}
	}
}
/******************************************************
// メニュー画面を見えるように画面中央付近まで移動させる
*******************************************************/
void MenuScrollIn() {
	if (g_saveBox.x < SAVE_BOX_XPOINT_MIN) {	// セーブメニューをスクロールアウト
		g_saveBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_saveBox.x = SAVE_BOX_XPOINT_MIN;		// セーブメニューが目標地点に来たら座標を固定
		// セーブ画面が移動しきってから
		// メニュー画面を見えるようにスクロール
		if (g_menuBox.x > MENU_SAVE_BOX_XPOINT_MAX) {
			g_menuBox.x -= MENU_SAVE_BOX_MOBE;
		}
		else {
			g_menuBox.x = MENU_SAVE_BOX_XPOINT_MAX;
		}
	}
}
/******************************************************
// メニュー画面を画面端付近に移動させる
*******************************************************/
void MenuScrollOut() {
	if (g_menuBox.x < MENU_BOX_XPOINT_MIN) {
		g_menuBox.x += MENU_SAVE_BOX_MOBE;
	}
	else {
		g_menuBox.x = MENU_BOX_XPOINT_MIN;
	}
}
/******************************************************
// ステージを決定させるカーソルを操作させる
*******************************************************/
void StageSelectOper() {
	//メニューカーソル移動処理
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_select_Stage > g_select_MAX) g_select_Stage = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
	}
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_select_Stage < 0) g_select_Stage = g_select_MAX;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
	}
}
/******************************************************
// メニュー一覧のカーソルを操作させる
*******************************************************/
void MenuSelectOper() {
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
		if (++g_menuSelect > 2) g_menuSelect = 0;
	}
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
		if (--g_menuSelect < 0) g_menuSelect = 2;
	}
}
/******************************************************
// セーブメニューのカーソルを移動させる
*******************************************************/
void SaveSelectOper() {
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
		if (++g_saveSelect > 2) g_saveSelect = 0;
	}
	// メニューカーソル制御処理
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		g_cursorAnime = 0;
		PlaySoundMem(g_sound[SE_DECISION], DX_PLAYTYPE_BACK, TRUE);			//選択SE再生
		if (--g_saveSelect < 0) g_saveSelect = 2;
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
