#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Player.h"
#include "control.h"
#include "Controler.h"
#include "Select.h"
#include "GameScene.h"
#include "Init.h"
#include "Trap.h"
#include "HP.h"

#include <math.h>
/*********************************************

* �萔�̐錾

*/////////////////////////////////////////////

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
/*********************************************

* �X�e�[�W�U�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage6() {
	static int anime = 0;							// �v���C���[�̉摜��ς���
	static int time = 0;							// �摜��؂�ւ���^�C�~���O����
	//// �{�X�̑傫�����郁�[�^�[
	//static int bw = 0;
	//static int bh = 0;
	//if (g_keyInfo.nowKey & PAD_INPUT_UP) {
	//	bh--;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
	//	bw++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
	//	bh++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
	//	bw--;
	//}

	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);


	if (++time % 4 == 0) anime++;

	// �{�X�̕\��
	DrawBox(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, g_boss[BOSS_STAGE6].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE6].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	//DrawRotaGraph2()


}

// ����
void BossMove_Stage6() {
}