#pragma once

struct scene_animaInput{	// �A�j���[�V�����ɕK�v�ȏ��

	int nextScene;		// �A�j���[�V�������I��������ɐ؂�ւ���V�[��
	int animeType;		// �A�j���[�V�����̃^�C�v	0:���� 1:����...
	int nowDisp;		// �A�j���[�V�������s����ʂ�ۑ�����
	

};
void ChangeScreen_Animation();								// �A�j���[�V�������s���֐�
scene_animaInput Get_NowDisp(int nextScene, int animeType);	// �V�[����ς��鎞�̃A�j���[�V�������N������֐� ���� (int ���̃V�[��, int �g�p����A�j���[�V�����̔ԍ� (0�Ԗڂ͎g��Ȃ��ŉ������I))