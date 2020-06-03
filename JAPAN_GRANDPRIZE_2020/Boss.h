#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"

/***********************************************************

// �}�N���̒�`

***********************************************************/
#define BOSS_WIDTH			(280 * 2)		// �{�X�̉���
#define BOSS_HEIGHT			(200 * 2)		// �{�X�̏c��
#define BOSS_AREA_ENEMY_MAX (3)				// �{�X��̃G�l�~�[���o������ő吔
#define BOSS_STAGE2_WIDTH (271)		// �{�X�̉���
#define BOSS_STAGE2_HEIGHT (271)	// �{�X�̏c��
#define BOSS_STAGE3_WIDTH  (128 * 3.5)// �{�X�̉���
#define BOSS_STAGE3_HEIGHT (128 * 3.5)// �{�X�̏c��
#define BOSS_STAGE4_WIDTH  (314)
#define BOSS_STAGE4_HEIGHT (286)
#define BOSS_STAGE5_WIDTH  (324)
#define BOSS_STAGE5_HEIGHT (415)

/***********************************************************

// �萔�̐錾

***********************************************************/
const int BOSSFULL_WIDTH[MAP_MAX] = {BOSS_WIDTH, BOSS_STAGE2_WIDTH, BOSS_STAGE3_WIDTH, BOSS_STAGE4_WIDTH, BOSS_STAGE5_WIDTH };
const int BOSSFULL_HEIGHT[MAP_MAX] = { BOSS_HEIGHT, BOSS_STAGE2_HEIGHT, BOSS_STAGE3_HEIGHT, BOSS_STAGE4_HEIGHT, BOSS_STAGE5_HEIGHT};
/***********************************************************

// �񋓑̂̐錾

***********************************************************/
enum {	// �{�X�̔z��
	BOSS_STAGE1,
	BOSS_STAGE2,
	BOSS_STAGE3,
	BOSS_STAGE4,
	BOSS_STAGE5,
	BOSS_STAGE6,
	BOSS_STAGE7,
	BOSS_STAGE8,
	BOSS_MAX,
};

enum {	// �{�X�̍U�����f
	BOSSATTACK_ENEMY_DROP = 1,			// �G���G�̐���
	BOSSATTACK_WATER_BULLET,			// ���e�ł̍U��
	BOSSATTACK_WAVE_ATTACK,				// �Ôg�ł̍U��
	BOSSATTACK_JUMPANDPOISON,			// �J�G���̃W�����v�ƋH�ɓł��o���U��
	BOSSATTACK_LONGTON,					// ���L�΂��U��
	BOSSATTACK_MINISPIDER_DROP,			// �~�j�X�p�C�_�[���h���b�v����
	BOSSATTACK_MINICLOUD_DROP,			// �~�j�_���h���b�v����
	BOSSATTACK_LIGHTNING,				// �����ɂ��U��
	BOSSATTACK_POISON_TRAP,				// �ł̃g���b�v��ݒu
	BOSSATTACK_MINIKURAGE_AIR,			// �󒆂̃~�j�N���Q�̍U��(Boss_MiniKurage_Drop�֐����{�X�ɓ���Ȃ��Ǝg���Ȃ�)
	BOSSATTACK_MINIKURAGE_GROUND,		// �n��̃~�j�N���Q�̍U��(Boss_MiniKurage_Drop�֐����{�X�ɓ���Ȃ��Ǝg���Ȃ�)
	BOSSATTACK_TACKLE,					// �{�X�̃^�b�N���U��
};

enum { // �{�X�̓����p�^�[��
	BOSSMOVE_NOMOTION,		// �m�[���[�V����
	BOSSMOVE_ATTACK,		// �{�X��Sin�g�ōU�߂Ă���
	BOSSMOVE_SPEEDDOWN,		// �{�X���v���C���[�ɒǂ�����铮��
};

enum {	// �{�X�R�̃W�����v�t���O����
	BOSS_3_JUMPOFF,
	BOSS_3_JUMPON,
	BOSS_3_DOWN,
};
struct boss4_parts :public picInfo {	//�{�X�S�̉_�Ǝ��̏�� 
	int hp;
	void ThreadInit() {
		Boss4_ThreadInit();
		hp = 5;
	}

};
struct bossAttackInfo {	// �{�X�̍U���̍ۂɎg���\������
	int x, y;

};
/***********************************************************

// �O���[�o���ϐ��̐錾

***********************************************************/
extern bossInfo g_boss[MAP_MAX];		// �{�X�̏��
extern boss4_parts g_boss4_Cloud;		// �{�X�S�̉_�̏��
extern boss4_parts g_boss4_Thread;		// �{�X�S�̎��̏��
/***********************************************************

// �֐��̐錾

***********************************************************/
int InputRand(int rand1, int rand2, int rand3);	// �����������Ƃ��ĎO���A���̒��̈�������_���ŕԂ�
bool BossDamageCheck(int bossHp);				// �{�X���_���[�W���󂯂����ǂ����𒲂ׂ�֐� TRUE: �{�X���_���[�W���󂯂� FALSE: �{�X�̓_���[�W���󂯂Ă��Ȃ�
bool BossNoAttackCheck(int bossAttackFlg);		// �{�X���U�����I�������𒲂ׂ�֐�TRUE: �{�X�̍U���I�� FALSE: �{�X�͍U�����A�܂��͏I�����Ă��΂炭�����Ă���
bool BossDropAttackCheck(int bossAttackFlg);	// �{�X���G�l�~�[���h���b�v���邩�𒲂ׂ�֐�TRUE: �{�X�̍U���J�n FALSE: �{�X�͍U�����A�܂��͏I�����Ă��΂炭�����Ă���
void Boss_MiniKurage_DropFlg();					// �~�j�N���Q���o���t���O�Ǘ�
void KurageHit();								// �v���C���[���N���Q�ɓ�����ƃ_���[�W���󂯂�

void BossDisp_Stage1();					// �X�e�[�W�P�̃{�X�̕\��
void BossMove_Stage1();					// �X�e�[�W�P�̃{�X�̓���
void BossDisp_Stage2();					// �X�e�[�W�Q�̃{�X�̕\��
void BossMove_Stage2();					// �X�e�[�W�Q�̃{�X�̓���
void BossDisp_Stage3();					// �X�e�[�W�R�̃{�X�̕\��
void BossMove_Stage3();					// �X�e�[�W�R�̃{�X�̓���
void BossDisp_Stage4();					// �X�e�[�W�S�̃{�X�̕\��
void BossMove_Stage4();					// �X�e�[�W�S�̃{�X�̓���
void BossDisp_Stage5();					// �X�e�[�W�T�̃{�X�̕\��
void BossMove_Stage5();					// �X�e�[�W�T�̃{�X�̓���
void Boss_Knock_Down();					// �{�X�̓����蔻��

void BossInit();						// �{�X�̏�����
void Boss_Stage4_Init();				// �{�X�S�̉_�̏�����
void Boss5_Init();						// �{�X�T�̏�����

void BossAttackDisp();					// �{�X�̍U��
void BossAttackMove();					// �{�X�̍U��

// �{�X�̃X�L���̕\��
void BossEnemyDropDisp();				// �ア�G���o���{�X��p�̋Z�̊֐�
void BossWaterBulletDisp();				// ���e�ōU������{�X��p�̋Z�̊֐�
// �{�X�̃X�L���̓���
void BossEnemyDropMove();				// �ア�G���o���{�X��p�̋Z�̊֐�
void BossMoveMotion(int *coolTime, int *moveFlg);		//
void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg);	// �{�X�P�̌����[�V����
void BossMoveMotion_Pattern2(int* coolTime, int* moveFlg);	// �{�X�Q�̌����[�V����
void BossWaterBulletMove();				// ���e�ōU������{�X��p�̋Z�̊֐�
void BossAreaEnemyMove();				// �{�X���o�����Ă���Ƃ��̎G���̓���
void BossAreaEnemyDisp();				// �{�X���o�����Ă���Ƃ��̎G���̕\��
void BossGenerateWave();				// �{�X���Ôg�𔭐������čU��
void BossJumpOrPoison_Disp();			// �{�X���W�����v���ċH�ɓł��o���\��		
void BossJumpOrPoison_Move();			// �{�X���W�����v���ċH�ɓł��o������
void BossLongTon_Disp();				// �{�X�����L�΂��čU������U���̕\��
void BossLongTon_Move();				// �{�X�����L�΂��čU�����铮��
void Boss_MiniSpider_Drop_Disp();		// �~�j�w偂��o���U���̕\��
void Boss_MiniSpider_Drop_Move();		// �~�j�w偂��o���U���̓���
void Boss_MiniCloud_Drop_Disp();		// �~�j�_���o���U���̕\��
void Boss_MiniCloud_Drop_Move();		// �~�j�_���o���U���̓���
void Boss_Lightning_Disp();				// �����̕\��
void Boss_Lightning_Move();				// �����̓���
void Poison_Trap_Disp();				// �ł̃g���b�v�̕\��
void Poison_Trap_Move();				// �ł̃g���b�v�̓���
bool Boss_3_Jump(int* coolTime, int* boss_JumpFlg, int jumpType);	// TRUE: �W�����v�I�� FALSE: �W�����v�J�n	// �{�X�R�̃W�����v (jumpType�͂O������ƒʏ�W�����v�A�P������Ƃ��ꂽX���W���C�����Ȃ���W�����v)
void Boss_MiniKurage_Drop_Disp();		// �{�X�G���A�̃~�j�N���Q�̕\��
void Boss_MiniKurage_Drop_Move();		// �{�X�G���A�̃~�j�N���Q�̓���
void BossMiniKurage_Attack_Air(int cntBuf_Air, bool* ataackFlg_AirKurage);		// �~�j�N���Q�̋󒆓ˌ��I
void BossMiniKurage_Attack_Ground(int cntBuf_Ground, bool* attackFlg_GroundKurage);	// �~�j�N���Q�̒n��U���I
void Boss_Tackle_Disp();				// �{�X���^�b�N������\��
void Boss_Tackle_Move();				// �{�X���^�b�N�����铮��

void (* const BossDisp[5])() = {		// �{�X�̕\��
	BossDisp_Stage1,
	BossDisp_Stage2,
	BossDisp_Stage3,
	BossDisp_Stage4,
	BossDisp_Stage5,

};

void (* const BossMove[5])() = {		// �{�X�̓���
	BossMove_Stage1,
	BossMove_Stage2,
	BossMove_Stage3,
	BossMove_Stage4,
	BossMove_Stage5,
};

