#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"

#define DEBUG_TEXT_ON
/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
extern mouse g_mouseInfo;	// �}�E�X�̏�ԊǗ�
extern image g_pic;			// �摜�̊Ǘ�
extern key g_keyInfo;		// �L�[�{�[�h�̏�ԊǗ�
extern int g_gameScene = 0;		// ��ʂ̃V�[���̐���	// 0:�Q�[���^�C�g�� 1:�X�e�[�W�Z���N�g 2:�Q�[���v���C3:�Q�[���I�[�o�[4:�Q�[���N���A

extern DINPUT_JOYSTATE g_controler;
extern controler g_button; 

enum {
	GAME_TYTLE,
	GAME_SELECT,
	GAME_PLAY,
	GAME_OVER,
	GAME_CLEAR,
};
/*********************************************

* �֐��̃v���g�^�C�v�錾

*/////////////////////////////////////////////
// �Q�[���̃��C���v���O����
int Main(void);					// �Q�[���̃��C������
void GameScene(int gameScene);	// ��ʂ̃V�[���Ǘ�


/**************************************************************************

* WinMain�֐�

**************************************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	ChangeWindowMode(TRUE);

	// �E�B���h�E��ʂ̑傫��
	SetGraphMode(1088, 768, 32);
	
	// DX���C�u�����̏�����
	if (DxLib_Init() == -1) return  -1;
	if (LoadPicture() == -1)return  -1;

	// ���C���֐����Ă�
	Main();

	// DX���C�u�����̌�n��
	DxLib_End();

	// �I��
	return 0;
}
/**************************************************************************

*  �Q�[���̃��C���v���O����

**************************************************************************/
int Main(void) {


	

	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		// ��ʂ̃N���A	���`��ނ͂��̊֐��̉��ցI
		ClearDrawScreen();

		// �}�E�X�A�L�[�{�[�h�̍��W�擾��A���͏��̎擾
		ControlInfo(&g_mouseInfo, &g_keyInfo);
		GameScene(g_gameScene);
		
		// �f�o�b�O���[�h(�ϐ��̒��̕�����`��)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0xffff00, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0xFFFF00, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
#endif // DEBUG_TEXT_ON

		// ��ʂ̍X�V
		ScreenFlip();
	}
	// �I��
	return 0;
}

void GameScene(int gameScene) {
	
	switch (gameScene){
	case GAME_TYTLE:	GamePlay();  break;	 // �Q�[���̕`��
	case GAME_SELECT:				 break;
	case GAME_PLAY:	    GamePlay();	 break;
	}
}

	

