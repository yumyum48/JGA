#pragma once

#include "DxLib.h"
#include "Map.h"

#define ENEMY_MAX 10
#define GROUND 450

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
    int player[10];
    int enemy;
    int map[MAP_MAX * SCROLL_MAX];
    int rain[2];

};

// プレイヤーの情報
struct playerInfo {
    int x, y;
    int hp;
    bool jumpFlg;
    bool attackFlg;

    void Init() { x = 100; y = GROUND; hp = 100; }

};

// 敵の情報
struct enemyInfo {
    int x = 1280;
    int y = 600;

    void Init() { x = 1280; y = GROUND; }

};
// マップの情報
struct mapInfo {
    float x, y;
    void MapInit1() {
        x = 0;
        y = 0;
    }
    void MapInit2() {
        x = 1024;
        y = 0;
    }
    void MapInit3() {
        x = 2048;
        y = 0;
    }
};

// 雨の情報
struct rainInfo {
    int x, y;
    void RainInit1() {
        x = 0;
        y = -768;
    }
};