#pragma once

#include "DxLib.h"
#include "Map.h"

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
    int Kirby;
    int map[MAP_MAX * SCROLL_MAX];

};

// �v���C���[�̏��
struct playerInfo {
    int x, y;
    bool jumpFlg;

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