#pragma once
#include "Struct.h"

#define SCROLL_MAX  (4)		// �X�N���[���摜�̍ő吔
#define MAP_MAX		(8)		// �}�b�v�̐�

void MapDisp();				// �}�b�v�̕\��
void MapMove();				// �}�b�v�̓���
void MapInit();				// �}�b�v�̏�����
void MapReset(int i);		// �X�N���[������}�b�v�����[�v������
void Scroll(float* mapX);	// �X�N���[������