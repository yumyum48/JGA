#include"DxLib.h"
#include "Macro.h"
#include "Change_ScReen_Animation.h"
void ChangeScreen_Animation() {
	scene_animaInput anima = Get_NowDisp(0, 0);
	DrawGraph(0, 0, anima.nowDisp, TRUE);
}

scene_animaInput Get_NowDisp(int nextScene, int animeType) {	// �V�[����ς��鎞�̃A�j���[�V�����̏����i�[���ĕԂ�l�Ƃ��ĕԂ��֐� ���� (int ���̃V�[��, int �g�p����A�j���[�V�����̔ԍ�)
	
	static scene_animaInput animation_Info;	// �A�j���[�V�����ɕK�v�ȏ����i�[����ϐ�

	if(animeType != 0) {
		SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// �A�j���[�V�����p�̉摜����U�t�H���_�֕ۑ�
		animation_Info.nowDisp = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//�A�j���[�V�����摜�����[�h
		animation_Info.nextScene = nextScene;
		animation_Info.animeType = animeType;
	
	}

	return animation_Info;

}
