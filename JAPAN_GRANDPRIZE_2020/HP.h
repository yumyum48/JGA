#pragma once
#include "DxLib.h"
#include "Struct.h"

//extern playerInfo g_player;				// �v���C���[�̏��
//extern enemyType g_enemy[ENEMY_MAX];		// �G�̏��

extern int g_noDamageCnt;						// �v���C���[�̖��G����

void ManagementHP();		// HP�Ǘ�
void HpMove();				// HP�v�Z����
void HpDisp();				// HP�\������
void HpInit();				// Hp�֌W�̏�����