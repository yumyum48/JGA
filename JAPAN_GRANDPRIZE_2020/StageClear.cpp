#include "DxLib.h"
#include "Struct.h"
#include "StageClear.h"
#include "GameScene.h"
#include "control.h"
#include "Rain.h"
#include "Player.h"
#include "Macro.h"
#include "Map.h"
#include "Struct.h"

picInfo clearText;			// �N���A�������́u���������I�I�v�̉摜
void StageClear() {
	StageClearMove();		// �X�e�[�W�N���A�̓���
	StageClearDisp();		// �X�e�[�W�N���A�̕\��
}


void StageClearDisp() {
	MapDisp();				// �}�b�v�̕\��
	PlayerDisp();			// �v���C���[�̕\��
	RainDisp();				// �J�̕\��
	//DrawModiGraph
	//DrawBox(clearText.x, clearText.y)
}

void StageClearMove() {
	RainMove();				// �J�̓���
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		g_gameScene = GAME_SELECT;
	}
	if (Player_StageClearMove() == 1) {

	}
}

int Player_StageClearMove() {
	
	if (g_player.y > GROUND) {	// ��l���������Ă�����n�ʂɗ��Ƃ�
		g_player.y += 10;
	}
	else {
		g_player.y = GROUND;
	}

	if (g_player.x < 1200) {	// ��l����X���W���ړ������ČŒ�
		g_player.x += 5;
	}
	else {
		g_player.x = 1200;
		return 1;
	}
	
	return 0;
}

void StageClearInit() {
	clearText.x = WINDOW_WIDTH / 2;
	clearText.y = WINDOW_HEIGHT / 2;

}