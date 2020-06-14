#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"

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
#define	BOSS_THREAD_WIDTH	(6)			// ���̉���
#define	BOSS_CLOUD_HEIGHT  (134)		// �_�̍���
#define BOSS_STAGE5_WIDTH  (324)		// �{�X�T�̕�
#define BOSS_STAGE5_HEIGHT (415)		// �{�X�T�̏c
#define BOSS_STAGE6_WIDTH  (89.6 + 179.2)		//�{�X�U�̉� (PLAYER_WIDTH * PLAYER_REDUCTION) + (PLAYER_WIDTH * PLAYER_REDUCTION)
#define BOSS_STAGE6_HEIGHT (PLAYER_HEIGHT + 70)	// �{�X�U�̏c
#define BOSS_STAGELAST_WIDTH  (537)		// ���X�{�X�̕�
#define BOSS_STAGELAST_HEIGHT (660)		// ���X�{�X�̏c

#define YAMATANO_NECK        (7)        // ���X�{�X�O�̂V�̂̎�

#define BOSS_WAVE_WIDTH      (200)		// �g�̉���
#define BOSS_WAVE_HEIGHT     (150)      // �g�̍���

#define BOSS_TON_HEIGHT      (70)		// ��̍���

#define BOSS_WAVE_WIDTH		 (200)		// �Ôg�̉���
#define BOSS_WAVE_HEIGHT	 (150)		// �Ôg�̏c��
/***********************************************************

// �萔�̐錾

***********************************************************/
const int BOSSFULL_WIDTH[MAP_MAX] = {BOSS_WIDTH, BOSS_STAGE2_WIDTH, BOSS_STAGE3_WIDTH, BOSS_STAGE4_WIDTH, BOSS_STAGE5_WIDTH, BOSS_STAGE6_WIDTH, BOSS_STAGELAST_WIDTH };
const int BOSSFULL_HEIGHT[MAP_MAX] = { BOSS_HEIGHT, BOSS_STAGE2_HEIGHT, BOSS_STAGE3_HEIGHT, BOSS_STAGE4_HEIGHT, BOSS_STAGE5_HEIGHT, BOSS_STAGE6_HEIGHT, BOSS_STAGELAST_HEIGHT };
const int KURAGE_MAX = 4;	// �N���Q�̍ő吔
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
	BOSS_LASTBOSS,
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
	BOSSATTACK_RUSH,					// �{�X�̓ːi�U��
	BOSSATTACK_LONG_RANGE,				// �{�X�̉������U��
	BOSSATTACK_MAX,                     // �{�X�̍U���̍ő吔
};

enum {    // ���X�{�X�̍U�����f

	LAST_BOSSATTACK_WATER_BULLET,            // ���X�{�X�p�̐��e
	LAST_BOSSATTACK_ENEMY_DROP,              // ���X�{�X�p�̕����G���G
	LAST_BOSSATTACK_LONGTON,                 // ���X�{�X�p�̐�
	LAST_BOSSATTACK_MINISPIDER_DROP,         // ���X�{�X�p�̃~�j�w�
	LAST_BOSSATTACK_MINICLOUD_DROP,          // ���X�{�X�p�̃~�j�_
	LAST_BOSSATTACK_LIGHTNING,               // ���X�{�X�p�̗���
	LAST_BOSSATTACK_MINIKURAGE,				 // ���X�{�X�p�̃~�j�N���Q�U��
	LAST_BOSSATTACK_SHADOW,					 // ���X�{�X�p�̉e�ɂ��U��
	LAST_BOSSATTACK_MAX,                     // ���X�{�X�̍U���̍ő吔
};

enum { // �{�X�̓����p�^�[��
	BOSSMOVE_NOMOTION,		// �m�[���[�V����
	BOSSMOVE_ATTACK,		// �{�X��Sin�g�ōU�߂Ă���
	BOSSMOVE_SPEEDDOWN,		// �{�X���v���C���[�ɒǂ�����铮��
	BOSSMOVE_DOWN,			// �U���A�ړ����ł��Ȃ����
};

enum {	// �{�X�R�̃W�����v�t���O����
	BOSS_3_JUMPOFF,
	BOSS_3_JUMPON,
	BOSS_3_DOWN,
};
enum {	// ���X�{�X�O�̂V�̂̎�
	LASTBOOS_OFF,        // �o�����Ă��Ȃ�
	LASTBOSS_ON,         // �o�����Ă���
	LASTBOSS_MINIKILL,   // �|���Ă��邯�ǉ�ʂɂ���
	LASTBOSS_KILL,       // �|����
	LASTBOSS_MINION,     // �o�����Ă��邯�ǁA�U���ł��Ȃ�
};

enum {    // ���X�{�X�O�̂V�̂̎ւ̏o�����Ă���ꏊ�̃^�O
	TAG_BOSS_LEFT,        // ���ɂ���
	TAG_BOSS_RIGHT,       // �E�ɂ���
};
struct lasbossInfo : public bossInfo {    // ���X�{�X�O�̂V�̂̎ւ̏��
	int w;		// X���W
	int h;		// Y���W
	int tag;	// �E�ɂ��邩���ɂ��邩�̃^�O
	int sevenAttackFlg;    // �U�����Ă��邩�ǂ�����^���U�Ŕ��f���� TRUE:�U������ FALSE: �U�����Ă��Ȃ�
	int anima;	// �A�j���[�V�����p�̃����o
	int animaMax;	// �A�j���[�V�����p�ő吔
	int animaMin;	// �A�j���[�V�����p�ŏ���
	void lasbossInit(int num);// ������
};

struct shadow : picInfo {				// ���X�{�X�O�̍Ō�̓G�̉e�̏��

	bool shadowDispFlg;		// �e�̕\���Ɏg�p����t���O	TRUE:�\��	FALSE:��\��
	bool attackDispFlg;		// �e�̉������U���\���Ɏg�p����t���O	TRUE:�\��	FALSE:��\��
	int preparationCnt;		// �\�����쎞��
	int attackx;
	int attacky;
	int attackw;
	int attackh;

	void ShadowInit(int bx, int by = (GROUND - PLAYER_HEIGHT), bool randFlg = FALSE) {	// �e�̈ʒu��������

		shadowDispFlg = FALSE;
		attackDispFlg = FALSE;
		preparationCnt = 0;
		x = bx - PLAYER_WIDTH / 2;
		y = GROUND - 280 * PLAYER_REDUCTION;
		w = PLAYER_WIDTH * PLAYER_REDUCTION;
		h = PLAYER_HEIGHT;
		/*w = 490;
		h = 230;*/
		//if (randFlg == TRUE) {
		//	y = by - 
		//}
	}
	void LongRangeInit(int bx, int by = (GROUND - 40/*PLAYER_HEIGHT*/), bool randFlg = FALSE) {

		shadowDispFlg = FALSE;
		attackDispFlg = FALSE;
		preparationCnt = 0;
		attackx = bx - 200;
		attacky = GROUND - 80;
		attackw = 150;
		attackh = PLAYER_HEIGHT / 2;
	}
};

struct boss4_parts :public picInfo {	//�{�X�S�̉_�Ǝ��̏�� 
	int hp;					// ���̂���
	bool dispFlg;			// ����\�����f����t���O
	void ThreadInit() {
		Boss4_ThreadInit();	// ���̏�����
		hp = 2;
		dispFlg = TRUE;
	}
	void ThreadReSet(int cloudX, int cloudY) {		// �����̎��𗋉_�ɍ��킹�čăZ�b�g
		x = cloudX - (BOSS_THREAD_WIDTH / 2) + 265 / 2;
		y = cloudY + (BOSS_CLOUD_HEIGHT / 2);
		w = cloudX + (BOSS_THREAD_WIDTH / 2) + 265 / 2;
	}

};
struct bossAttackInfo {	// �{�X�̍U���̍ۂɎg���\������
	int x, y;

};
struct boss5_extension :public bossInfo {	// �{�X�T�̕ϐ��g�� 
	int anime;
	bool attackFlg;
	bool animeFlg;
	void AnimtionInit() {
		anime = 0;
		attackFlg == FALSE;
	}
};

struct rightningInfo {        // �����̏��
	int x = 419;                // X���W�̏�����
	int y = 180;                // Y���W�̏�����
	int cnt;					//
	float exRate;				// 

};
//struct barrier : public picInfo {
//	bool flg;	// �o���t���O
//	int cnt;	// �o���J�E���g
//
//	// barriar�����������郁�\�b�h
//	void barrierInit() {
//		x = g_boss[g_select_Stage].x - 100;	// X���W�̏����ʒu
//		y = g_boss[g_select_Stage].y + 10;	// Y���W�̏����ʒu
//
//		flg = FALSE;	// �o���t���O��������	
//		cnt = 0;		// �o���J�E���g��������
//	}
//};
/***********************************************************

// �O���[�o���ϐ��̐錾

***********************************************************/
extern bossInfo g_boss[MAP_MAX];		// �{�X�̏��
extern boss4_parts g_boss4_Cloud;		// �{�X�S�̉_�̏��
extern boss4_parts g_boss4_Thread;		// �{�X�S�̎��̏��
extern trapInfo g_wave;                 // �g�̏��
extern picInfo g_boss3_Ton;             // ��̏��
extern lasbossInfo g_boss_Yamatano[YAMATANO_NECK];    // ���X�{�X�O�̂V�̂̎�
extern bool g_lastBoss_StartAnimeFlg;    // ���X�{�X�O�̏o���A�j���[�V�������s���t���O TRUE:�A�j���[�V�������s�� FALSE:�s��Ȃ�
extern boss5_extension g_boss5_Ex;		// �{�X�T�̕ϐ��g��
//extern barrier g_barrier;				// �o���A�̏��
extern rightningInfo g_rightning;		// �����̏��
extern shadow g_boss_shadow;			// �e�̍U���̏��
extern int g_boss4_JumpAnime;			// �J�G���̃W�����v����A�j���[�V����
/***********************************************************

// �֐��̐錾

***********************************************************/
int InputRand(int rand1, int rand2, int rand3);	// �����������Ƃ��ĎO���A���̒��̈�������_���ŕԂ�
int InputHyperRand(int rand1, int rand2, int rand3 = 0, int rand4 = 0, int rand5 = 0, int rand6 = 0, int rand7 = 0, int rand8 = 0);
bool BossDamageCheck(int bossHp);				// �{�X���_���[�W���󂯂����ǂ����𒲂ׂ�֐� TRUE: �{�X���_���[�W���󂯂� FALSE: �{�X�̓_���[�W���󂯂Ă��Ȃ�
void Boss_Damage_Disp(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// �{�X���_���[�W��H��������[�V����������
void Boss_Damage_Disp2(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// �{�X���_���[�W��H��������[�V����������2
void Boss_Damage_Disp3(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// �{�X���_���[�W��H��������[�V����������3
bool BossNoAttackCheck(int bossAttackFlg);		// �{�X���U�����I�������𒲂ׂ�֐�TRUE: �{�X�̍U���I�� FALSE: �{�X�͍U�����A�܂��͏I�����Ă��΂炭�����Ă���
bool BossDropAttackCheck(int bossAttackFlg);	// �{�X���G�l�~�[���h���b�v���邩�𒲂ׂ�֐�TRUE: �{�X�̍U���J�n FALSE: �{�X�͍U�����A�܂��͏I�����Ă��΂炭�����Ă���
void Boss_MiniKurage_DropFlg();					// �~�j�N���Q���o���t���O�Ǘ�
void KurageHit();								// �v���C���[���N���Q�ɓ�����ƃ_���[�W���󂯂�

void LastBossRightNingAnime();            // 
void Last_Boss_SnakeDispFlg_Managar();    // 

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
void BossDisp_Stage6();					// �X�e�[�W�U�̃{�X�̕\��
void BossMove_Stage6();					// �X�e�[�W�U�̃{�X�̓���
void BossDisp_Stage_Last();				// ���X�{�X�\��
void BossMove_Stage_Last();				// ���X�{�X����

void Boss_Knock_Down();					// �{�X���|����鏈��
void Boss_Snake_Knockdown();            // ���X�{�X�O�̂V�̂̎ւ��|����鏈��
void Snake_Add_To_Anime();				// �ւ̒ǉ��A�j���[�V����

void BossInit();						// �{�X�̏�����
void Boss_Stage4_Init();				// �{�X�S�̉_�̏�����
void LastBossInit();                    // ���X�{�X�O�̂V�̂̎ւ̏�����
void Boss5_Init();						// �{�X�T�̏�����
void Boss6_Init();						// �{�X�U�̏�����

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
void BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage);		// �~�j�N���Q�̋󒆓ˌ��I
void BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage);	// �~�j�N���Q�̒n��U���I
void Boss_Tackle_Disp();				// �{�X���^�b�N������\��
void Boss_Tackle_Move();				// �{�X���^�b�N�����铮��
void ThreadMove(int* moveFlg);          // �����̎��̓�������
void SpiderNoThreadMove(int* moveFlg);  // �����̎����؂ꂽ���̓���
void Boss_Rush_Disp();					// �e�̓ːi�U��
void Boss_Rush_Move();					// �e�̓ːi�U��
void Boss_LongRange_Disp();				// �e�̉������U��
void Boss_LongRange_Move();				// �e�̉������U��

void (* const BossDisp[MAP_MAX])() = {		// �{�X�̕\��
	BossDisp_Stage1,
	BossDisp_Stage2,
	BossDisp_Stage3,
	BossDisp_Stage4,
	BossDisp_Stage5,
	BossDisp_Stage6,
	BossDisp_Stage_Last,
};

void (* const BossMove[MAP_MAX])() = {		// �{�X�̓���
	BossMove_Stage1,
	BossMove_Stage2,
	BossMove_Stage3,
	BossMove_Stage4,
	BossMove_Stage5,
	BossMove_Stage6,
	BossMove_Stage_Last,
};


void YmatanoSeven_Disp();	// ���X�{�X�O�̂V�̂̎ւ̕`��(�U���n�̂�)
void YmatanoSeven_Move();	// ���X�{�X�O�̂V�̂̎ւ̓���
void LastBoss_Disp();		// ���X�{�X
void LastBoss_Move();

// �~�j�N���Q�̋󒆍U��
void Last_BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage);
// �~�j�N���Q�̒n��U��
void Last_BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage);

void Last_Boss_Attack_WaterBullet_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ���X�{�X�p�̐��e�\��
void Last_Boss_Attack_WaterBullet_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ���X�{�X�p�̐��e����
void Last_Boss_Attack_BossEnemyDrop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);  // ���X�{�X�p�̕����G���G�̕\��
void Last_Boss_Attack_BossEnemyDrop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);  // ���X�{�X�p�̕����G���G�̓���
void Last_Boss_Attack_BossLongTon_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ���X�{�X�p�̐�\��
void Last_Boss_Attack_BossLongTon_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ���X�{�X�p�̐㓮��
void Last_Boss_Attack_MiniSpider_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);// ���X�{�X�p�̃~�j�w偕\��
void Last_Boss_Attack_MiniSpider_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);// ���X�{�X�p�̃~�j�w偓���
void Last_Boss_Attack_MiniCloud_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);	// ���X�{�X�p�̃~�j�_�̕\��
void Last_Boss_Attack_MiniCloud_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);	// ���X�{�X�p�̃~�j�_�̓���
void Last_Boss_Attack_Lightning_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ���X�{�X�p�̗����̕\��
void Last_Boss_Attack_Lightning_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ���X�{�X�p�̗����̕\��
void Last_Boss_MiniKurage_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ���X�{�X�p�̃~�j�N���Q�̂̕\��
void Last_Boss_MiniKurage_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ���X�{�X�p�̃~�j�N���Q�̂̕\��
void Last_Boss_Shadow_Attack_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);			// ���X�{�X�p�̉e�̕\��
void Last_Boss_Shadow_Attack_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);			// ���X�{�X�p�̉e�̕\��



/***********************************************************

// ���X�{�X�O�̂V�̂̎ւ̍U��

***********************************************************/
// �\��
void (* const Last_Yamatano_Boss_Attack_Disp[LAST_BOSSATTACK_MAX])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ���X�{�X�p�̍U���\���Ǘ�

		Last_Boss_Attack_WaterBullet_Disp,
		Last_Boss_Attack_BossEnemyDrop_Disp,
		Last_Boss_Attack_BossLongTon_Disp,
		Last_Boss_Attack_MiniSpider_Drop_Disp,
		Last_Boss_Attack_MiniCloud_Drop_Disp,
		Last_Boss_Attack_Lightning_Disp,
		Last_Boss_MiniKurage_Drop_Disp,
		Last_Boss_Shadow_Attack_Disp,
};
// ����
void (* const Last_Yamatano_Boss_Attack_Move[LAST_BOSSATTACK_MAX])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ���X�{�X�p�̍U�������Ǘ�

		Last_Boss_Attack_WaterBullet_Move,
		Last_Boss_Attack_BossEnemyDrop_Move,
		Last_Boss_Attack_BossLongTon_Move,
		Last_Boss_Attack_MiniSpider_Drop_Move,
		Last_Boss_Attack_MiniCloud_Drop_Move,
		Last_Boss_Attack_Lightning_Move,
		Last_Boss_MiniKurage_Drop_Move,
		Last_Boss_Shadow_Attack_Move,
};

/***********************************************************

// ���X�{�X�̖{�̂̍U��

***********************************************************/
void Last_Boss_Attack_Null_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);	// �U�������Ȃ�
void Last_Boss_Attack_Null_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);	// �U�������Ȃ�
void (* const Last_Boss_Attack_Disp[LAST_BOSSATTACK_MAX + 1])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ���X�{�X�p�̍U���\���Ǘ�
		Last_Boss_Attack_Null_Disp,
		Last_Boss_Attack_WaterBullet_Disp,
		Last_Boss_Attack_BossEnemyDrop_Disp,
		Last_Boss_Attack_BossLongTon_Disp,
		Last_Boss_Attack_MiniSpider_Drop_Disp,
		Last_Boss_Attack_MiniCloud_Drop_Disp,
		Last_Boss_Attack_Lightning_Disp,
		Last_Boss_MiniKurage_Drop_Disp,
		Last_Boss_Shadow_Attack_Disp,
};
// ����
void (* const Last_Boss_Attack_Move[LAST_BOSSATTACK_MAX + 1])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ���X�{�X�p�̍U�������Ǘ�
		Last_Boss_Attack_Null_Move,
		Last_Boss_Attack_WaterBullet_Move,
		Last_Boss_Attack_BossEnemyDrop_Move,
		Last_Boss_Attack_BossLongTon_Move,
		Last_Boss_Attack_MiniSpider_Drop_Move,
		Last_Boss_Attack_MiniCloud_Drop_Move,
		Last_Boss_Attack_Lightning_Move,
		Last_Boss_MiniKurage_Drop_Move,
		Last_Boss_Shadow_Attack_Move,
};


