#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "GamePlay.h"
// ���ꂼ��̏���������
void GameInit() {
	MapInit();			// �}�b�v�f�[�^�̏���������
	PlayerInit();		// �v���C���[�̏���������
	EnemyInit();		// �G�l�~�[�̏���������
	RainInit();			// �J�̃A�j���[�V�����̏���������
	g_enemybeat = 0;	// �G�l�~�[��|���������J�E���g����

}
