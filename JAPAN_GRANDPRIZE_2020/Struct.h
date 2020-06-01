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
    int titleText[4];                   // �^�C�g���̃e�L�X�g�摜
    int player[56];                     // �v���C���[�̉摜
    int SkillMotion[12];                 //�X�L�����[�V�����摜
    int enemy_walk[4];                  // �����G���G�̂̉摜
    int enemy_fly[4];                   // ��ԎG���G�̉摜
    int map[MAP_MAX * SCROLL_MAX];      // �}�b�v�̉摜
    int backMap[MAP_MAX * SCROLL_MAX];  // �}�b�v�̔w�i
    int rain;                           // �J�̉摜
    int reticle;                        // �G�����b�N�I���������̉摜(���e�B�N���摜)
    int PlayerUI;                       //player��UI�摜
    int Life[2];                        //player��HP�摜
    int boss_1_1[16];                   // �{�X_�P�̉摜
    int boss_2_1[9];                    // �{�X_�Q�̉摜
    int boss_3_1[5];                    // �{�X_�R�̉摜
    //int skill2[4];                      //�X�L��2�̃��[�V�����摜(��)
    //int skill3[5];                      //�X�L��3�̃��[�V�����摜(��)
    int skillEffect[40];                //�X�L���G�t�F�N�g�摜
    int selectBack;                     // �Z���N�g��ʂ̔w�i�摜
    int waterBullet[5];                 // �{�X�̐��e�̉摜
    int bossTongue;                     // �{�X�R�̐�̉摜
    int trap;                           // �g���b�v�̉摜
    int gauge;                          // �Q�[�W�̉摜
    int enemyVapour[5];                 // �G���j���̏��C�̉摜
    int enemySplashes[5];               // �G���a�������̐����Ԃ��̉摜
    int stageClearText;                 // �X�e�[�W���N���A��������[��������]�̕���
    int gameOverText;                   // �Q�[���I�[�o�[�̎���[�������s]�̕���
    int skillAicon[8];                  // skill�̃A�C�R��
    int skillRing[2];                   // skill�̑���
    int skilChoiceBox;                  //skillcustom�̑I��
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
    float gauge;      //�Q�[�W
    bool swordFlg; //TRUE = ����, FALSE = �[��
    int timecount; //�[�������̐؂�ւ��̎���
    bool useSkillFlg;   //�X�L�����g���Ƃ��ɔ[����Ԃ�������Ԃ� TRUE = ����, FALSE = �[��
    bool barrierFlg;    //�X�L��6 �o���A�̃t���O TRUE = �o���A�L, FALSE = �o���A��
    bool powerUpFlg;    //�X�L��5 �Η͏㏸�t���O TRUE = ON, FALSE = OFF
    int powerUpTime;    //�X�L��5 �Η͏㏸����
    int useSkillGage;   //�����X�L���Q�[�W�̗�
    float skillCoolTime[3];  //�X�L���Ďg�p�̃N�[���^�C���i�[
    int skillNo; //�g�p�����������̃X�L���̔z��ԍ�
    void Init();   // �v���C���[�̏�����//Player.cpp�̈�ԉ�������Œ�`

};

// �G�̏��
struct enemyInfo {

    int x = 574 * 0.2;                       // �G��X���W�̏����ʒu
    int y = GROUND - (545 * 0.5);            // �G��Y���W�̏����ʒu
    int flg = FALSE;                         // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
    int anime = 0;                           // �A�j���[�V�����̏�����
    
    void WalkInit();                 // �����G�̏�����

    void FlyInit();                  // ��ԓG�̏�����

    void BossArea_WlakInit(int bx, int by);
    void BossArea_CloudInit(int bx, int by);   //�@�{�X�G���A�̃~�j�_�̏�����
    void BossArea_SpiderInit(int bx, int by);   //�@�{�X�G���A�̃~�j�w偂̏�����
    void BufferAssignment(int ex, int ey) {
        x = ex;
        y = ey;
        flg = TRUE;
    }
    void BufferInit() {
        x = 0;
        y = 0;
        flg = FALSE;
    }
};

struct enemyType {      // �G�̎��
    enemyInfo fly;      // ��ԓG
    enemyInfo walk;     // �����G
    enemyInfo cloud;    // �_
    enemyInfo spider;   // �w�
};

struct bossInfo {     // �{�X�̏��
    int hp;           // �̗�
    int x, y;         // ���W
    int popflg;       // ��ʂɂ��邩���Ȃ����A�Ƃǂ߂��h���邩�ǂ����̃t���O
    int attackFlg;   // �U�������ǂ����̃t���O(�����̋Z�𕪂��邽�߁Aint�^�@��:== 1 �Ȃ�΁B�B�B == 2 �Ȃ�΁B�B�B)

    // �z��ŏ������ł���킱��|
    void Init_Stage(int num) {

        switch (num) {  // �{�X�̏�����
        case 0:         // �X�e�[�W�P�̃{�X��������
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 1:         // �X�e�[�W�Q�̃{�X��������
            hp = 10;
            x = 823;
            y = 397;
            popflg = 0;
            attackFlg = 0;
            break;
        case 2:         // �X�e�[�W�R�̃{�X��������
            hp = 10;
            x = 822;
            y = GROUND - 128 * 3.5;
            popflg = 0;
            attackFlg = 0;
            break;
        case 3:         // �X�e�[�W�S�̃{�X��������
            hp = 10;
            x = 843;
            y = 45 + 286;
            popflg = 0;
            attackFlg = 0;
            break;
        case 4:         // �X�e�[�W�T�̃{�X��������
            hp = 10;
            x = 808;
            y = 134;
            popflg = 0;
            attackFlg = 0;
            break;
        case 5:         // �X�e�[�W�U�̃{�X��������
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 6:         // �X�e�[�W�V�̃{�X��������
            hp = 10;
            x = 872;
            y = 160;
            popflg = 0;
            attackFlg = 0;
            break;
        case 7:         // �X�e�[�W�W�̃{�X��������
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
    void WaveInit(float bossX) {
        x = bossX;
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
    int x;          // X���W
    int y;          // Y���W
    int w;          // ��
    int h;          // ����
    picInfo() {     // �R���g���X�^�ɂ�鏉����
        x = 0;
        y = 0;
        w = 0;          
        h = 0;          
    }
    /*void Boss3_TonInit() {  // �{�X�R�̐�̏�����
        x = 819;
        y = 440;
        
    }*/
    void Boss3_TonInit(int bossX, int bossY) {  // �{�X�R�̐�̏�����
        x = bossX + 100;
        y = bossY;

    }
    void Boss4_CloudInit() {    // �{�X�S�̉_�̏�����
        x = 868;
        y = 36;
        w = x + 265;    // ���W��X�`�ɂ���
        h = y + 134;    // ���W��Y�`�ɂ���

    }
    void Boss4_ThreadInit() {
        x = 995;
        y = 170;
        w = x + 6;    // ���W��X�`�ɂ���
        h = y + 162;    // ���W��Y�`�ɂ���

    }
    void MenuWindowInit() {     // ���j���[��ʂ̏�����
        x = 1182; 
        y = 39;
    }
    void MenuSaveWindowInit() { // �Z�[�u��ʂ̏�����
        x = 1280;
        y = 39;
    }
    void SelectStageInit(int num) { // �Z���N�g��ʂ̏�����
        switch (num) {
        /*case 0: 
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
            break;*/

        case 0:  x = 217; y = 99;  break;
        case 1:  x = 558; y = 129; break;
        case 2:  x = 926; y = 178; break;
        case 3:  x = 689; y = 310; break;
        case 4:  x = 451; y = 381; break;
        case 5:  x = 224; y = 506; break;
        case 6:  x = 508; y = 563; break;
        case 7:  x = 826; y = 499; break;
        default: x = 0;   y = 0;   break;

        }
    };
};