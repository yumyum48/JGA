#pragma once
#define SCROLL_MAX  (3)
#define MAP_MAX		(8)

extern int g_stageInput;

void MapDisp();	// �}�b�v�̕\��
void MapMove();	// �}�b�v�̓���
void MapInit();	// �}�b�v�̏�����
void Scroll(float* mapX);	// �X�N���[������