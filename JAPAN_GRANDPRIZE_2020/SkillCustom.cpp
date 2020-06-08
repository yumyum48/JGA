#include "DxLib.h"
#include "SkillCustom.h"
#include "GameScene.h"
#include "control.h"
#include "Struct.h"
#include "Player.h"
#include "Sounds.h"
#include "Picture.h"
#include "Select.h"

static int g_Skill_Num = 1;	//選択しているスキル番号
int g_set = 0;			//セットした番号
int debug = 1;
int con_1, con_2;		//配列コントロール変数

bool costomEndFlg = FALSE;	//画面移動時の確認フラグ
bool skill_ReleaseFlg[7] = { FALSE }; //スキル解放フラグ
int past_Skill[3] = { 0 };	//前のスキル情報を保存


void SkillCustom() {
	SkillCustom_Move();
	SkillCustom_Disp();

}

// スキルカスタマイズの表示
void SkillCustom_Disp() {

	DrawRotaGraph2(0, 0, 0, 0, 8.0, 0.0, g_pic.customBackimage, TRUE);		// 背景表示
	//デバッグ用
	DrawFormatString(0, 60, 0xFFFFFF, "%d", g_player.skillcustom[0]);
	DrawFormatString(10, 60, 0xFFFFFF, "%d", g_player.skillcustom[1]);
	DrawFormatString(20, 60, 0xFFFFFF, "%d", g_player.skillcustom[2]);
	DrawFormatString(0, 80, 0xFFFFFF, "%d", g_Skill_Num);
	DrawFormatString(10, 80, 0xFFFFFF, "%d", debug);



	DrawFormatString(0, 100, 0xFF0000, "%d", skill_ReleaseFlg[g_Skill_Num - 1]);

	//お知らせ用
	//DrawString(800, 800, "↑ボタンでスキル決定", 0xFFFFFF);
	//DrawString(800, 900, "↓ボタンでスキル解除", 0xFFFFFF);

	//仮
	SetFontSize(40);
	DrawString(1000, 650, "決定", 0x00FF00);
	if (costomEndFlg == TRUE) DrawBox(1000, 650, 1100, 700, 0x00FF00, FALSE);

	SkillChoice_Dis();

	DrawExtendGraph(35, 650, 320, 735, g_pic.skilChoiceBox, FALSE);

	DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[0]], TRUE, FALSE);
	DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[1]], TRUE, FALSE);
	DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[2]], TRUE, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	SetDrawBright(255, 0, 0);
	if (g_set < 1) DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[0]], TRUE, FALSE);
	if (g_set < 2) DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[1]], TRUE, FALSE);
	if (g_set < 3) DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[g_player.skillcustom[2]], TRUE, FALSE);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	//スキル格納の場所
	{
		if (g_player.skillcustom[0] != 0) {
			switch (g_player.skillcustom[0]) {
			case 1: DrawRotaGraph(83, 695, 1, 0,  g_pic.skillAicon[1], TRUE, FALSE);break;   //DrawCircle(85, 695, 30, 0xFF0000, TRUE); break;
			case 2: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE); break;
			case 3: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE); break;
			case 4: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE); break;
			case 5: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE); break;
			case 6: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE); break;
			case 7: DrawRotaGraph(83, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE); break;
			default: break;
			}
		}
		if (g_player.skillcustom[1] != 0) {
			switch (g_player.skillcustom[1]) {
			case 1: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[1], TRUE, FALSE); break;
			case 2: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE);  break;
			case 3: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE);  break;
			case 4: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE);  break;
			case 5: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE);  break;
			case 6: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE);  break;
			case 7: DrawRotaGraph(178, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE);  break;
			default: break;
			}
		}
		if (g_player.skillcustom[2] != 0) {
			switch (g_player.skillcustom[2]) {
			case 1: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[1], TRUE, FALSE); break;
			case 2: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[2], TRUE, FALSE); break;
			case 3: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[3], TRUE, FALSE); break;
			case 4: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[4], TRUE, FALSE); break;
			case 5: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[5], TRUE, FALSE); break;
			case 6: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[6], TRUE, FALSE); break;
			case 7: DrawRotaGraph(273, 695, 1, 0, g_pic.skillAicon[7], TRUE, FALSE); break;
			default: break;
			}
		}
	}*/
}


// スキルカスタマイズの動き
void SkillCustom_Move() {
	static int comparation;				//仮格納
	static bool Storage = TRUE;

	//スキル解放情報更新
	for (int i = 0; i < g_select_MAX + 1; i++) skill_ReleaseFlg[i] = TRUE;

	/*if (Storage == TRUE) {
		for (int st_num = 0; st_num < 3; st_num++) g_player.skillcustom[g_set++] = 0, Storage = FALSE;
		g_set = 0;
	}*/
	if (Storage == TRUE) {
		//前のスキル情報を保存
		for (int i = 0; i < 3; i++) past_Skill[i] = g_player.skillcustom[i];

		if (g_player.skillcustom[g_set] != 0) {
			g_set++;
			if (g_set >= 3) {
				g_set = 0;
				Storage = FALSE;
				costomEndFlg = FALSE;
			}
		}
		else Storage = FALSE;
	}

	//スキル選択
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) if (++g_Skill_Num > 7) g_Skill_Num = 1;
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) 	if (--g_Skill_Num < 1) g_Skill_Num = 7;

	//スキル決定（仮）
	//if ((g_keyInfo.keyFlg & PAD_INPUT_UP) && g_set < 3) {
	if ((g_keyInfo.keyFlg & PAD_INPUT_A) && g_set < 3 && costomEndFlg == FALSE) {

		comparation = g_Skill_Num;


		/*if ((comparation != g_player.skillcustom[0])
			&& (comparation != g_player.skillcustom[1])
			&& (comparation != g_player.skillcustom[2])) {
			g_player.skillcustom[g_set++] = comparation;
		}*/
		if (skill_ReleaseFlg[comparation - 1] == TRUE) {
			if (g_set == 0) g_player.skillcustom[g_set++] = comparation;
			if (g_set == 1) {
				if (comparation != g_player.skillcustom[0])
					g_player.skillcustom[g_set++] = comparation;
			}
			if (g_set == 2) {
				if ((comparation != g_player.skillcustom[0])
					&& (comparation != g_player.skillcustom[1]))
					g_player.skillcustom[g_set++] = comparation;
			}
		}
	}

	//スキル解除(仮)
	//if ((g_keyInfo.keyFlg & PAD_INPUT_DOWN) && g_set > 0) g_player.skillcustom[--g_set] = 0;
	if ((g_keyInfo.keyFlg & PAD_INPUT_2) && g_set > 0) g_player.skillcustom[--g_set] = 0;
	else if ((g_keyInfo.keyFlg & PAD_INPUT_2) && g_set == 0) {//B連打でセレクト画面に戻る
		for (int i = 0; i < 3; i++) g_player.skillcustom[i] = past_Skill[i];
		//スキル解放情報更新
		for (int i = 0; i < 8; i++) skill_ReleaseFlg[i] = FALSE;
		g_gameScene = GAME_SELECT;
		Storage = TRUE;
		costomEndFlg = FALSE;
	}

	//セレクト画面に戻る
	//if (g_keyInfo.keyFlg & PAD_INPUT_A) g_gameScene = GAME_SELECT,Storage = TRUE;

	//セレクト画面に戻る
	if (costomEndFlg == TRUE && (g_keyInfo.keyFlg & PAD_INPUT_A)) {
		if (g_player.skillcustom[0] == 0) g_player.skillcustom[0] = 1; //何も装備しなかった場合スキル１を入れる
		if (g_set == 1) g_player.skillcustom[1] = 0, g_player.skillcustom[2] = 0;
		if (g_set == 2)g_player.skillcustom[2] = 0;
		//スキル解放情報更新
		for (int i = 0; i < 7; i++) skill_ReleaseFlg[i] = FALSE;
		g_gameScene = GAME_SELECT;
		Storage = TRUE;
		costomEndFlg = FALSE;
	}
	//決定キャンセル
	if ((g_keyInfo.keyFlg & PAD_INPUT_2) && costomEndFlg == TRUE) costomEndFlg = FALSE;
	//決定確認
	if (g_set == 3 || g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		costomEndFlg = TRUE;
	}
}

void SkillChoice_Dis()
{
	static float animering = 0;

	for (g_choice.choice_num = 1; g_choice.choice_num < 8; g_choice.choice_num++) {
		DrawExtendGraph(g_choice.x[g_choice.choice_num],
			g_choice.y[g_choice.choice_num],
			g_choice.w[g_choice.choice_num],
			g_choice.h[g_choice.choice_num],
			g_pic.skillAicon[g_choice.choice_num], TRUE);
		if (skill_ReleaseFlg[g_choice.choice_num - 1] == FALSE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			SetDrawBright(0, 0, 0);
			DrawExtendGraph(g_choice.x[g_choice.choice_num],
				g_choice.y[g_choice.choice_num],
				g_choice.w[g_choice.choice_num],
				g_choice.h[g_choice.choice_num],
				g_pic.skillAicon[g_choice.choice_num], TRUE);
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	animering += 0.1F;
	DrawRotaGraph(633, 500, 2.6, animering, g_pic.skillRing[1], TRUE, FALSE);

	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) SkillAni_Plus();
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) SkillAni_Min();

}

void SkillAni_Plus() {
	int box = 7;

	g_choice.x_esc = g_choice.x[7];
	g_choice.y_esc = g_choice.y[7];
	g_choice.w_esc = g_choice.w[7];
	g_choice.h_esc = g_choice.h[7];

	for (int i = 8; i > 1; i--) {
		if (box + (i - 9) > 0) {
			g_choice.x_null = g_choice.x[box];
			g_choice.y_null = g_choice.y[box];
			g_choice.w_null = g_choice.w[box];
			g_choice.h_null = g_choice.h[box];

			g_choice.x[box + (i - 8)] = g_choice.x[box + (i - 9)];
			g_choice.y[box + (i - 8)] = g_choice.y[box + (i - 9)];
			g_choice.w[box + (i - 8)] = g_choice.w[box + (i - 9)];
			g_choice.h[box + (i - 8)] = g_choice.h[box + (i - 9)];

			g_choice.x[box + (i - 9)] = g_choice.x_null;
			g_choice.y[box + (i - 9)] = g_choice.y_null;
			g_choice.w[box + (i - 9)] = g_choice.w_null;
			g_choice.h[box + (i - 9)] = g_choice.h_null;
		}
		else {
			g_choice.x[1] = g_choice.x_esc;
			g_choice.y[1] = g_choice.y_esc;
			g_choice.w[1] = g_choice.w_esc;
			g_choice.h[1] = g_choice.h_esc;

			box = 7;
		}
	}
}

void SkillAni_Min() {
	int box = 1;//g_choice.mana_num;

	g_choice.x_esc = g_choice.x[1];
	g_choice.y_esc = g_choice.y[1];
	g_choice.w_esc = g_choice.w[1];
	g_choice.h_esc = g_choice.h[1];

	for (int i = 1; i < 8; i++) {
		if ((box + i) < 8) {
			g_choice.x_null = g_choice.x[box];
			g_choice.y_null = g_choice.y[box];
			g_choice.w_null = g_choice.w[box];
			g_choice.h_null = g_choice.h[box];

			g_choice.x[box + (i - 1)] = g_choice.x[box + i];
			g_choice.y[box + (i - 1)] = g_choice.y[box + i];
			g_choice.w[box + (i - 1)] = g_choice.w[box + i];
			g_choice.h[box + (i - 1)] = g_choice.h[box + i];

			g_choice.x[box + i] = g_choice.x_null;
			g_choice.y[box + i] = g_choice.y_null;
			g_choice.w[box + i] = g_choice.w_null;
			g_choice.h[box + i] = g_choice.h_null;
		}
		else {
			g_choice.x[7] = g_choice.x_esc;
			g_choice.y[7] = g_choice.y_esc;
			g_choice.w[7] = g_choice.w_esc;
			g_choice.h[7] = g_choice.h_esc;

			box = 1;
		}
	}
}
