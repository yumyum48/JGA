#include "DxLib.h"
#include "SkillCustom.h"
#include "GameScene.h"
#include "control.h"

void SkillCustom() {
	SkillCustom_Move();
	SkillCustom_Disp();

}

// �X�L���J�X�^�}�C�Y�̕\��
void SkillCustom_Disp() {

}

// �X�L���J�X�^�}�C�Y�̓���
void SkillCustom_Move() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		g_gameScene = GAME_SELECT;
	}
}