#pragma once
#include "Struct.h"

#define SCROLL_MAX  (3)
#define MAP_MAX		(8)

void MapDisp();	// �}�b�v�̕\��
void MapMove();	// �}�b�v�̓���
void MapInit();	// �}�b�v�̏�����
void Scroll(float* mapX);	// �X�N���[������