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
    int jumpFlg;

};

// マップの情報
struct mapInfo {
    int x, y;
    int obj[];
};