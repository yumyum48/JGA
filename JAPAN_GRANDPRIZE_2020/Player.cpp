
#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "HP.h"
#include "Skill.h"
#include "Select.h"

#define G                (0.5F)		// �d��
#define JUMP_POWER       (15.0F)	// �W�����v��



float g_speed = 0.0F;	//�����鑬�x
int g_resetMotion = 0;	//�A�j���[�V�����n�_
int g_maxMotion = 7;	//�I�_
int g_attackTime = 0;	//�U���̃N�[���^�C��
bool g_skillFlg;		// �X�L�������ǂ����̃t���O
int g_SkillSelectAicon = 0; //�X�L���̃A�C�R���ړ�
//bool g_swordFlg = FALSE; //TRUE = ����, FALSE = �[��

void PlayerDisp() {
	static int anime = 0;							// �v���C���[�̉摜��ς���
	static int time = 0;							// �摜��؂�ւ���^�C�~���O����
	static float skillTime[3] = { 0 };				// �X�L���N�[���^�C��
	static int skill6Anime[2] = { 0 };				//�X�L��6�A�j���[�V����

	if (++time % 4 == 0) anime++;
	if (anime < g_resetMotion || anime > g_maxMotion) anime = g_resetMotion;

	if (g_player.barrierFlg == TRUE) {
		//�X�L��6�o���A�\��
		if (skill6Anime[0] < 150 && skill6Anime[1] == 0) skill6Anime[0] += 5;
		if (skill6Anime[0] > 50 && skill6Anime[1] == 1) skill6Anime[0] -= 5;
		if (skill6Anime[0] >= 150) skill6Anime[1] = 1;
		if (skill6Anime[0] <= 50) skill6Anime[1] = 0;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 + skill6Anime[0]);
		DrawGraph(g_player.x - 80, g_player.y - 300, g_pic.skillEffect[20], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - skill6Anime[0]);
		DrawGraph(g_player.x - 80, g_player.y - 300, g_pic.skillEffect[21], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (g_player.powerUpFlg == TRUE) {//�X�L��5�@��
		DrawBox(g_player.x, g_player.y, g_player.x + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0x00ffff, TRUE);
		if (g_player.powerUpTime > 0) g_player.powerUpTime--;
		else {
			if (g_player.jumpFlg == FALSE) {
				g_noDamageCnt = 0;
				if (g_player.x < 1000) g_player.x += 50, g_player.jumpFlg == FALSE, EnemyCut();
				else g_player.powerUpTime = SKILL5_TIME, g_player.powerUpFlg = FALSE;
			}
		}
	}

	// �c��
	PlayerAfterimage(anime);
	//�v���C���[�̕`��
	if (g_player.attackFlg == FALSE && g_noDamageCnt >= 60) {
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime], TRUE);
	} else if (g_noDamageCnt <= 60) {
		if (g_noDamageCnt % 12 == 0) //���G���Ԕ�����
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[48], TRUE);
	}
	DrawFormatString(500, 0, 0xff0000, "%d", g_attackTime);
	DrawFormatString(600, 0, 0xffffff, "%d", g_boss[g_select_Stage].hp);
	DrawFormatString(0, 400, 0xFF0000, "%d", g_player.skillFlg);
	DrawFormatString(0, 600, 0xFFFF00, "%f", g_player.skillCoolTime[g_player.skillNo]);
	DrawFormatString(0, 700, 0x00FFFF, "%d", g_player.skillNo);
	DrawFormatString(0, 750, 0x0000FF, "%d", g_player.powerUpTime);
	
	if (g_player.skillFlg != 0) {
		SkillDisp[g_player.skillFlg - 1](g_maxMotion, g_resetMotion);
	}

	//��
	//static float gauge = 320;
	DrawGraph(20, -40, g_pic.PlayerUI, TRUE);					//�A�C�R��
	//DrawBox(80, 120, 80 + gauge, 130, 0xFF0000, TRUE);
	DrawRectGraph(75,-40,0,0,g_player.gauge,240,g_pic.gauge,TRUE,FALSE); //�Q�[�W
	if (g_player.swordFlg == TRUE) {
		if (g_player.gauge > 0) g_player.gauge -= 0.1;
	} else {
		if (g_player.gauge < 265 && g_player.useSkillGage <= 0) g_player.gauge += 0.5;
	}

	//�X�L���g�p���̃Q�[�W����
	//if (g_player.attackFlg == TRUE) g_player.gauge -= 2;
	if (g_player.useSkillGage > 0) {
		g_player.useSkillGage -= g_player.skillFlg;
		g_player.gauge -= g_player.skillFlg;
	}

	if (g_player.gauge < 0) g_player.gauge = 0;

	//�X�L���̍Ďg�p�܂ł̃N�[���^�C��
	for (int i = 0; i < 3; i++) {
		if ((g_keyInfo.keyFlg & PAD_INPUT_A) && skillTime[i] <= 0) {
			if (g_player.swordFlg == FALSE) {
				skillTime[i] = g_player.skillCoolTime[i];
			}else {
				g_player.skillCoolTime[i] = g_player.skillCoolTime[i] / 2;
				skillTime[i] = g_player.skillCoolTime[i];
			}
		}
		if (g_player.skillCoolTime[i] > 0) g_player.skillCoolTime[i] -= 0.1F;
		if (g_player.skillCoolTime[i] < 0) g_player.skillCoolTime[i] = 0.0F, skillTime[i] = 0;
	}

	//�X�L�����\��
	DrawRotaGraph(WINDOW_WIDTH / 2 + g_SkillSelectAicon, WINDOW_HEIGHT - 70, 1, -time / 8, g_pic.skillRing[0], TRUE);
	//�������Ă���X�L���\��
	DrawGraph(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[0]], TRUE);
	DrawGraph(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[1]], TRUE);
	DrawGraph(WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT - 120, g_pic.skillAicon[g_player.skillcustom[2]], TRUE);

	//�N�[���^�C��
	SetDrawBright(255, 0, 0);
	DrawCircleGauge(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[0] / skillTime[0]) * float(100), g_pic.skillAicon[g_player.skillcustom[0]]);
	DrawCircleGauge(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[1] / skillTime[1]) * float(100), g_pic.skillAicon[g_player.skillcustom[1]]);
	DrawCircleGauge(WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT - 70, (g_player.skillCoolTime[2] / skillTime[2]) * float(100), g_pic.skillAicon[g_player.skillcustom[2]]);
	SetDrawBright(255, 255, 255);

	//���ʕ\��
	DrawRotaGraph(WINDOW_WIDTH / 2 + g_SkillSelectAicon, WINDOW_HEIGHT - 70, 1, time / 8, g_pic.skillRing[1], TRUE);

}

void PlayerMove() {
	PlayerJump();		// �v���C���[�̃W�����v����
	PlayerControl();	// �v���C���[�𑀍삷��֐�
	PlayerAnimation();
	//if (g_player.skillFlg != 0) {
	//	SkillMove[g_player.skillFlg - 1]();
	//}
}

// �v���C���[�̎c��
void PlayerAfterimage(int anime) {
	static int resetMotion_Buf[3] = { 0, 0, 0 };		// �}�C�t���[���̃v���C���[�̃A�j���[�V�������i�[
	static int maxMotion_Buf[3] = { 0, 0, 0 };		// �}�C�t���[���̃v���C���[�̃A�j���[�V�������i�[
	if (g_player.swordFlg == TRUE) {
		int anime_Buf = anime - 1;					// �ߋ��̃v���C���[�A�j���[�V�������i�[����
		resetMotion_Buf[2] = resetMotion_Buf[1];
		resetMotion_Buf[1] = resetMotion_Buf[0];
		resetMotion_Buf[0] = g_resetMotion;

		maxMotion_Buf[2] = maxMotion_Buf[1];
		maxMotion_Buf[1] = maxMotion_Buf[0];
		maxMotion_Buf[0] = g_maxMotion;

		for (int i = 0; i < 3; i++) {
			if (anime_Buf < resetMotion_Buf[i] || anime_Buf > maxMotion_Buf[i]) anime_Buf = resetMotion_Buf[i];
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			// �c���v���C���[�\��
			//g_player.y = g_mouseInfo.mouseY;
			DrawRotaGraph2(g_player.x - ((i + 1) * 30), g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime_Buf], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

//�v���C���[�̃A�j���[�V����
void PlayerAnimation() {
	//static int time = 0;	//�����A�[���̐؂�ւ�
	if (g_player.swordFlg == FALSE) {
		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_player.timecount = 10;
		}
	} else {
		if (g_keyInfo.keyFlg & PAD_INPUT_4){
			g_player.timecount = 10;
		}
	}

	//�[����Ԃ̃A�j���[�V����
	if (g_player.swordFlg == FALSE) {
		if (g_player.jumpFlg == TRUE) {		//�W�����v
			if (g_speed < 0) {
				g_resetMotion = CLOSE_JUMP_UP;
				g_maxMotion = CLOSE_JUMP_UP;
			}
			else {
				g_resetMotion = CLOSE_JUMP_DOWN_S;
				g_maxMotion = CLOSE_JUMP_DOWN_E;
			}
		}
		else {
			g_resetMotion = CLOSE_MOVE_S;
			g_maxMotion = CLOSE_MOVE_E;
		}
		if (g_player.attackFlg == TRUE) {//�X�L���U��(��)
			g_resetMotion = 32;
			g_maxMotion = 32;
		}
	}

	//������Ԃ̃A�j���[�V����
	if (g_player.swordFlg == TRUE) {
		if (g_player.jumpFlg == TRUE) {		//�W�����v
			if (g_speed < 0) {
				g_resetMotion = OPEN_JUMP_UP;
				g_maxMotion = OPEN_JUMP_UP;
			}
			else {
				g_resetMotion = OPEN_JUMP_DOWN_S;
				g_maxMotion = OPEN_JUMP_DOWN_E;
			}
		}
		else {
			g_resetMotion = OPEN_MOVE_S;
			g_maxMotion = OPEN_MOVE_E;
		}
		if (g_player.attackFlg == TRUE) {//�X�L���U��(��)
			g_resetMotion = 32;
			g_maxMotion = 32;
		}
	}
	if (g_player.timecount <= 10 && g_player.swordFlg == FALSE) {//�ʏ펞�̔���
		if (--g_player.timecount > 0) g_resetMotion = SWORD_OPEN_S, g_maxMotion = SWORD_OPEN_E;
	}
	if (g_player.timecount == 0 && g_player.swordFlg == FALSE) {
		g_player.swordFlg = TRUE;
		if(g_player.useSkillFlg == TRUE) g_player.attackFlg = TRUE;
	}
	if (g_player.timecount <= 10 && g_player.swordFlg == TRUE) {//�[��
		if (--g_player.timecount > 0) g_resetMotion = SWORD_CLOSE_S, g_maxMotion = SWORD_CLOSE_E;
	}
	if (g_player.timecount == 0 && g_player.swordFlg == TRUE) {
		g_player.swordFlg = FALSE;
		g_player.useSkillFlg = FALSE;
	}

	if (g_boss[g_select_Stage].hp <= 0) {
		g_resetMotion = CLOSE_MOVE_S;
		g_maxMotion = CLOSE_MOVE_E;
	}
}

// �W�����v����
void PlayerJump() {
	//�W�����v����(�~�{�^��)
	if (g_player.jumpFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_2) {
		g_speed = -JUMP_POWER;
		g_player.jumpFlg = TRUE;
	}

	g_player.y += g_speed;
	g_speed += G;

	if (g_player.y >= GROUND - PLAYER_HEIGHT) {
		g_player.jumpFlg = FALSE;
		g_speed = 0.0F;
		g_player.y = GROUND - PLAYER_HEIGHT;
	}
}
// �{�^�������������̏���
void PlayerControl() {
	//�U��(�Z�{�^��)
	//if (g_player.attackFlg == FALSE && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if ((g_player.attackFlg == FALSE && g_skillFlg == TRUE) && g_keyInfo.keyFlg & PAD_INPUT_3) {
	//if(g_skillFlg == TRUE){
		//g_player.x += 500.0F;
		//g_player.attackFlg = TRUE;
	//}

	//if (g_keyInfo.keyFlg & PAD_INPUT_3) {
	//	g_player.attackFlg = TRUE;
	//}

	if (g_player.attackFlg == TRUE) {
		g_attackTime++;
	}
	if (g_attackTime > 20) {
		g_attackTime = 0;
		g_player.attackFlg = FALSE;
		if(g_player.useSkillFlg == TRUE)g_player.timecount = 10;

	}
	if (g_player.x > 100 && g_player.attackFlg == FALSE && g_player.y >= GROUND - PLAYER_HEIGHT) {
		g_player.x -= 5.0F;
	}

	if (g_player.x < 100) g_player.x = 100;


	//�ʏ�U��
	/*if (g_player.skillFlg == 0 && (g_keyInfo.keyFlg & PAD_INPUT_3)) {
		//g_player.attackFlg = TRUE;
		EnemyCut();		// �G�l�~�[��|������
	}*/


	//(���{�^��??)
	if (g_button.squareButton == true) {

	}
	
	static int cnt = 0;
	// �X�L���I���I�t
	SkillChange();
	/*
	if (g_player.skillFlg != 0) {
		if (g_keyInfo.keyFlg & PAD_INPUT_4)
			g_player.skillFlg = 0;
	}
	else {

		if (g_keyInfo.keyFlg & PAD_INPUT_4) {
			g_player.skillFlg = SkillChange();

		}
	}*/
	g_player.skillFlg = SkillChange();

}

int SkillChange() {
	static int skillNum = 0; //�z��
	static int useSkill = 1; //�g���X�L��

	if (g_player.attackFlg == FALSE) {
		// �X�L���I��
		if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
			if (++skillNum > 2) skillNum = 0,SkillInit();
		}
		if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
			if (--skillNum < 0) skillNum = 2, SkillInit();
		}
	}

	if (skillNum == 0) g_SkillSelectAicon = 0;
	if (skillNum == 1) g_SkillSelectAicon = -100;
	if (skillNum == 2) g_SkillSelectAicon = 100;

	// skillNum�̒��g
	DrawFormatString(0, 500, 0xFEFFFF, "%d", skillNum);
	
	g_player.skillNo = skillNum;

	useSkill = g_player.skillcustom[skillNum];

	return useSkill;
}


// �G���ԍ����ɓ������烍�b�N�I�������鏈��
void EnemyLockOn() {
	DrawBox(g_player.x + PLAYER_WIDTH, g_player.y, g_player.x + PLAYER_WIDTH + PLAYER_WIDTH, g_player.y + PLAYER_HEIGHT, 0xFF0000, 0);
	EnemyCut();		// �G�l�~�[��|������
}

// �v���C���[�̊ԍ����ɓ����Ă���G��|������
void EnemyCut() {
	static int enemyNum = 0;	// �����ɓ|�����G���J�E���g����ϐ�
	static int noDamageCnt = 61;// �{�X�̖��G����

	for (int i = 0; i < ENEMY_MAX; i++) {
		// �����G
		if ((g_enemy[i].walk.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
			|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].walk.x, g_enemy[i].walk.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].walk.x + (ENEMY_WIDTH / 3), g_enemy[i].walk.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].walk.WalkInit();
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].walk.x, g_enemy[i].walk.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].walk.WalkInit();
				}
				else {
					g_enemy[i].walk.BossArea_WlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
				}
				//g_player.attackFlg = TRUE;
			}
		}
		// ���ł���G
		if ((g_enemy[i].fly.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
			|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].fly.x, g_enemy[i].fly.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].fly.x + (ENEMY_WIDTH / 3), g_enemy[i].fly.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_player.skillFlg == 2) {
				//g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].fly.WalkInit();
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				/*if (g_skillFlg == TRUE) g_player.x = g_enemy[i].fly.x - PLAYER_WIDTH;
				g_player.y = g_enemy[i].fly.y - PLAYER_HEIGHT;*/
				//g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].fly.x, g_enemy[i].fly.y);
				g_enemy[i].fly.WalkInit();
				//g_player.attackFlg = TRUE;
			}
		}
		// �~�j�w�
		if ((g_enemy[i].spider.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].spider.x, g_enemy[i].spider.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
				|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].spider.x, g_enemy[i].spider.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].spider.x + (ENEMY_WIDTH / 3), g_enemy[i].spider.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].spider.WalkInit();
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].spider.x, g_enemy[i].spider.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].spider.WalkInit();																// �|���ꂽ�珉����
				}
				else {
					g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	// �{�X�G���A�œ|���ꂽ�ꍇ���������@��ς���
				}
				//g_player.attackFlg = TRUE;
			}
		}
		// �~�j�_
		if ((g_enemy[i].cloud.flg == TRUE)
			&& ((PlayerInterval(g_enemy[i].cloud.x, g_enemy[i].cloud.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE)
				|| (SkillMove[g_player.skillFlg - 1](g_enemy[i].cloud.x, g_enemy[i].cloud.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE))) {
			// ���e�B�N���\��
			DrawRotaGraph2(g_enemy[i].cloud.x + (ENEMY_WIDTH / 3), g_enemy[i].cloud.y + (ENEMY_HEIGHT / 3), 0, 0, 0.2, 0.0, g_pic.reticle, TRUE);
			// �G��|������
			if (g_player.skillFlg == 2) {
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemy[i].cloud.FlyInit();
			}
			//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			if (g_player.attackFlg == TRUE) {
				//if(g_skillFlg == TRUE) g_player.x = g_enemy[i].walk.x - PLAYER_WIDTH;
				g_enemybeat++;			// �G�l�~�[��|���������J�E���g
				g_enemyBuffer[enemyNum++].BufferAssignment(g_enemy[i].cloud.x, g_enemy[i].cloud.y);
				if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
					g_enemy[i].cloud.WalkInit();																// �|���ꂽ�珉����
				}
				else {	
					g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	// �{�X�G���A�œ|���ꂽ�ꍇ���������@��ς���
				}
				//g_player.attackFlg = TRUE;
			}
		}
	}
	//boss
	if (g_enemybeat > ENEMY_BEAT_MAX[g_select_Stage]) {
		if (PlayerInterval(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE
			|| (SkillMove[g_player.skillFlg - 1](g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, BOSSFULL_WIDTH[g_select_Stage], BOSSFULL_HEIGHT[g_select_Stage]) == TRUE)) {
			if (++noDamageCnt > 60 && g_boss[g_select_Stage].hp > 0) {
				if (g_player.skillFlg == 2) {
					g_boss[g_select_Stage].hp -= 1;
					noDamageCnt = 0;
				}
				//if (g_keyInfo.keyFlg & PAD_INPUT_A) {
				if (g_player.attackFlg == TRUE) {
					//if (g_skillFlg == TRUE) g_player.x = g_boss[0].x - PLAYER_WIDTH;
					if (g_player.skillFlg == 1) g_boss[g_select_Stage].hp -= 2;
					if (g_player.skillFlg == 3) g_boss[g_select_Stage].hp -= 3;
					if (g_player.powerUpFlg == TRUE) g_boss[g_select_Stage].hp -= 1;
					noDamageCnt = 0;
				}

				if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {
					g_boss[g_select_Stage].hp -= 5;
					noDamageCnt = 0;
				}
			}
		}
		// ��
		if (PlayerInterval(g_boss4_Thread.x, g_boss4_Thread.y, (g_boss4_Thread.w - g_boss4_Thread.x), (g_boss4_Thread.h - g_boss4_Thread.y)) == TRUE
			|| (SkillMove[g_player.skillFlg - 1](g_boss4_Thread.x, g_boss4_Thread.y, (g_boss4_Thread.w - g_boss4_Thread.x), (g_boss4_Thread.h - g_boss4_Thread.y)) == TRUE)) {
			if (++noDamageCnt > 60 && g_boss4_Thread.hp <= 0) {
				DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, TRUE);
			}
		}
	}

	enemyNum = 0;
}
// �v���C���[�̉摜�ƓG�̉摜�̓����蔻�� (TRUE: �������� | FALSE: ������Ȃ�����)
bool PlayerInterval(int ex, int ey, int ew, int eh) {
	//�ʏ�U������
	if (g_player.skillFlg == 0) {
		if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
			&& ((long int)g_player.x + (long int)PLAYER_WIDTH /*+ (long int)PLAYER_WIDTH*/ >= ex)
			&& ((long int)g_player.y <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
			&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
			return TRUE;
		}
	}

	if (g_player.powerUpFlg == TRUE && g_player.powerUpTime <= 0 && g_player.jumpFlg == FALSE) {

		if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
			&& ((long int)g_player.x + (long int)PLAYER_WIDTH + PLAYER_WIDTH >= ex)
			&& ((long int)g_player.y - (long int)PLAYER_HEIGHT <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
			&& ((long int)g_player.y + (long int)PLAYER_HEIGHT >= ey)) {
			return TRUE;
		}
	}
	////�ԍ������L�т�X�L������
	//if (g_player.skillFlg == 1) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	////��Ԏa���U������i�����j
	////DrawBox(skill_X + g_skillAnime, skill_Y, skill_X + PLAYER_WIDTH + PLAYER_WIDTH + g_skillAnime, skill_Y + PLAYER_HEIGHT, 0x0000ff, true);
	//if (g_player.skillFlg == 2) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	////������ɐL�т�U������i�����j
	//if (g_player.skillFlg == 3) {
	//	if (((long int)g_player.x + (long int)PLAYER_WIDTH + (long int)PLAYER_WIDTH <= ex + ew)		// �G��X���W���A�v���C���[��X���W����������^
	//		&& ((long int)g_player.x + (long int)PLAYER_WIDTH >= ex)
	//		&& ((long int)g_player.y <= ey + eh)		// �G��Y���W���A�v���C���[��Y���W����������^
	//		&& ((long int)g_player.y + PLAYER_HEIGHT >= ey)) {
	//		return TRUE;
	//	}
	//}

	return FALSE;
}

// �v���C���[�̌��̕����̔���𔲂��ɁA�v���C���[���g�̓����蔻��(��ɃG�l�~�[�Ƃ̏Փ˂Ɏg��)(��������:TRUE  �������Ă��Ȃ�����:FALSE)
bool PlayerHitCheck(int ex, int ey, int ew, int eh) {
	if( (g_player.x  <= ex + ew)
	&&	(g_player.x + (PLAYER_WIDTH / 2) >= ex)
	&&	(g_player.y  <= ey + eh)
	&&	(g_player.y + (PLAYER_HEIGHT) >= ey) ){
		
		return TRUE;
	}

	return FALSE;
}

// �v���C���[�̏���������
void playerInfo::Init() {
	x = 100 * PLAYER_REDUCTION;
	y = GROUND - PLAYER_HEIGHT;
	hp = 3;
	attackFlg = FALSE;
	jumpFlg = FALSE;
	skillFlg = 0;
	skillGage = 100;
	skill_MAX = 3;
	gauge = 265;
	swordFlg = FALSE;
	useSkillFlg = FALSE;
	barrierFlg = FALSE;
	powerUpFlg = FALSE;
	powerUpTime = SKILL5_TIME;
	useSkillGage = 0;
	timecount = 0;
	//skillcustom[0] = 1;
	//skillcustom[1] = 0;
	//skillcustom[2] = 0;
	skillCoolTime[0] = 0;
	skillCoolTime[1] = 0;
	skillCoolTime[2] = 0;
	skillNo = 0;
}
// �v���C���[�̏���������
void PlayerInit() {
	g_player.Init();
}