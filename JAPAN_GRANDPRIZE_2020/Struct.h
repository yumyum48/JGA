#pragma once

#include "DxLib.h"
#include "Map.h"
#include "Macro.h"
//#include "Player.h"



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
    int title[2];                       // �^�C�g���摜
    int titleText[2];                      // �^�C�g���̃e�L�X�g�摜
    int player[56];                     // �v���C���[�̉摜
    int enemy_walk[2];                  // �����G���G�̂̉摜
    int enemy_fly[2];                   // ��ԎG���G�̉摜
    int map[MAP_MAX * SCROLL_MAX];      // �}�b�v�̉摜
    int backMap[MAP_MAX * SCROLL_MAX];  // �}�b�v�̔w�i
    int rain;                           // �J�̉摜
    int reticle;                        // �G�����b�N�I���������̉摜(���e�B�N���摜)
    int PlayerUI;                       //player��UI�摜
    int Life[2];                        //player��HP�摜
    int boss_1_1[8];                    // �{�X_�P�̉摜
    int skill[5];                       //�X�L��3�̃��[�V�����摜(��)
    int selectBack;                     // �Z���N�g��ʂ̔w�i�摜
    int waterBullet[5];                 // �{�X�̐��e�̉摜
    int trap;                           // �g���b�v�̉摜


};

// �v���C���[�̏��
struct playerInfo {
    int x, y;       // �v���C���[��X,Y���W
    int hp;         // �v���C���[��HP
    int skillGage;  // �X�L���̃Q�[�W
    int skillFlg;   // �X�L���̃t���O(0:�������Ȃ� 1:�X�L���P�@2:�X�L���Q...)
    int skill_MAX; // �g�p�\�X�L��(0:�������Ȃ� 1:�X�L���P�@2:�X�L���Q...)
    bool jumpFlg;   // �W�����v�t���O
    bool attackFlg; // �U�����Ă��邩�ǂ����̃t���O
    int skillcustom[3]; // �������̃X�L���擾
    void Init() {   // �v���C���[�̏�����
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

// �G�̏��
struct enemyInfo {

    int x = 1000;
    int y = GROUND + 30;
    bool flg;
    void WalkInit() {   // �G�̏�����
        x = 1280;     // �G��X���W�̏����ʒu
        y = GROUND + 30;   // �G��Y���W�̏����ʒu
        flg = FALSE;  // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
    }
    void FlyInit() {
        x = 1280;     // �G��X���W�̏����ʒu
        y = GROUND - 30;   // �G��Y���W�̏����ʒu
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
    int attackFlg;   // �U�������ǂ����̃t���O(�����̋Z�𕪂��邽�߁Aint�^�@��:== 1 �Ȃ�΁B�B�B == 2 �Ȃ�΁B�B�B)

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

struct bossType {     // �{�X�̎��
    bossInfo stage1;  // �X�e�[�W�P�̃{�X
    bossInfo stage2;  // �X�e�[�W�Q�̃{�X
};

// �}�b�v�̏��
struct mapInfo {
    float x, y; // �}�b�v��X,Y���W
    void MapInit1() {   // �X�N���[���P�̍��W
        x = 0*2;
        y = 0;
    }
    void MapInit2() {   // �X�N���[���Q�̍��W
        x = 250*2;
        y = 0;
    }
    void MapInit3() {   // �X�N���[���R�̍��W
        x = 500*2;
        y = 0;
    }
    void MapInit4() {   // �X�N���[���S�̍��W
        x = 750*2;
        y = 0;
    }
};
// �g���b�v�̏��
struct trapInfo {

    int x, y;
    bool dispFlg;	// �g���b�v���o�������邩�ǂ����̃t���O	TRUE: �o�������� FALSE: �o�������Ȃ�
    void Init() {
        x = 1300;
        y = 574;
        dispFlg = FALSE;
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

// �X�N���[�����x�̒ቺ�Ɋւ�����
struct slowInfo {
    float mag; // �X�N���[�����x
    float rainMag; // �J�̃X�N���[�����x
    int playerAnime; // �A�j���[�V�������x
    void StandardMagInit() { // ������
        mag = 1.0;
        rainMag = 1.0;
        playerAnime = 4;
    }
    void SlowMagDown() { // �X�N���[�����x�̒ቺ
        mag = 0.4;
        playerAnime = 20;
    }
    void RainSpeedDowm() { // �J�̃X�N���[�����x�̒ቺ
        rainMag = 0.6;
    }
};

struct picInfo {
    int x;          //X���W
    int y;          //Y���W
    void MenuWindowInit() {     // ���j���[��ʂ̏�����
        x = 1182; 
        y = 39;
    }
    void SelectStageInit(int num) { // �Z���N�g��ʂ̏�����
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