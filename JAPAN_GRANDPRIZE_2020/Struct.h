#pragma once

#include "DxLib.h"
#include "Map.h"

#define ENEMY_MAX 5
#define GROUND 450
#define PLAYER_WIDTH	 (280)		// �v���C���[�̉���
#define PLAYER_HEIGHT	 (200)		// �v���C���[�̏c��
#define ENEMY_WIDTH		 (574 * 0.5)// �G�l�~�[�̉���
#define ENEMY_HEIGHT	 (545 * 0.5)// �G�l�~�[�̏c��

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
    int Block;                      // ��
    int QBlock;                     // ��
    int player[16];                 // �v���C���[�̉摜
    int enemy;                      // �G�l�~�[�̉摜
    int map[MAP_MAX * SCROLL_MAX];  // �}�b�v�̉摜
    int rain[2];                    // �J�̉摜

};

// �v���C���[�̏��
struct playerInfo {
    int x, y;       // �v���C���[��X,Y���W
    int hp;         // �v���C���[��HP
    bool jumpFlg;   // �W�����v�t���O
    bool attackFlg; // �U�����Ă��邩�ǂ����̃t���O

    void Init() {   // �v���C���[�̏�����
        x = 100; 
        y = GROUND; 
        hp = 100;
    }

};

// �G�̏��
struct enemyInfo {
    int x;
    int y;
    bool flg;
    void Init() {   // �G�̏�����
        x = 1280;     // �G��X���W�̏����ʒu
        y = GROUND;   // �G��Y���W�̏����ʒu
        flg = FALSE;  // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
    }

};

struct enemyType {  // �G�̎��
    enemyInfo fly;  // ��ԓG
    enemyInfo walk; // �����G

};

struct bossInfo {     // �{�X�̏��
    int hp;           // �̗�
    int x, y;         // ���W
    int popflg;       // ��ʂɂ��邩���Ȃ����A�Ƃǂ߂��h���邩�ǂ����̃t���O
    bool attackFlg;   // �U�������ǂ����̃t���O
};

struct bossType {
    bossInfo stage1;  // �X�e�[�W�P�̃{�X
    bossInfo stage2;  // �X�e�[�W�Q�̃{�X
};
// �}�b�v�̏��
struct mapInfo {
    float x, y; // �}�b�v��X,Y���W
    void MapInit1() {   // �X�N���[���P�̍��W
        x = 0;
        y = 0;
    }
    void MapInit2() {   // �X�N���[���Q�̍��W
        x = 1024;
        y = 0;
    }
    void MapInit3() {   // �X�N���[���R�̍��W
        x = 2048;
        y = 0;
    }
};

// �J�̏��
struct rainInfo {
    int x, y;           // X,Y���W
    void RainInit1() {  // ������
        x = 0;
        y = -768;
    }
};