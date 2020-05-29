#pragma once
#include "DxLib.h"

#define PLAYER_SKILLS    8								// �v���C���[�̎g�p�ł���X�L���̐�

enum {//�e�X�L���̃Q�[�W�g�p��
	SKILL1_GAUGE = 50,		//�X�L��1�̃Q�[�W�g�p��
	SKILL2_GAUGE = 150,		//�X�L��2�̃Q�[�W�g�p��
	SKILL3_GAUGE = 100,		//�X�L��3�̃Q�[�W�g�p��
	SKILL4_GAUGE = 150,		//�X�L��4�̃Q�[�W�g�p��
	SKILL5_GAUGE = 200,		//�X�L��5�̃Q�[�W�g�p��
	SKILL6_GAUGE = 200,		//�X�L��6�̃Q�[�W�g�p��
	SKILL7_GAUGE = 100,		//�X�L��7�̃Q�[�W�g�p��
	SKILL8_GAUGE = 100,		//�X�L��8�̃Q�[�W�g�p��
};

enum {//�e�X�L���̍Ďg�p�N�[���^�C��
	SKILL1_COOLTIME = 50,	//�X�L��1�̃N�[���^�C��
	SKILL2_COOLTIME = 50,	//�X�L��2�̃N�[���^�C��
	SKILL3_COOLTIME = 50,	//�X�L��3�̃N�[���^�C��
	SKILL4_COOLTIME = 50,	//�X�L��4�̃N�[���^�C��
	SKILL5_COOLTIME = 50,	//�X�L��5�̃N�[���^�C��
	SKILL6_COOLTIME = 50,	//�X�L��6�̃N�[���^�C��
	SKILL7_COOLTIME = 50,	//�X�L��7�̃N�[���^�C��
	SKILL8_COOLTIME = 50,	//�X�L��8�̃N�[���^�C��

};

extern bool g_skillswitch;

void SkillDisp_1(int aniMAX, int aniMIN);											//
bool SkillMove_1(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_2(int aniMAX, int aniMIN);											//
bool SkillMove_2(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_3(int aniMAX, int aniMIN);											//
bool SkillMove_3(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_4(int aniMAX, int aniMIN);											//
bool SkillMove_4(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_5(int aniMAX, int aniMIN);											//
bool SkillMove_5(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_6(int aniMAX, int aniMIN);											//
bool SkillMove_6(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_7(int aniMAX, int aniMIN);											//
bool SkillMove_7(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void SkillDisp_8(int aniMAX, int aniMIN);											//
bool SkillMove_8(int ex, int ey, int ew, int eh);		//�X�L���̓����蔻��

void(* const SkillDisp[PLAYER_SKILLS])(int aniMAX, int aniMIN) = {
	SkillDisp_1,
	SkillDisp_2,
	SkillDisp_3,
	SkillDisp_4,
	SkillDisp_5,
	SkillDisp_6,
	SkillDisp_7,
	SkillDisp_8,
};
bool(* const SkillMove[PLAYER_SKILLS])(int ex, int ey, int ew, int eh) = {
	SkillMove_1,
	SkillMove_2,
	SkillMove_3,
	SkillMove_4,
	SkillMove_5,
	SkillMove_6,
	SkillMove_7,
	SkillMove_8,
};

void SkillInit();