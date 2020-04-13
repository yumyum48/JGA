#pragma once

#include "DxLib.h"
#include "Map.h"

#define ENEMY_MAX 10
#define GROUND 450

// �}�E�X�̓��͏��
struct mouse {
    int mouseX, mouseY;
    int oldMouse, nowMouse, MouseFlg;
};

// �L�[�{�[�h�̓��͏��
struct key {
    int oldKey, nowKey, keyFlg;
};

// �R���g���[���[�̍\����
struct controler {
    bool circleButton, crossButton, squareButton, triangleButton;
    int moveStick;
    int nowCon, oldCon, conFlg;	// �{�^���̉����Ă��邩�̃t���O

};

// �摜�̎��
struct image {
    int Block;
    int QBlock;
    int player[10];
    int enemy;
    int map[MAP_MAX * SCROLL_MAX];
    int rain[2];

};

// �v���C���[�̏��
struct playerInfo {
    int x, y;
    int hp;
    bool jumpFlg;
    bool attackFlg;

    void Init() { x = 100; y = GROUND; hp = 100; }

};

// �G�̏��
struct enemyInfo {
    int x = 1280;
    int y = 600;

    void Init() { x = 1280; y = GROUND; }

};
// �}�b�v�̏��
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

// �J�̏��
struct rainInfo {
    int x, y;
    void RainInit1() {
        x = 0;
        y = -768;
    }
};