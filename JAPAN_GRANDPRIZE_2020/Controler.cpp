

#include "DxLib.h"
#include "Controler.h"
#include "Struct.h"


int ControlerCheck(void) {

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &g_controler);

	// 二重反応対策変数
	static int squarFlg = 0;
	static int crossFlg = 0;
	static int circleFlg = 0;
	static int triangleFlg = 0;
	//プレイヤー１のボタン判定
	// □ボタン
	if (g_controler.Buttons[0] == 128 && squarFlg == 0) {
		g_button.squareButton = true;
		squarFlg = 1;
	}
	else{
		g_button.squareButton = false;
		g_controler.Buttons[0] == 0 ? squarFlg = 0 : squarFlg = 1;			// 二重反応防止
	}

	// Xボタン
	if (g_controler.Buttons[1] == 128 && crossFlg == 0) {
		g_button.crossButton = true;
		crossFlg = 1;
	}
	else {
		g_button.crossButton = false;
		g_controler.Buttons[1] == 0 ? crossFlg = 0 : crossFlg = 1;			// 二重反応防止
	}

	// 〇ボタン
	if (g_controler.Buttons[2] == 128 && circleFlg == 0) {
		g_button.circleButton = true;
		circleFlg = 1;
	}
	else {
		g_button.circleButton = false;
		g_controler.Buttons[2] == 0 ? circleFlg = 0 : circleFlg = 1;		// 二重反応防止
	}

	// △ボタン
	if (g_controler.Buttons[3] == 128 && triangleFlg == 0) {
		g_button.triangleButton = true;
		triangleFlg = 1;
	}
	else {
		g_button.triangleButton = false;
		g_controler.Buttons[0] == 0 ? triangleFlg = 0 : triangleFlg = 1;	// 二重反応防止
	}
	//プレイヤー１のスティック判定
	if (g_controler.Y < 0
		&& g_controler.X >= -200
		&& g_controler.X <= 200) {
		g_button.moveStick = 1;		//上向き
	}
	else if (g_controler.X > 0
		&& g_controler.Y >= -200
		&& g_controler.Y <= 200) {
		g_button.moveStick = 3;		//右
	}
	else if (g_controler.Y > 0
		&& g_controler.X >= -200
		&& g_controler.X <= 200) {
		g_button.moveStick = 5;		//下
	}
	else if (g_controler.X < 0
		&& g_controler.Y >= -200
		&& g_controler.Y <= 200) {
		g_button.moveStick = 7;		//左
	}
	else if (g_controler.Y < 0
		&& g_controler.X > 0) {
		g_button.moveStick = 2;		//右上
	}
	else if (g_controler.Y > 0
		&& g_controler.X > 0) {
		g_button.moveStick = 4;		//右下
	}
	else if (g_controler.X < 0
		&& g_controler.Y > 0) {
		g_button.moveStick = 6;		//左下
	}
	else if (g_controler.X < 0
		&& g_controler.Y < 0) {
		g_button.moveStick = 8;		//左上
	}
	else {
		g_button.moveStick = 0;		//
	}

	return 0;
}