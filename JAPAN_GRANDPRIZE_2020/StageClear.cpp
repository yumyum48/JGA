//// �v���C���[�̒��S����~���ł�
//DrawCircle(g_player.x + 102, g_player.y + 111, 10, TRUE);

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
#include "Init.h"
#include "Picture.h"
#include "Boss.h"
#include "Select.h"

bool g_animationScene = FALSE;	// �A�j���[�V�������I�������ăe�L�X�g��\��������t���O	TRUE:�e�L�X�g�̕\��ON	FALSE:�{�X�����j����A�j���[�V������

picInfo g_clearText;			// �N���A�������́u���������I�I�v�̉摜
void StageClear() {
	StageClearMove();		// �X�e�[�W�N���A�̓���
	StageClearDisp();		// �X�e�[�W�N���A�̕\��
}


void StageClearDisp() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationDisp();
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		MapDisp();				// �}�b�v�̕\��
		PlayerDisp();			// �v���C���[�̕\��
		RainDisp();				// �J�̕\��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph2(g_clearText.x, g_clearText.y, 0, 0, 0.6, 0.0, g_pic.stageClearText, TRUE);


		DrawString(g_mouseInfo.mouseX, g_mouseInfo.mouseY, "A�{�^���������ƃ��j���[��ʂ֖߂�܂�", 0xFF0000); // A�{�^���������ƃZ���N�g��ʂɖ߂�܂�
		//DrawModiGraph
		//DrawBox(clearText.x, clearText.y)
	}
}

void StageClearMove() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationMove();
	}
	else {
		RainMove();				// �J�̓���

		if (Player_StageClearMove() == 1) {
			if (ClearTextMove() == 1) {
				SetFontSize(39);

				if (g_keyInfo.keyFlg & PAD_INPUT_A) {

					GameInit();
					g_gameScene = GAME_SELECT;
				}
			}
		}
	}
}

int ClearTextMove() {
	if (g_clearText.y < 298) {
		g_clearText.y += 25;
	}
	else {
		g_clearText.y = 298;
		return 1;
	}

	return 0;
}
int Player_StageClearMove() {
	
	if (g_player.y > GROUND) {	// ��l���������Ă�����n�ʂɗ��Ƃ�
		g_player.y += 10;
	}
	else {
		g_player.y = GROUND;
	}

	if (g_player.x < 500) {	// ��l����X���W���ړ������ČŒ�
		g_player.x += 10;
	}
	else {
		g_player.x = 500;
		
		// �v���C���[�Î~���[�V����
		return 1;
	}

	if (g_player.attackFlg == TRUE) g_player.attackFlg = FALSE;
	if (g_player.swordFlg == TRUE) g_player.swordFlg = FALSE;
	
	return 0;
}

// �{�X���j���̃A�j���[�V�����@�`��
void BossDefeatAnimationDisp() {
	MapDisp();						// �}�b�v�̕\��

	(*BossDisp[g_select_Stage])();	// �{�X�̕\��
	PlayerDisp();					// �v���C���[�̕\��

	RainDisp();						// �J�̕\��
}

// �{�X���j���̃A�j���[�V�����@��������
void BossDefeatAnimationMove() {
	static int animationDelay = 0;		// ���������̃e�L�X�g�\���܂ł̃A�j���[�V��������
	static bool animationFlg = FALSE;	// �{�X���j�̃A�j�����N��������t���O	TRUE:�A�j���̊J�n	FALSE:����U�肫��P�\����
	
	animationDelay++;

	// �v���C���[������U��؂�P�\����
	if (animationFlg == FALSE) {
		if (animationDelay % 15 == 0) {
			RainMove();		// �J�̓���
		}
	}
	// �{�X�����j����A�j���[�V����
	else {

	}

	// �A�j���[�V�������Ԃ̊Ǘ�
	if (animationDelay > 200) {			// �A�j���[�V�����I�����̏���������
		g_animationScene = TRUE;
		animationDelay = 0;
	}
}

void StageClearInit() {
	g_clearText.x = 279;
	g_clearText.y = -237;

}