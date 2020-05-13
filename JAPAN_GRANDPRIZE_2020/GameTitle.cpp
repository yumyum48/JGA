#include "DxLib.h"
#include "control.h"
#include "Controler.h"
#include "GameTitle.h"
#include "Picture.h"
#include "Struct.h"
#include "GameScene.h"
#include "Macro.h"
#include "Rain.h"
#include "Init.h"

enum {	// タイトルのテキストの情報
	TITLE_NEW_START,	// 新しくゲームを始める
	TITLE_ROAD,			// セーブデータから選んでゲームを始める
	TITLE_END,			// ゲームを終了する
	TITLE_MAX,			// 情報の最大数
};
// 定数の宣言
const int TITLETEXT_X[TITLE_MAX] = { 498, 498, 549};	// [初めから]や[続きから]や[終了]の画像のX座標
const int TITLETEXT_Y[TITLE_MAX] = { 402, 536, 665};	// [初めから]や[続きから]や[終了]の画像のY座標

int g_selectCheck;	// 今プレイヤーが選択しているものを確認する(0:初めから 1:続きから 2:終了)

// ゲームタイトルのメイン関数
void GameTitle() {
	TitleMove();
	TitleDisp();	
}

// タイトルの描画
void TitleDisp() {
	picInfo backImage;		// タイトルの背景画像の座標
	picInfo titleRogo;		// タイトルロゴの画像の座標
	
	RainDisp();

	DrawRotaGraph2(backImage.x, backImage.y, 0, 0, 8.0, 0.0, g_pic.title[0], TRUE);		// タイトルの背景
	DrawGraph(107, 118, g_pic.titleText[0], TRUE);										// タイトルのロゴ
	DrawGraph(TITLETEXT_X[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START], g_pic.titleText[1], TRUE);										// [初めから]の文字
	DrawGraph(TITLETEXT_X[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD], g_pic.titleText[2], TRUE);										// [続きから]の文字
	DrawGraph(TITLETEXT_X[TITLE_END], TITLETEXT_Y[TITLE_END], g_pic.titleText[3], TRUE);										// [終了]の文字

	int titleTextW[3] = { 280, 280, 188 };	// タイトルの[初めから][続きから][終了]のテキスト画像の横幅
	int titleTextH[3] = { 84, 84, 87 };	// タイトルの[初めから][続きから][終了]のテキスト画像の縦幅
	switch (g_selectCheck) {
	case 0:
		// 何を選択しているかわかるように四角を視覚化
		DrawBox(TITLETEXT_X[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START], TITLETEXT_X[TITLE_NEW_START] + titleTextW[TITLE_NEW_START], TITLETEXT_Y[TITLE_NEW_START] + titleTextH[TITLE_NEW_START], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_SELECT;	// ゲームセレクトへ移動
			Reset();					// ゲーム内容をリセットにする
		}
		break;
	case 1:
		// 何を選択しているかわかるように四角を視覚化
		DrawBox(TITLETEXT_X[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD], TITLETEXT_X[TITLE_ROAD] + titleTextW[TITLE_ROAD], TITLETEXT_Y[TITLE_ROAD] + titleTextH[TITLE_ROAD], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_SELECT;	// ゲームセレクトへ移動
			// ↑本当はロードするデータを選択してロードし終えてゲームセレクトへ移動
		}
		break;
	case 2:
		// 何を選択しているかわかるように四角を視覚化
		DrawBox(TITLETEXT_X[TITLE_END], TITLETEXT_Y[TITLE_END], TITLETEXT_X[TITLE_END] + titleTextW[TITLE_END], TITLETEXT_Y[TITLE_END] + titleTextH[TITLE_END], 0xFF0000, FALSE);
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			g_gameScene = GAME_END;		// ゲーム終了
		}
		break;
	default:
		break;
	}

	
}

void TitleSound() {
	
}

// タイトルでの動き
void TitleMove() {
	

	RainMove();


	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {	// 一番下で下をもう一度押すと上に戻る
		if (++g_selectCheck > 2) g_selectCheck = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {		// 一番上で上をもう一度押すと、下に行く
		if (--g_selectCheck < 0) g_selectCheck = 2;
	}


	

}