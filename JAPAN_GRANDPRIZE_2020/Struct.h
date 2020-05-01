#pragma once

#include "DxLib.h"
#include "Map.h"
#include "Macro.h"
//#include "Player.h"



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
    int player[56];                 // プレイヤーの画像
    int enemy;                      // エネミーの画像
    int map[MAP_MAX * SCROLL_MAX];  // マップの画像
    int backMap;                    // マップの背景
    int rain;                        // 雨の画像
    int reticle;                    // 敵をロックオンした時の画像(レティクル画像)
    int PlayerUI;                   //playerのUI画像
    int Life[2];                    //playerのHP画像

};

// プレイヤーの情報
struct playerInfo {
    int x, y;       // プレイヤーのX,Y座標
    int hp;         // プレイヤーのHP
    int skillGage;  // スキルのゲージ
    int skillFlg;   // スキルのフラグ(0:何もしない 1:スキル１　2:スキル２...)
    int skill_MAX; // 使用可能スキル(0:何もしない 1:スキル１　2:スキル２...)
    bool jumpFlg;   // ジャンプフラグ
    bool attackFlg; // 攻撃しているかどうかのフラグ
    void Init() {   // プレイヤーの初期化
        x = 100 * PLAYER_REDUCTION;
        y = 490;
        hp = 3;
        attackFlg = FALSE;
        jumpFlg = FALSE;
        skillFlg = 0;
        skillGage = 100;
        skill_MAX = 1;
    }

};

// 敵の情報
struct enemyInfo {

    int x = 1000;
    int y = GROUND + 30;
    bool flg;
    void WalkInit() {   // 敵の初期化
        x = 1280;     // 敵のX座標の初期位置
        y = GROUND + 30;   // 敵のY座標の初期位置
        flg = FALSE;  // 敵を表示しているかどうかのフラグ TRUE:表示している FALSE:表示していない
    }
    void FlyInit() {
        x = 1280;     // 敵のX座標の初期位置
        y = GROUND - 30;   // 敵のY座標の初期位置
        flg = FALSE;  // 敵を表示しているかどうかのフラグ TRUE:表示している FALSE:表示していない
    }

};

struct enemyType {  // 敵の種類
    enemyInfo fly;  // 飛ぶ敵
    enemyInfo walk; // 歩く敵

};

struct bossInfo {     // ボスの情報
    int hp;           // 体力
    int x, y;         // 座標
    int popflg;       // 画面にいるかいないか、とどめを刺せるかどうかのフラグ
    int attackFlg;   // 攻撃中かどうかのフラグ(複数個の技を分けるため、int型　例:== 1 ならば。。。 == 2 ならば。。。)

    void Init_Stage1() {
        hp = 3;
        x = 872;
        y = 160;
        popflg = 0;
        attackFlg = 0;
    }
};

struct bossType {     // ボスの種類
    bossInfo stage1;  // ステージ１のボス
    bossInfo stage2;  // ステージ２のボス
};

// マップの情報
struct mapInfo {
    float x, y; // マップのX,Y座標
    void MapInit1() {   // スクロール１の座標
        x = 0*2;
        y = 0;
    }
    void MapInit2() {   // スクロール２の座標
        x = 250*2;
        y = 0;
    }
    void MapInit3() {   // スクロール３の座標
        x = 500*2;
        y = 0;
    }
    void MapInit4() {   // スクロール４の座標
        x = 750*2;
        y = 0;
    }
};
// トラップの情報
struct trapInfo {

    int x, y;
    bool dispFlg;	// トラップを出現させるかどうかのフラグ	TRUE: 出現させる FALSE: 出現させない
    void Init() {
        x = 1300;
        y = 510;
        dispFlg = FALSE;
    }
};
// 雨の情報
struct rainInfo {
    int x, y;           // X,Y座標
    void RainInit1() {  // 初期化
        x = 0;
        y = -768;
    }
};

// スクロール速度の低下に関する情報
struct slowInfo {
    float mag; // スクロール速度
    float rainMag; // 雨のスクロール速度
    int playerAnime; // アニメーション速度
    void StandardMagInit() { // 初期化
        mag = 1.0;
        rainMag = 1.0;
        playerAnime = 4;
    }
    void SlowMagDown() { // スクロール速度の低下
        mag = 0.4;
        playerAnime = 20;
    }
    void RainSpeedDowm() { // 雨のスクロール速度の低下
        rainMag = 0.6;
    }
};