#pragma once
#include "DxLib.h"

extern bool g_animationScene;	// �A�j���[�V�������I�������ăe�L�X�g��\��������t���O	TRUE:�e�L�X�g�̕\��ON	FALSE:�{�X�����j����A�j���[�V����

void StageClear();				// �X�e�[�W�N���A�֐��̊Ǘ�
void StageClearDisp();			// �X�e�[�W�N���A�̕\��
void StageClearMove();			// �X�e�[�W�N���A�̓���
int Player_StageClearMove();	// �X�e�[�W�N���A���̃v���C���[�̓���
int ClearTextMove();			// [��������]�̉摜�̃A�j���[�V����
void StageClearInit();			// �X�e�[�W�N���A��ʂ̏�����
void BossDefeatAnimationDisp();	// �{�X���j���̃A�j���[�V�����`��
void BossDefeatAnimationMove();	// �{�X���j���̃A�j���[�V������������