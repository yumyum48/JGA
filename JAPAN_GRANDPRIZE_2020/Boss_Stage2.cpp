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

/*********************************************

* �X�e�[�W�Q�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage2() {
	DrawRotaGraph(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, 0.9f, 0.0, g_pic.enemy_walk[0], FALSE, TRUE);
}

// ����
void BossMove_Stage2() {

}
