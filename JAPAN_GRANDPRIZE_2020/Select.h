#pragma once

void StageSelect();				// ステージのセレクト処理
void SelectDisp();				// ステージのセレクトの表示処理
void SelectMove();				// ステージのセレクトの動きの処理
void SpeedSelect();				// ステージのセレクトの動きの処理
void SelectInit();				// セレクト画面の初期化
void MenuSelectOper();			// メニュー一覧のカーソルを移動させる
void MenuScrollOut();			// メニュー画面を画面端付近に操作させる
void StageSelectOper();			// ステージの決定のためのカーソルを操作させる
void MenuScrollIn();			// メニュー画面を見えるように画面中央付近まで移動させる
void MenuSelect();				// メニュー画面で決定を押すことでセーブ画面、スキルカスタマイズ画面、タイトル画面へ移動できるようにする
extern int g_select_Stage;		//ステージをセレクト
extern int g_speedLevel;		//スクロール速度の選択
extern int g_select_MAX;			// 今プレイヤーがいけるステージを制御する(中の数字が0なら1ステージを指しています。(添え字ずれしてます。))

enum { // スクロール速度
	SPEED_EASY = 10,
	SPEED_NORMAL = 12,
	SPEED_HARD = 15,
};