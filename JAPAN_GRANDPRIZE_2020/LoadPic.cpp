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
	
	// �{�^��UI�̉摜
	if (LoadDivGraph("image/Button_UI2.png", 2, 3, 1, 100, 100, g_pic.button, 0) == -1) return -1;

	// �v���C���[�摜�̓ǂݍ���
	if (LoadDivGraph("image/player3.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	//�X�L�����[�V�����摜
	if (LoadDivGraph("image/Skill_player.png", 15, 3, 5, 280, 200, g_pic.SkillMotion, 0) == -1) return -1;
	//UI�摜
	if ((g_pic.PlayerUI = LoadGraph("image/Aicon2.png")) == -1) return -1;
	//Life�摜
	if (LoadDivGraph("image/Life.png", 2, 2, 1, 100, 100, g_pic.Life, 0) == -1) return -1;

	//�Q�[�W�摜
	if ((g_pic.gauge = LoadGraph("image/AiconGauge.png")) == -1) return -1;

	//�X�L��2���[�V����(��)
	//if (LoadDivGraph("image/skill2.png", 4, 4, 1, 200, 200, g_pic.skill2, 0) == -1) return -1;
	//�X�L��3���[�V����(��)
	//if (LoadDivGraph("image/skill3.png", 5, 5, 1, 1443/5, 289, g_pic.skill3, 0) == -1) return -1;
	//�X�L���G�t�F�N�g
	if (LoadDivGraph("image/Skill_effect.png", 30, 5, 6, 400, 400, g_pic.skillEffect, 0) == -1) return -1;
	//�X�L��7�̕����v���C���[
	if (LoadDivGraph("image/Skill_7_Effect.png", 56, 8, 7, 280, 200, g_pic.skill7_Effect, 0) == -1) return -1;
	//finishMotion
	if (LoadDivGraph("image/Enemy_Finish_player3.png", 16, 4, 4, 280, 200, g_pic.finishMotion, 0) == -1) return -1;

	//�ӂ���
	if (LoadDivGraph("image/�ӂ���.png", 2, 2, 1, 80, 96, g_pic.husuma, 0) == -1) return -1;

	//�X�L���A�C�R��
	if (LoadDivGraph("image/SkillAicon.png", 8, 8, 1, 100, 100, g_pic.skillAicon, 0) == -1) return -1;
	//�X�L���A�C�R������(��)
	if ((g_pic.skillRing[0] = LoadGraph("image/ring.png")) == -1) return -1;
	if ((g_pic.skillRing[1] = LoadGraph("image/magatama.png")) == -1) return -1;

	//�X�L���I����ʂ̃Z�b�g�{�b�N�X
	if ((g_pic.skilChoiceBox = LoadGraph("image/SkillChoiceBox.png")) == -1) return -1;
	//�X�L���I����ʂ̔w�i
	if ((g_pic.customBackimage = LoadGraph("image/skillcustom_back.png")) == -1) return -1;

	// �����G���G�摜�̓ǂݍ���
	if (LoadDivGraph("image/EnemyZako1.png", 4, 4, 1, 100, 100, g_pic.enemy_walk, 0) == -1)return -1;

	// ��ԎG���G
	if (LoadDivGraph("image/zkfry.png", 4, 4, 1, 574, 545, g_pic.enemy_fly, 0) == -1)return -1;

	// �~�j�N���Q�G���G
	if (LoadDivGraph("image/MiniJelly.png", 4, 4, 1, 64, 64, g_pic.enemy_kurage, 0) == -1)return -1;

	/*//�}�b�v�̓ǂݍ���
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// �}�b�v�ǂݍ���
	if (LoadDivGraph("image/Stage_main_ALL.png", 28, 4, 7, 250, 400, g_pic.map, 0) == -1)
		return -1;
	//// �}�b�v�w�i�ǂݍ���
	//if ((g_pic.backMap = LoadGraph("image/Stage1_Back2.png")) == -1) return -1;
	
		// �}�b�v�w�i�ǂݍ���
	if (LoadDivGraph("image/Stage_back_ALL.png", 28, 4, 7, 250, 400, g_pic.backMap, 0) == -1)
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
	if (LoadDivGraph("image/Boss_1.png", 16, 8, 2, 280, 200, g_pic.boss_1_1, 0) == -1)return -1;

	// �{�X_�Q�̉摜�ǂݍ���
	if (LoadDivGraph("image/ZakoOPAll.png", 9, 9, 1, 256, 256, g_pic.boss_2_1, 0) == -1)return -1;

	// �{�X_�R�̉摜�ǂݍ���
	if (LoadDivGraph("image/BossFlog.png", 5, 5, 1, 128, 128, g_pic.boss_3_1, 0) == -1)return -1;

	// �{�X_�S�̉摜�ǂݍ���
	if (LoadDivGraph("image/SpiderBossAll.png", 6, 6, 1, 550, 500, g_pic.boss_4_1, 0) == -1)return -1;


	// �{�X_�T�̉摜�ǂݍ���
	if (LoadDivGraph("image/JellyFishBossAll.png", 10, 10, 1, 550, 600, g_pic.boss_5_1, 0) == -1)return -1;

	// �{�X_�T�̃V�[���h�摜�ǂݍ���
	if ((g_pic.boss6_sield = LoadGraph("image/JellyShield.png")) == -1) return -1;

	// �{�X_���}�^�m�̉摜�ǂݍ���
	if (LoadDivGraph("image/YamaSann01.png", 4, 4, 1, 300, 500, g_pic.boss_Yamatano, 0) == -1)return -1;

	//// �{�X_�P�̖A�摜�ǂݍ���
	//if (LoadDivGraph("image/Boss1_Water.png", 8, 8, 0, 280, 200, g_pic.boss_1_2, 0) == -1)
	//	return -1;
	// �Z���N�g��ʂ̔w�i�ǂݍ���
	//if ((g_pic.selectBack = LoadGraph("image/Select.png")) == -1) return -1;
	if ((g_pic.selectBack = LoadGraph("image/�Z���N�g���.png")) == -1) return -1;
	//�Z���N�g��ʂ�UI�摜�ǂݍ���
	if (LoadDivGraph("image/SelectUIChar.png", 4, 1, 4, 200, 100, g_pic.selectUI, 0) == -1)return -1;
	if ((g_pic.selectUI[4] = LoadGraph("image/SelectUI.png")) == -1) return -1;

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

	// �{�X�R�̐�̉摜
	if ((g_pic.bossTongue = LoadGraph("image/tongue.png")) == -1) return -1;

	// �q�w偂̉摜
	if (LoadDivGraph("image/SpederKids.png", 4, 4, 1, 64, 64, g_pic.spiderKids, 0) == -1)return -1;

	// ���_�̉摜
	if ((g_pic.thundercloud = LoadGraph("image/Cloud.png")) == -1) return -1;
	// �����̎��̉摜
	if ((g_pic.spiderThread = LoadGraph("image/String.png")) == -1) return -1;



	return 0;
}