#include "DxLib.h" 
#include "Struct.h"
#include "control.h"
#include "Select.h"
#include "Trap.h"


													

/*********************************************

* �g���b�v�̕\��

*/////////////////////////////////////////////
void TrapDisp() {
	
	
	if (GetRand(10) == 1) g_trap.dispFlg = TRUE;										// �����_���Ńg���b�v���o��������t���O���I���ɂ���
	
	if (g_trap.dispFlg == TRUE) {
		DrawFormatString(500, 0, 0xFF00FF, "�g���b�v�o�Ă܂���I");
		DrawBox(g_trap.x, g_trap.y, g_trap.x + 100, g_trap.y + 100, 0xFF0000, TRUE);	// �g���b�v��\��
	}
}


/*********************************************

* �g���b�v�̓���

*/////////////////////////////////////////////
void TrapMove() {
	if (g_trap.dispFlg) {
		g_trap.x -= g_speedLevel;														// �g���b�v��X���W���X�N���[�����x�Ɠ����l�ŉ��Z������

		if (g_trap.x + 100 < 0) {
			g_trap.Init();																// �g���b�v����ʊO�ɓ������ꍇ������
			g_trap.dispFlg = FALSE;
		}
	}
}	

/*********************************************

* �g���b�v�̏�����

*/////////////////////////////////////////////
void TrapInit() {
	g_trap.Init();
}