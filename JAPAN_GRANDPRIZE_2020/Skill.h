#pragma once
#include "DxLib.h"

#define PLAYER_SKILLS    8								// プレイヤーの使用できるスキルの数

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