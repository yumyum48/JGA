#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
	
void BossDisp_Stage1();						// �X�e�[�W�P�̃{�X�̕\��
void BossMove_Stage1();						// �X�e�[�W�P�̃{�X�̓���
void (* const BossDisp[1])() = {		// �{�X�̕\��
	BossDisp_Stage1,
};

void (* const BossMove[1])() = {		// �{�X�̓���
	BossMove_Stage1,
};
