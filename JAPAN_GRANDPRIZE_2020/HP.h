#pragma once
#include "DxLib.h"
#include "Struct.h"

//extern playerInfo g_player;				// �v���C���[�̏��
//extern enemyType g_enemy[ENEMY_MAX];		// �G�̏��

extern int g_MutekiTime;

void ManagementHP();		//HP�Ǘ�
void HpMove();				//HP�v�Z����
void HpDisp();				//HP�\������