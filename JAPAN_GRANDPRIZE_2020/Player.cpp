#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Player.h"

image g_pic;

void PlayerDisp() {
	DrawGraph(63, 505, g_pic.Kirby, TRUE);
}
void PlayerMove() {

}
/*
void PlayerMove(playerInfo* p) {
	float moveX = 0.0F;
	float moveY = 0.0F;

	if (p->jumpFlg == FALSE && //ジャンプボタン ) {
		p->jumpFlg = TRUE;
	}
	
}*/