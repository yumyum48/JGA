#pragma once

#include "DxLib.h"

// �}�E�X�̓��͏��
struct mouse {
    int mouseX, mouseY;
    int oldMouse, nowMouse, MouseFlg;
};

// �L�[�{�[�h�̓��͏��
struct key {
    int oldKey, nowKey, keyFlg;
};

// �摜�̎��
struct image {
    int Block;
    int QBlock;
    int Kirby;
    int map[2];

};

// �v���C���[�̏��
struct playerInfo {
    int x, y;
    int jumpFlg;

};

// �}�b�v�̏��
struct mapInfo {
    int x, y;
    int obj[];
};