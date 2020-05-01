#pragma once
#include "DxLib.h"

#define PLAYER_SKILLS    1									// プレイヤーの使用できるスキルの数

void SkillDisp_1(int aniMAX, int aniMIN);											//
void SkillMove_1();											//

void(* const SkillDisp[PLAYER_SKILLS])(int aniMAX, int aniMIN) = {
	SkillDisp_1,
};
void(* const SkillMove[PLAYER_SKILLS])() = {
	SkillMove_1,
};