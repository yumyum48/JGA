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
    int map[2];

};

// �v���C���[�̏��
struct playerInfo {
    int x, y;
    bool jumpFlg;

};

// �}�b�v�̏��
struct mapInfo {
    int x, y;
    int obj[];
};