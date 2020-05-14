#include "DxLib.h"
#include "Sounds.h"


int LoadSounds(void) {				//�T�E���h�ǂݍ���

	if ((g_sound[BGM_TITLE] = LoadSoundMem("sounds/Soushi2.mp3")) == -1) return -1;	//�^�C�g��BGM
	if ((g_sound[BGM_SELECT] = LoadSoundMem("sounds/n2.mp3")) == -1) return -1;	//�Z���N�gBGM
	if ((g_sound[BGM_BATTLE] = LoadSoundMem("sounds/Gen-ou-You.mp3")) == -1) return -1;	//�o�g��BGM
	if ((g_sound[BGM_BOSS] = LoadSoundMem("sounds/senou.mp3")) == -1) return -1;	//�o�g��BGM
	if ((g_sound[BGM_LAST_BOSS] = LoadSoundMem("sounds/n76.mp3")) == -1) return -1;	//���X�{�XBGM
	if ((g_sound[BGM_RAIN] = LoadSoundMem("sounds/towm-torrential-rain1.mp3")) == -1) return -1;	//�JBGM
	if ((g_sound[BGM_OVER] = LoadSoundMem("sounds/Torii.mp3")) == -1) return -1;	//�Q�[�����S�N���ABGM
	if ((g_sound[BGM_GAMECLEAR] = LoadSoundMem("sounds/n103.mp3")) == -1) return -1;	//�Q�[�����S�N���ABGM

	if ((g_sound[SE_ENEMY_DOWN] = LoadSoundMem("sounds/sei_ge_jouhatu01.mp3")) == -1) return -1;	//�G����SE
	if ((g_sound[SE_DECISION] = LoadSoundMem("sounds/hyoushigi1.mp3")) == -1) return -1;	//�I��SE
	if ((g_sound[SE_KETTEI] = LoadSoundMem("sounds/japanese-style-1.mp3")) == -1) return -1;	//����SE
	if ((g_sound[SE_STEP] = LoadSoundMem("sounds/footstep-rain.mp3")) == -1) return -1;	//����SE
	if ((g_sound[SE_JUMP] = LoadSoundMem("sounds/pichan.mp3")) == -1) return -1;	//�W�����vSE
	if ((g_sound[SE_TYAKUTI] = LoadSoundMem("sounds/02.mp3")) == -1) return -1;	//���nSE

	if ((g_sound[VOICE_NORMAL] = LoadSoundMem("sounds/sizukani.mp3")) == -1) return -1;	//��l���U���{�C�X
	if ((g_sound[VOICE_SPECIAL] = LoadSoundMem("sounds/witch-special1.mp3")) == -1) return -1;	//��l���K�E�{�C�X
	if ((g_sound[VOICE_DAMAGE] = LoadSoundMem("sounds/thief-boy-damage2.mp3")) == -1) return -1;	//��l���_���[�W�{�C�X

	if ((g_sound[BOSS1_ATTACK] = LoadSoundMem("sounds/se_maoudamashii_element_water06.mp3")) == -1) return -1;	//�{�X�P�U����
	if ((g_sound[BOSS3_ATTACK1] = LoadSoundMem("sounds/Boss2_1.mp3")) == -1) return -1;	//�{�X�R��U����
	if ((g_sound[BOSS3_ATTACK2] = LoadSoundMem("sounds/boss_born.mp3")) == -1) return -1;	//�{�X�R�ŏ��U����
	if ((g_sound[BOSS3_ATTACK2] = LoadSoundMem("sounds/boss_born.mp3")) == -1) return -1;	//�{�X�S����������
	if ((g_sound[BOSS5_SHIELD] = LoadSoundMem("sounds/shield.mp3")) == -1) return -1;	//�{�X�T�V�[���h��
	if ((g_sound[BOSS5_ATTACK] = LoadSoundMem("sounds/short_bomb.mp3")) == -1) return -1;	//�{�X�T�N���Q�~�T�C����




}