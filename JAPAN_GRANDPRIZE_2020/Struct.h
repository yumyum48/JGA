#pragma once

#include "DxLib.h"

// マウスの入力状態
struct mouse {
    int mouseX, mouseY;
    int oldMouse, nowMouse, MouseFlg;
};

// キーボードの入力状態
struct key {
    int oldKey, nowKey, keyFlg;
};

// コントローラーの構造体
struct controler {
    bool circleButton, crossButton, squareButton, triangleButton;
    int moveStick;
    int nowCon, oldCon, conFlg;	// ボタンの押しているかのフラグ

};

// 画像の種類
struct image {
    int Block;
    int QBlock;
    int Kirby;
    int map[2];

};

// プレイヤーの情報
struct playerInfo {
    int x, y;
    bool jumpFlg;

};

// マップの情報
struct mapInfo {
    int x, y;
    int obj[];
};