#pragma once

struct scene_animaInput{	// �A�j���[�V�����ɕK�v�ȏ��

	int nextScene;		// �A�j���[�V�������I��������ɐ؂�ւ���V�[��
	int animeType;		// �A�j���[�V�����̃^�C�v	0:���� 1:����...
	int nowDisp[2];		// �A�j���[�V�������s����ʂ�ۑ�����
	

};

struct animationInfo {		// �A�j���[�V�����ɕK�v�ȓ����Ȃǂ��Č�����ꍇ�Ɏg�����
	int x, y;	// X, Y���W

	void Init(int num) {
		switch (num) {
		case 0: 
			x = 0;
			y = 0;
			break;
		case 1:
			x = WINDOW_WIDTH / 2;
			y = 0;
		default:
			break;
		}
		
	}
};
void ChangeScreen_Animation();								// �A�j���[�V�������s���֐�
void ChangeScreen_Animation_Init();							// �A�j���[�V�����p�̏������֐�
void Scene_Animation_Shoji(int nextScene);					// ��q���J���悤�ȃA�j���[�V����
scene_animaInput Get_NowDisp(int nextScene, int animeType);	// �V�[����ς��鎞�̃A�j���[�V�������N������֐� ���� (int ���̃V�[��, int �g�p����A�j���[�V�����̔ԍ� (0�Ԗڂ͎g��Ȃ��ŉ������I))