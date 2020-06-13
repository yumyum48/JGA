#include"DxLib.h"
#include "Macro.h"
#include "Change_ScReen_Animation.h"
#include "Struct.h"
#include "GameScene.h"
#include "Map.h"
#include "Player.h"
#include "Rain.h"
#include "Select.h"

enum {
	HUSUMA_LEFT,
	HUSUMA_RIGHT,
	HUSUMA_LEFT_CLOSE,
	HUSUMA_RIGHT_CLOSE,
	HUSUMA_OPEN,
};

animationInfo g_disp[2];
int g_openFlg = HUSUMA_RIGHT_CLOSE;

void ChangeScreen_Animation() {
	
	MapDisp();			// �}�b�v�̕\��
	RainDisp();			// �J�̕\��
	RainMove();			// �J�̓���
	PlayerDisp();		// �v���C���[�̕\��
	
	if (g_openFlg != HUSUMA_OPEN) {
		SelectDisp();
	}
	scene_animaInput anima = Get_NowDisp(0, 0);
	if (anima.animeType == 1) {
		DrawGraph(g_disp[0].x, g_disp[0].y, anima.nowDisp[0], TRUE);
	}
	else if (anima.animeType == 2) {

		DrawRotaGraph2(g_disp[0].x, g_disp[0].y, 0, 0, 8.0, 0.0, anima.nowDisp[0], TRUE);
		DrawRotaGraph2(g_disp[1].x, g_disp[1].y, 0, 0, 8.0, 0.0, anima.nowDisp[1], TRUE);
		Scene_Animation_Shoji(anima.nextScene);
	}
}

void Scene_Animation_Shoji(int nextScene) {
	int move = 15;
	if (g_openFlg == HUSUMA_RIGHT_CLOSE) {		// �߂�A�j���[�V����
		if (g_disp[HUSUMA_RIGHT].x >=  (WINDOW_WIDTH / 2)) {
			g_disp[HUSUMA_RIGHT].x -= move;
		}
		else {
			g_openFlg = HUSUMA_LEFT_CLOSE;
		}
	}
	if (g_openFlg == HUSUMA_LEFT_CLOSE) {		// �߂�A�j���[�V����
		if (g_disp[HUSUMA_LEFT].x + (WINDOW_WIDTH / 2) <= (WINDOW_WIDTH / 2)) {
			g_disp[HUSUMA_LEFT].x += move;
		}
		else {
			g_openFlg = HUSUMA_OPEN;
		}
	}
	if (g_openFlg == HUSUMA_OPEN) {		// �߂�A�j���[�V����
		if ((g_disp[HUSUMA_LEFT].x + (WINDOW_WIDTH / 2)) + WINDOW_WIDTH > 0) {		// ���̏�q
			g_disp[HUSUMA_LEFT].x -= move;
		}

		if (g_disp[HUSUMA_RIGHT].x < WINDOW_WIDTH) {									// �E�̏�q
			g_disp[HUSUMA_RIGHT].x += move;
		}
		else {
			ChangeScreen_Animation_Init();									// �A�j���[�V�������I�����Ă����珉����
			g_openFlg = HUSUMA_RIGHT_CLOSE;									// �I�[�v���t���O��������
			g_gameScene = nextScene;										// �V�[���؂�ւ�
		}
	}
}
scene_animaInput Get_NowDisp(int nextScene, int animeType) {	// �V�[����ς��鎞�̃A�j���[�V�����̏����i�[���ĕԂ�l�Ƃ��ĕԂ��֐� ���� (int ���̃V�[��, int �g�p����A�j���[�V�����̔ԍ�)
	
	static scene_animaInput animation_Info;	// �A�j���[�V�����ɕK�v�ȏ����i�[����ϐ�

	if(animeType == 1) {
		SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// �A�j���[�V�����p�̉摜����U�t�H���_�֕ۑ�
		animation_Info.nowDisp[0] = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//�A�j���[�V�����摜�����[�h
		animation_Info.nextScene = nextScene;	// �󂯎�������̃V�[�����i�[
		animation_Info.animeType = animeType;	// �󂯎�����A�j���[�V�����^�C�v���i�[
	
	}
	else if (animeType == 2) {
		//SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// �A�j���[�V�����p�̉摜����U�t�H���_�֕ۑ�
		LoadDivGraph("image/�ӂ���.png", 2, 2, 1, 80, 96, animation_Info.nowDisp, 0);//�A�j���[�V�����摜�����[�h
		for (int i = 0; i < 2; i++) {
			g_disp[i].ShoujiInit(i);
		}
		animation_Info.nextScene = nextScene;	// �󂯎�������̃V�[�����i�[
		animation_Info.animeType = animeType;	// �󂯎�����A�j���[�V�����^�C�v���i�[
	}

	//switch (animeType) {
	//case 1:
	//	SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// �A�j���[�V�����p�̉摜����U�t�H���_�֕ۑ�
	//	animation_Info.nowDisp = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//�A�j���[�V�����摜�����[�h
	//	animation_Info.nextScene = nextScene;
	//	animation_Info.animeType = animeType;
	//	break;
	//case 2:
	//	break;
	//default:
	//	break;
	//}

	return animation_Info;

}

void ChangeScreen_Animation_Init() {
	for (int i = 0; i < 2; i++) {
		g_disp[i].Init(i);			// �A�j���[�V�����p�̉�ʂ�����������
	}

	g_openFlg = HUSUMA_RIGHT_CLOSE;	// �I�[�v���t���O��������
}