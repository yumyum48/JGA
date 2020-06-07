#pragma once
#include "DxLib.h"
#include "Struct.h"


#define SCROLL_MAX  (4)		// �X�N���[���摜�̍ő吔
#define MAP_MAX		(8)		// �}�b�v�̐�

extern mapInfo g_map[SCROLL_MAX];

void MapDisp();				// �}�b�v�̕\��
void MapMove();				// �}�b�v�̓���
void MapInit();				// �}�b�v�̏�����
void MapReset(int i);		// �X�N���[������}�b�v�����[�v������
void MapReset2(int i);		// �X�N���[������}�b�v�̔w�i�����[�v������
int Scroll(int mapX, int speed);	// �X�N���[������