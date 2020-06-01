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
#include "Select.h"
#include "Change_ScReen_Animation.h"
#include "StageClear.h"
#include "GameOver.h"
#include "HP.h"
// ���ꂼ��̏���������
void GameInit() {
	MapInit();			// �}�b�v�f�[�^�̏���������
	PlayerInit();		// �v���C���[�̏���������
	HpInit();			// HP�֌W�̏�����
	EnemyInit();		// �G�l�~�[�̏���������
	RainInit();			// �J�̃A�j���[�V�����̏���������
	BossInit();			// �{�X�̏���������
	TrapInit();			// �g���b�v�̏�񏉊���
	SelectInit();		// �Z���N�g��ʂ̏�����
	g_enemybeat = 0;	// �G�l�~�[��|���������J�E���g����ϐ��̏�����
	ChangeScreen_Animation_Init();	// �V�[���`�F���W�A�j���[�V�����̏�����
	StageClearInit();	// �X�e�[�W�N���A��ʂ̏�����
	GameOverInit();		// �Q�[���I�[�o�[��ʂ̏�����
	//g_gameScene = GAME_TITLE;	// �^�C�g���֖߂�

}

// �ۑ����ׂ��f�[�^���폜
void Reset(){
	g_select_MAX = 0;			// �v���C���[���s����X�e�[�W���P�݂̂ɂ���
	g_player.skill_MAX = 1;	// �v���C���[�̎擾���Ă���X�L�����Q�[���J�n��Ԃɖ߂�
	g_playTime = 0;	// �v���C���Ԃ�������
	g_player.skillcustom[0] = 1;
	g_player.skillcustom[1] = 0;
	g_player.skillcustom[2] = 0;
	GameInit();
}