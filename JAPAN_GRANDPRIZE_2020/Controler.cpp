

#include "DxLib.h"
#include "Controler.h"
#include "Struct.h"


int ControlerCheck(void) {

	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &g_controler);

	//�v���C���[�P�̃{�^������
	if (g_controler.Buttons[0] == 128)	g_button.squareButton = true;
	else							g_button.squareButton = false;

	if (g_controler.Buttons[1] == 128)	g_button.crossButton = true;
	else							g_button.crossButton = false;


	if (g_controler.Buttons[2] == 128)	g_button.circleButton = true;
	else							g_button.circleButton = false;


	if (g_controler.Buttons[3] == 128)	g_button.triangleButton = true;
	else							g_button.triangleButton = false;

	//�v���C���[�P�̃X�e�B�b�N����
	if (g_controler.Y < 0
		&& g_controler.X >= -200
		&& g_controler.X <= 200) {
		g_button.moveStick = 1;		//�����
	}
	else if (g_controler.X > 0
		&& g_controler.Y >= -200
		&& g_controler.Y <= 200) {
		g_button.moveStick = 3;		//�E
	}
	else if (g_controler.Y > 0
		&& g_controler.X >= -200
		&& g_controler.X <= 200) {
		g_button.moveStick = 5;		//��
	}
	else if (g_controler.X < 0
		&& g_controler.Y >= -200
		&& g_controler.Y <= 200) {
		g_button.moveStick = 7;		//��
	}
	else if (g_controler.Y < 0
		&& g_controler.X > 0) {
		g_button.moveStick = 2;		//�E��
	}
	else if (g_controler.Y > 0
		&& g_controler.X > 0) {
		g_button.moveStick = 4;		//�E��
	}
	else if (g_controler.X < 0
		&& g_controler.Y > 0) {
		g_button.moveStick = 6;		//����
	}
	else if (g_controler.X < 0
		&& g_controler.Y < 0) {
		g_button.moveStick = 8;		//����
	}
	else {
		g_button.moveStick = 0;		//
	}

	return 0;
}