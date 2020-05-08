#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "GamePlay.h"
#include "Boss.h"
#include "GameScene.h"
#include "Trap.h"
#include "Skill.h"
#include "StageClear.h"


// ���ꂼ��̏���������
void GameInit() {
	MapInit();			// �}�b�v�f�[�^�̏���������
	PlayerInit();		// �v���C���[�̏���������
	EnemyInit();		// �G�l�~�[�̏���������
	RainInit();			// �J�̃A�j���[�V�����̏���������
	BossInit();			// �{�X�̏���������
	TrapInit();			// �g���b�v�̏�񏉊���
	SkillInit();		// �X�L�����̏�����
	StageClearInit();	// �X�e�[�W�N���A�̏�����
	g_enemybeat = 0;	// �G�l�~�[��|���������J�E���g����ϐ��̏�����

	//g_gameScene = GAME_TITLE;	// �^�C�g���֖߂�

}


void Reset(){
	g_player.skill_MAX = 1;
}