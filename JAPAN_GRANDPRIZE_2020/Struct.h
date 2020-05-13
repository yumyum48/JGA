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
    int title[2];                       // タイトル画像
    int titleText[2];                      // タイトルのテキスト画像
    int player[56];                     // プレイヤーの画像
    int enemy_walk[2];                  // 歩く雑魚敵のの画像
    int enemy_fly[2];                   // 飛ぶ雑魚敵の画像
    int map[MAP_MAX * SCROLL_MAX];      // マップの画像
    int backMap[MAP_MAX * SCROLL_MAX];  // マップの背景
    int rain;                           // 雨の画像
    int reticle;                        // 敵をロックオンした時の画像(レティクル画像)
    int PlayerUI;                       //playerのUI画像
    int Life[2];                        //playerのHP画像
    int boss_1_1[8];                    // ボス_１の画像
    int skill[5];                       //スキル3のモーション画像(仮)
    int selectBack;                     // セレクト画面の背景画像
    int waterBullet[5];                 // ボスの水弾の画像
    int trap;                           // トラップの画像


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
    int skillcustom[3]; // 装備中のスキル取得
    void Init() {   // プレイヤーの初期化
        x = 100 * PLAYER_REDUCTION;
        y = GROUND;
        hp = 3;
        attackFlg = FALSE;
        jumpFlg = FALSE;
        skillFlg = 0;
        skillGage = 100;
        skill_MAX = 3;
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

    void Init_Stage(int num) {
        switch (num) {
        case 0:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 1:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 2:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 3:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 4:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 5:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 6:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 7:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 8:
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        }

    };
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
        y = 574;
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

struct picInfo {
    int x;          //X座標
    int y;          //Y座標
    void MenuWindowInit() {     // メニュー画面の初期化
        x = 1182; 
        y = 39;
    }
    void SelectStageInit(int num) { // セレクト画面の初期化
        switch (num) {
        case 0: 
            x = 217;
            y = 599;
            break;
        case 1:
            x = 547;
            y = 563;
            break;
        case 2:
            x = 926;
            y = 506;
            break;
        case 3:
            x = 689;
            y = 381;
            break;
        case 4:
            x = 451;
            y = 310;
            break;
        case 5:
            x = 224;
            y = 178;
            break;
        case 6:
            x = 508;
            y = 69;
            break;
        case 7:
            x = 826;
            y = 69;
            break;
        default:
            x = 0;
            y = 0;
            break;
            
        }
    };
};