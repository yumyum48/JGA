#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"

// �ア�G�A�{�X�̕\��
void MonsterDisp() {
	if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
		EnemyDisp[g_select_Stage]();				// �ア�G�̕`��
	}
	else {
		BossDisp[g_select_Stage]();					// �{�X�̕\��
	}
}

// �ア�G�A�{�X�̓���
void MonsterMove() {
	if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
		EnemyMove();								// �ア�G�̓���
	}
	else {
		BossMove[g_select_Stage]();					// �{�X�̓���
	}
}


// �ア�G�̓���
void EnemyMove() {
	

	for (int i = 0; i < ENEMY_MAX; i++) {		//�n��̓G�̓���
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= g_speedLevel+3;
			//g_enemy[i].walk.y = GROUND;
		}

		if (g_enemy[i].walk.x+ENEMY_WIDTH < 0) {
			/*for (int j = 0; j < walkEnemy_pop - 1; j++) {
				g_enemy[i + j].walk = g_enemy[i + j + 1].walk;
			}
			walkEnemy_pop -= 1;*/

			//g_enemy[i].walk.flg = FALSE;

			g_enemy[i].walk.WalkInit();
		}

		//if (g_button.circleButton == true) g_enemy[i].walk.Init();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {		//�󒆂̓G�̓���
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= g_speedLevel+3;
			g_enemy[i].fly.y = (GROUND - ENEMY_HEIGHT) - 200;
		}

		if (g_enemy[i].fly.x + ENEMY_WIDTH < 0) {

			g_enemy[i].fly.FlyInit();
		}

	}
}

// �G���j���̃A�j���[�V����
int EnemyEvaporation(){
	const int animationMax = 5;
	// 0�Ԗڂ͐����Ԃ��̃A�j���[�V����,1�Ԗڂ͏����̃A�j���[�V����
	static int anime[ENEMY_MAX][2] = { { 0, 0},	
										{ 0, 0},
										{ 0, 0},
										{ 0, 0},
										{ 0, 0} };
	static int time[ENEMY_MAX]  = { 60, 60, 60, 60, 60 };
	static float moveX[ENEMY_MAX] = { 0, 0, 0, 0, 0 },
				moveY[ENEMY_MAX] = { 0, 0, 0, 0, 0 };
	static int cntFlg[ENEMY_MAX] = { FALSE, FALSE, FALSE, FALSE, FALSE };

	// �󂢂Ă�ϐ��Ɉړ�
	for (int i = 0; i < ENEMY_MAX - 2; i++) {
		for (int j = i; j < ENEMY_MAX - 1; j++) {
			if (g_enemyBuffer[j].flg == FALSE
				&& g_enemyBuffer[j].flg != g_enemyBuffer[j + 1].flg) {
				g_enemyBuffer[j].flg = TRUE;
				g_enemyBuffer[j].x = g_enemyBuffer[j + 1].x;
				g_enemyBuffer[j].y = g_enemyBuffer[j + 1].y;
				g_enemyBuffer[j + 1].flg = FALSE;
			}
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		for(int j=0;j<ENEMY_MAX;j++){

			/*if (cntFlg[i] == FALSE
				&& g_enemyBuffer[i].flg == TRUE) {
				cntFlg[i] = TRUE;
			}*/

			// �A�j���[�V����
			if (g_enemyBuffer[i].flg == TRUE){
				if (anime[i][0] < animationMax) {
					if (time[i]++ % 24 == 23)anime[i][0]++;
				}
				else if (anime[i][1] < animationMax) {
					if (time[i]++ % 36 == 35)anime[i][1]++;
				}
			}

			// �A�j���[�V�����I�����̏���������
			/*if (anime[i] >= animationMax
				&& g_enemyBuffer[i].flg == TRUE) {
				anime[i] = 0;
				g_enemyBuffer[i].flg = FALSE;
				cntFlg[i] = FALSE;
			}*/

			// �t���O�� �^�̎��A�j���[�V������\��
			if (g_enemyBuffer[i].flg == TRUE){
				if (anime[i][0] < animationMax) {
					moveX[i] -= g_speedLevel / 5;
					DrawRotaGraph(g_enemyBuffer[i].x + moveX[i], g_enemyBuffer[i].y,
						3.0f, /*DX_PI_F / 180 * 335*/0.0, g_pic.enemySplashes[anime[i][0]], TRUE, FALSE);
				}
				else if (anime[i][1] < animationMax) {
					moveX[i] -= g_speedLevel / 5;
					moveY[i] -= g_speedLevel / 10;
					DrawRotaGraph(g_enemyBuffer[i].x + 150 + moveX[i], g_enemyBuffer[i].y - 70 + moveY[i],
						1.0f, 0.0, g_pic.enemyVapour[anime[i][1]], TRUE, FALSE);
				}
			}
		}

	}

	// �A�j���[�V�����I�����̏���������
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (anime[i][1] >= animationMax
			&& g_enemyBuffer[i].flg == TRUE) {
			anime[i][0] = 0;
			anime[i][1] = 0;
			moveX[i] = 0;
			moveY[i] = 0;
			g_enemyBuffer[i].flg = FALSE;
			cntFlg[i] = FALSE;
			g_enemybeat++;			// �G�l�~�[��|���������J�E���g
			return 1;
		}
	}
	return 0;
}

// �����G�̏�����
void enemyInfo::WalkInit() {                 // �G�̏�����
	x = 1280;								 // �G��X���W�̏����ʒu
	y = GROUND - ENEMY_HEIGHT;       // �G��Y���W�̏����ʒu
	flg = FALSE;							 // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
	anime = 0;								 // �A�j���[�V�����̏�����
}

// ��ԓG�̏�����
void enemyInfo::FlyInit() {
	x = 1280;                      // �G��X���W�̏����ʒu
	y = GROUND - ENEMY_HEIGHT;               // �G��Y���W�̏����ʒu
	flg = FALSE;                   // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
	anime = 0;                     // �A�j���[�V�����̏�����
}
// �{�X�G���A�̕����G���G�̏�����
void enemyInfo::BossArea_WlakInit(int bx, int by) {
	x = bx - ENEMY_WIDTH;          // �G��X���W�̏����ʒu
	y = GROUND - ENEMY_HEIGHT;     // �G��Y���W�̏����ʒu
	flg = FALSE;                   // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
	anime = 0;                     // �A�j���[�V�����̏�����
}
// �{�X�G���A�̃~�j�_�̏�����
void enemyInfo::BossArea_CloudInit(int bx, int by) {   //�@�{�X�G���A�̃~�j�_�̏�����

	x = bx - ENEMY_WIDTH;            // �G��X���W�̏����ʒu
	y = (GROUND - ENEMY_HEIGHT) - 200;                // �G��Y���W�̏����ʒu
	flg = FALSE;                    // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
	anime = 0;                      // �A�j���[�V�����̏�����
}
// �{�X�G���A�̃~�j�w偂̏�����
void enemyInfo::BossArea_SpiderInit(int bx, int by) {   //�@�{�X�G���A�̃~�j�w偂̏�����
	
	x = bx - ENEMY_WIDTH;                 // �G��X���W�̏����ʒu
	y = GROUND - ENEMY_HEIGHT;                          // �G��Y���W�̏����ʒu
	flg = FALSE;                         // �G��\�����Ă��邩�ǂ����̃t���O TRUE:�\�����Ă��� FALSE:�\�����Ă��Ȃ�
	anime = 0;                           // �A�j���[�V�����̏�����
}
// �{�X�G���A�̃N���Q�̏�����
void enemyInfo::BossArea_KurageInit(int by) {
	x = WINDOW_WIDTH;
	y = by;
	flg = FALSE;
	anime = 0;
}
// �ア�G�̏�����
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.WalkInit();
		g_enemy[i].fly.FlyInit();

	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemyBuffer[i].BufferInit();
	}
	
	//g_coolTime = 0;
}