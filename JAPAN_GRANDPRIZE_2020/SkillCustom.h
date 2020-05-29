#pragma once
void SkillCustom();		 // スキルカスタマイズの管理
void SkillCustom_Disp(); // スキルカスタマイズの表示
void SkillCustom_Move(); // スキルカスタマイズの動き

void SkillChoice_Dis();	//スキル選択描写

void SkillAni_Plus();	//スキルアニメーション+
void SkillAni_Min();	//スキルアニメーション-


	//スキル選択見た目
	//DrawCircle(600, 450, 100, 0xFF0000, TRUE);			//スキル１
	//DrawCircle(330, 380, 70, 0x00FF00, TRUE);			//スキル２
	//DrawCircle(240, 230, 40, 0xFFFF00, TRUE);			//スキル３
	//DrawCircle(450, 145, 20, 0xFF00FF, TRUE);			//スキル４
	//DrawCircle(805, 145, 20, 0x00FFFF, TRUE);			//スキル５
	//DrawCircle(1000, 230, 40, 0xFFFFFF, TRUE);			//スキル６
	//DrawCircle(870, 380, 70, 0x0000FF, TRUE);			//スキル７

struct ChoiceInfo {
	int x[8]{0, 500,780,945,775,415,180,265};
	int y[8]{0, 375,285,170,110,110,170,285 };
	int w[8]{0, 765,975,1055,835,475,295,465};
	int h[8]{0, 620,465,275,170,170,275,465};

	//int x[8]{0, 600,330,240,450,805,1000,870};
	//int y[8]{0, 450,380,230,145,145,230,380};
	//double e[8]{0, 1.5,2,1.5,1,0.5,0.5,1 };

	int x_null;
	int y_null;

	int w_null;
	int h_null;

	//double e_null;

	int x_esc;
	int y_esc;
	int w_esc;
	int h_esc;

	//double e_esc;

	int image_null;

	int mana_num = 1;
	int choice_num;
};

extern ChoiceInfo g_choice;

//if(g_Skill_Num == 7 && g_choice.mana_num == 1){
//	g_choice.x_null = g_choice.x[1];
//	g_choice.y_null = g_choice.y[1];
//	g_choice.w_null = g_choice.w[1];
//	g_choice.h_null = g_choice.h[1];

//	g_choice.x[1] = g_choice.x[0];
//	g_choice.y[1] = g_choice.y[0];
//	g_choice.w[1] = g_choice.w[0];
//	g_choice.h[1] = g_choice.h[0];

//	g_choice.x[0] = g_choice.x_null;
//	g_choice.y[0] = g_choice.y_null;
//	g_choice.w[0] = g_choice.w_null;
//	g_choice.h[0] = g_choice.h_null;
//}
//else {
//	if (SkillAni_Cal(g_Skill_Num) == 1) {
//		g_choice.x_null = g_choice.x[6];
//		g_choice.y_null = g_choice.y[6];
//		g_choice.w_null = g_choice.w[6];
//		g_choice.h_null = g_choice.h[6];

//		g_choice.x[6] = g_choice.x[0];
//		g_choice.y[6] = g_choice.y[0];
//		g_choice.w[6] = g_choice.w[0];
//		g_choice.h[6] = g_choice.h[0];

//		g_choice.x[0] = g_choice.x_null;
//		g_choice.y[0] = g_choice.y_null;
//		g_choice.w[0] = g_choice.w_null;
//		g_choice.h[0] = g_choice.h_null;
//	}
//	else {
//		g_choice.x_null = g_choice.x[g_choice.mana_num];
//		g_choice.y_null = g_choice.y[g_choice.mana_num];
//		g_choice.w_null = g_choice.w[g_choice.mana_num];
//		g_choice.h_null = g_choice.h[g_choice.mana_num];

//		box = g_choice.mana_num;

//		for (int c = 1,con_1 = 1 , con_2 = 0; c < 8; c++,con_1++,con_2++) {
//			if ((g_choice.mana_num + con_2 == 7) || (g_choice.mana_num + con_1 == 7)) 
//				SkillAni_CalP();

//			g_choice.x[box + con_2] = g_choice.x[box + con_1];
//			g_choice.y[box + con_2] = g_choice.y[box + con_1];
//			g_choice.w[box + con_2] = g_choice.w[g_choice.mana_num + con_1];
//			g_choice.h[box + con_2] = g_choice.h[box + con_1];

//		}

//		g_choice.x[g_choice.mana_num + con_1] = g_choice.x_null;
//		g_choice.y[g_choice.mana_num + con_1] = g_choice.y_null;
//		g_choice.w[g_choice.mana_num + con_1] = g_choice.w_null;
//		g_choice.h[g_choice.mana_num + con_1] = g_choice.h_null;
//	}
//}



	//if (g_choice.mana_num == 7 && g_Skill_Num == 1) {
	//	g_choice.x_null = g_choice.x[0];
	//	g_choice.y_null = g_choice.y[0];
	//	g_choice.w_null = g_choice.w[0];
	//	g_choice.h_null = g_choice.h[0];

	//	g_choice.x[0] = g_choice.x[1];
	//	g_choice.y[0] = g_choice.y[1];
	//	g_choice.w[0] = g_choice.w[1];
	//	g_choice.h[0] = g_choice.h[1];

	//	g_choice.x[1] = g_choice.x_null;
	//	g_choice.y[1] = g_choice.y_null;
	//	g_choice.w[1] = g_choice.w_null;
	//	g_choice.h[1] = g_choice.h_null;
	//}
	//else {
	//	if (SkillAni_Cal(g_choice.mana_num) == 1) {
	//		g_choice.x_null = g_choice.x[0];
	//		g_choice.y_null = g_choice.y[0];
	//		g_choice.w_null = g_choice.w[0];
	//		g_choice.h_null = g_choice.h[0];

	//		g_choice.x[0] = g_choice.x[6];
	//		g_choice.y[0] = g_choice.y[6];
	//		g_choice.w[0] = g_choice.w[6];
	//		g_choice.h[0] = g_choice.h[6];

	//		g_choice.x[6] = g_choice.x_null;
	//		g_choice.y[6] = g_choice.y_null;
	//		g_choice.w[6] = g_choice.w_null;
	//		g_choice.h[6] = g_choice.h_null;
	//	}
	//	else {
	//		g_choice.x_null = g_choice.x[g_choice.mana_num - 1];
	//		g_choice.y_null = g_choice.y[g_choice.mana_num - 1];
	//		g_choice.w_null = g_choice.w[g_choice.mana_num - 1];
	//		g_choice.h_null = g_choice.h[g_choice.mana_num - 1];

	//		g_choice.x[g_choice.mana_num - 1] = g_choice.x[g_choice.mana_num];
	//		g_choice.y[g_choice.mana_num - 1] = g_choice.y[g_choice.mana_num];
	//		g_choice.w[g_choice.mana_num - 1] = g_choice.w[g_choice.mana_num];
	//		g_choice.h[g_choice.mana_num - 1] = g_choice.h[g_choice.mana_num];

	//		g_choice.x[g_choice.mana_num] = g_choice.x_null;
	//		g_choice.y[g_choice.mana_num] = g_choice.y_null;
	//		g_choice.w[g_choice.mana_num] = g_choice.w_null;
	//		g_choice.h[g_choice.mana_num] = g_choice.h_null;
	//	}
	//}