#pragma once
#include "DxLib.h"

#define PLAYER_SKILLS    8								// プレイヤーの使用できるスキルの数

enum {//各スキルのゲージ使用量
	SKILL1_GAUGE = 50,		//スキル1のゲージ使用量
	SKILL2_GAUGE = 150,		//スキル2のゲージ使用量
	SKILL3_GAUGE = 100,		//スキル3のゲージ使用量
	SKILL4_GAUGE = 150,		//スキル4のゲージ使用量
	SKILL5_GAUGE = 200,		//スキル5のゲージ使用量
	SKILL6_GAUGE = 200,		//スキル6のゲージ使用量
	SKILL7_GAUGE = 100,		//スキル7のゲージ使用量
	SKILL8_GAUGE = 100,		//スキル8のゲージ使用量
};

enum {//各スキルの再使用クールタイム
	SKILL1_COOLTIME = 50,	//スキル1のクールタイム
	SKILL2_COOLTIME = 50,	//スキル2のクールタイム
	SKILL3_COOLTIME = 50,	//スキル3のクールタイム
	SKILL4_COOLTIME = 50,	//スキル4のクールタイム
	SKILL5_COOLTIME = 50,	//スキル5のクールタイム
	SKILL6_COOLTIME = 50,	//スキル6のクールタイム
	SKILL7_COOLTIME = 50,	//スキル7のクールタイム
	SKILL8_COOLTIME = 50,	//スキル8のクールタイム

};

extern bool g_skillswitch;

void SkillDisp_1(int aniMAX, int aniMIN);											//
bool SkillMove_1(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_2(int aniMAX, int aniMIN);											//
bool SkillMove_2(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_3(int aniMAX, int aniMIN);											//
bool SkillMove_3(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_4(int aniMAX, int aniMIN);											//
bool SkillMove_4(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_5(int aniMAX, int aniMIN);											//
bool SkillMove_5(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_6(int aniMAX, int aniMIN);											//
bool SkillMove_6(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_7(int aniMAX, int aniMIN);											//
bool SkillMove_7(int ex, int ey, int ew, int eh);		//スキルの当たり判定

void SkillDisp_8(int aniMAX, int aniMIN);											//
bool SkillMove_8(int ex, int ey, int ew, int eh);		//スキルの当たり判定

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