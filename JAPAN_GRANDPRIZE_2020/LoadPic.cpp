#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// �^�C�g���摜
	if ((g_pic.title[0] = LoadGraph("image/titleimage5a.png")) == -1) return -1;

	// �^�C�g���̃e�L�X�g�摜
	if ((g_pic.titleText[0] = LoadGraph("image/Title_Text2.png")) == -1) return -1;		// �^�C�g�����S
	if ((g_pic.titleText[1] = LoadGraph("image/NewGame1.png")) == -1) return -1;			// �^�C�g�����S
	if ((g_pic.titleText[2] = LoadGraph("image/Continue1.png")) == -1) return -1;		// �^�C�g�����S
	if ((g_pic.titleText[3] = LoadGraph("image/fin1.png")) == -1) return -1;		// �^�C�g�����S
	
	

	// �v���C���[�摜�̓ǂݍ���
	if (LoadDivGraph("image/player3.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	//�X�L�����[�V�����摜
	if (LoadDivGraph("image/Skill_player.png", 9, 3, 3, 280, 200, g_pic.SkillMotion, 0) == -1) return -1;
	//UI�摜
	if ((g_pic.PlayerUI = LoadGraph("image/Aicon2.png")) == -1) return -1;
	//Life�摜
	if (LoadDivGraph("image/Life.png", 2, 2, 1, 100, 100, g_pic.Life, 0) == -1) return -1;

	//�Q�[�W�摜
	if ((g_pic.gauge = LoadGraph("image/AiconGauge.png")) == -1) return -1;

	//�X�L��2���[�V����(��)
	if (LoadDivGraph("image/skill2.png", 4, 4, 1, 200, 200, g_pic.skill2, 0) == -1) return -1;
	//�X�L��3���[�V����(��)
	if (LoadDivGraph("image/skill3.png", 5, 5, 1, 1443/5, 289, g_pic.skill3, 0) == -1) return -1;

	// �����G���G�摜�̓ǂݍ���
	if (LoadDivGraph("image/EnemyZako1.png", 4, 4, 1, 100, 100, g_pic.enemy_walk, 0) == -1)return -1;

	// ��ԎG���G
	if (LoadDivGraph("image/zkfry.png", 4, 4, 1, 574, 545, g_pic.enemy_fly, 0) == -1)return -1;

	/*//�}�b�v�̓ǂݍ���
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// �}�b�v�ǂݍ���
	if (LoadDivGraph("image/Stage1_main2.png", 4, 4, 1, 250, 400, g_pic.map, 0) == -1)
		return -1;
	//// �}�b�v�w�i�ǂݍ���
	//if ((g_pic.backMap = LoadGraph("image/Stage1_Back2.png")) == -1) return -1;
	
		// �}�b�v�w�i�ǂݍ���
	if (LoadDivGraph("image/Stage1_Back2.png", 4, 4, 1, 250, 400, g_pic.backMap, 0) == -1)
		return -1;
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// �J�̉摜�̓ǂݍ���
	if ((g_pic.rain = LoadGraph("image/RainLarge.png")) == -1) return -1;

	if ((g_pic.trap = LoadGraph("image/toge.png")) == -1) return -1;
	// ���e�B�N���摜�̓ǂݍ���
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;

	// �{�X_�P�̉摜�ǂݍ���
	if (LoadDivGraph("image/Boss_1.png", 16, 8, 2, 280, 200, g_pic.boss_1_1, 0) == -1)
		return -1;

	//// �{�X_�P�̖A�摜�ǂݍ���
	//if (LoadDivGraph("image/Boss1_Water.png", 8, 8, 0, 280, 200, g_pic.boss_1_2, 0) == -1)
	//	return -1;
	// �Z���N�g��ʂ̔w�i�ǂݍ���
	if ((g_pic.selectBack = LoadGraph("image/Select.png")) == -1) return -1;

	// ���e�̉摜�̓ǂݍ���
	if (LoadDivGraph("image/watb1.png", 5, 5, 1, 32, 32, g_pic.waterBullet, 0) == -1)return -1;

	// �G���j���̐����Ԃ�
	if (LoadDivGraph("image/bassha.png", 5, 5, 1, 100, 100, g_pic.enemySplashes, 0) == -1)return -1;
	// �G���j���̏��C
	if (LoadDivGraph("image/moku1.png", 5, 5, 1, 100, 100, g_pic.enemyVapour, 0) == -1)return -1;

	// �X�e�[�W�N���A����[��������]�̕���
	if ((g_pic.stageClearText = LoadGraph("image/stageClear.png")) == -1) return -1;

	// �Q�[���I�[�o�[����[�������s]�̕���
	if ((g_pic.gameOverText = LoadGraph("image/gameOver.png")) == -1) return -1;


	return 0;
}