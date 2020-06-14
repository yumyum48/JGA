//// プレイヤーの中心から円がでる
//DrawCircle(g_player.x + 102, g_player.y + 111, 10, TRUE);

#include "DxLib.h"
#include "Struct.h"
#include "StageClear.h"
#include "GameScene.h"
#include "control.h"
#include "Rain.h"
#include "Player.h"
#include "Macro.h"
#include "Map.h"
#include "Struct.h"
#include "Init.h"
#include "Picture.h"
#include "Boss.h"
#include "Select.h"
#include "Sounds.h"

bool g_animationScene = FALSE;	// アニメーションを終了させてテキストを表示させるフラグ	TRUE:テキストの表示ON	FALSE:ボスを撃破するアニメーション

int g_husumaAnime = 0;			//ふすまのアニメーション
bool g_husumaFlg = FALSE;		//ふすまのフラグ

picInfo g_clearText;			// クリアした時の「討伐完了！！」の画像
void StageClear() {
	StageClearDisp();		// ステージクリアの表示
	StageClearMove();		// ステージクリアの動き
}


void StageClearDisp() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationDisp();		//ボス撃破アニメーション
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		MapDisp();				// マップの表示
		//PlayerDisp();			// プレイヤーの表示
		RainDisp();				// 雨の表示
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaGraph2(-(WINDOW_WIDTH / 2) + g_husumaAnime, 0, 0, 0, 8.0, 0.0, g_pic.husuma[0], TRUE);
		DrawRotaGraph2(WINDOW_WIDTH - g_husumaAnime, 0, 0, 0, 8.0, 0.0, g_pic.husuma[1], TRUE);
		if (g_husumaFlg == TRUE) {
			if (g_husumaAnime < WINDOW_WIDTH / 2) g_husumaAnime += 15;
		}
		if (g_husumaAnime >= WINDOW_WIDTH / 2) {
			g_husumaAnime = WINDOW_WIDTH / 2;

			DrawRotaGraph2(g_clearText.x, g_clearText.y, 0, 0, 0.6, 0.0, g_pic.stageClearText, TRUE);
			int textX = 112;	// テキスト画像のX座標
			int textY = 689;	// テキスト画像のY座標
			int textX2 = 374;	// 剣技を獲得しましたのX座標
			int textY2 = 412;	// 剣技を獲得しましたのY座標
			int textX3 = 591;	// スキルアイコンのX座標
			int textY3 = 326;	// スキルアイコンのY座標

			DrawGraph(textX3, textY3, g_pic.skillAicon[g_select_Stage + 2], TRUE);
			DrawGraph(textX2, textY2, g_pic.kengiText, TRUE);
			SetFontSize(28);
			DrawString(textX, textY, "Bボタンを押すとメニュー画面へ戻ります", 0xFF0000); // Aボタンを押すとセレクト画面に戻ります
			
			DrawFormatString(0, 0, 0x00FF00, "%d\n%d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
		}
		//DrawModiGraph
		//DrawBox(clearText.x, clearText.y)
	}
}

void StageClearMove() {

	if (g_animationScene == FALSE) {
		BossDefeatAnimationMove();
	}
	else {
		RainMove();				// 雨の動き

		//if (Player_StageClearMove() == 1) {
			if (ClearTextMove() == 1) {
				SetFontSize(39);

				if (g_keyInfo.keyFlg & PAD_INPUT_B) {

					g_animationScene = FALSE;
					g_husumaFlg = FALSE;
					g_husumaAnime = 0;
					GameInit();
					g_gameScene = GAME_SELECT;
				}
			}
		//}
	}
}

int ClearTextMove() {
	if (g_clearText.y < 51) {
		g_clearText.y += 25;
	}
	else {
		g_clearText.y = 51;
		return 1;
	}

	return 0;
}
int Player_StageClearMove() {
	
	if (g_player.y >= GROUND) {	// 主人公が浮いていたら地面に落とす
		g_player.y += 10;
	}
	else {
		g_player.y = GROUND;
	}

	if (g_player.x < 500) {	// 主人公のX座標を移動させて固定
		g_player.x += 10;
	}
	else {
		g_player.x = 500;
		
		// プレイヤー静止モーション
		return 1;
	}

	if (g_player.attackFlg == TRUE) g_player.attackFlg = FALSE;
	if (g_player.swordFlg == TRUE) g_player.swordFlg = FALSE;
	
	return 0;
}

// ボス撃破時のアニメーション　描画
void BossDefeatAnimationDisp() {
	MapDisp();						// マップの表示


	RainDisp();						// 雨の表示
}

// ボス撃破時のアニメーション　内部処理
void BossDefeatAnimationMove() {
	static int animationDelay = 0;		// 討伐完了のテキスト表示までのアニメーション時間
	static bool animationFlg = FALSE;	// ボス撃破のアニメを起動させるフラグ	TRUE:アニメの開始	FALSE:権を振りきる猶予時間
	static float playerAnimation = 0;	//playerのアニメ
	static int bossBlend = 255;			//bossの透過率
	static bool AnimeFlg[9] = { FALSE };//playerアニメの切り替えフラグ

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bossBlend);
	(*BossDisp[g_select_Stage])();	// ボスの表示
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// プレイヤーが刀を振り切る猶予時間
	if (animationFlg == FALSE) {
		if (animationDelay % 15 == 0) {
			RainMove();		// 雨の動き
		}
		animationDelay++;
		if (animationDelay < 55) PlayerDisp();// プレイヤーの表示
		if (animationDelay > 50 && animationDelay < 60)DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x000000, TRUE);
		if (animationDelay > 55) {
			g_boss[g_select_Stage].Init_Stage(g_select_Stage);
			g_boss[g_select_Stage].x = 500;
			g_player.x = 400 * PLAYER_REDUCTION;
			g_player.y = GROUND - PLAYER_HEIGHT;
			DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.finishMotion[15], TRUE);
		}
		if (animationDelay >= 80)animationFlg = TRUE, animationDelay = 0, AnimeFlg[0] = TRUE;
	}
	// ボスを撃破するアニメーション
	else {
		RainMove();		// 雨の動き
		//animationDelay++;
		DrawRotaGraph2(g_player.x, g_player.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.finishMotion[int(playerAnimation)], TRUE);
		/*
		if (animationDelay <= 10) g_player.y -= 4;
		if (animationDelay > 10 && animationDelay <= 100) {
			g_player.y -= 10;
			playerAnimation = 1;
			if (g_select_Stage == 0 || g_select_Stage == 4)if (g_player.y < g_boss[g_select_Stage].y) animationDelay = 100;
			if (g_select_Stage == 1 || g_select_Stage == 2)if (g_player.y < 300) animationDelay = 100;
		}
		if (animationDelay > 100 && animationDelay <= 150) g_player.x += 2, g_player.y += 2, playerAnimation = 2;
		if (animationDelay > 150 && animationDelay <= 250) {
			if (playerAnimation < 5.0F) playerAnimation += 0.2F;
			else playerAnimation = 3.0F;
			g_player.x += 8;
			if (g_select_Stage != 1 && g_select_Stage != 2) g_player.y += 2;
			if (g_select_Stage == 1 || g_select_Stage == 2) g_player.y++;
			if (g_player.x > 1000) animationDelay = 250;
		}
		if (animationDelay > 250 && animationDelay <= 260) g_player.x++, g_player.y += 2, playerAnimation = 6;
		if (animationDelay > 260 && animationDelay <= 270) g_player.x++, g_player.y += 2, playerAnimation = 7;
		if (animationDelay > 270 && animationDelay <= 350) {
			g_player.x++;
			g_player.y += 2;
			if (playerAnimation < 9.0F) playerAnimation += 0.2F;
			else playerAnimation = 8.0F;
			if (g_player.y < GROUND - PLAYER_HEIGHT) {
				g_player.y = GROUND - PLAYER_HEIGHT;
				animationDelay = 350;
			}
		}
		if (animationDelay > 350 && animationDelay <= 355) playerAnimation = 10;
		if (animationDelay > 355 && animationDelay <= 360) playerAnimation = 11;
		if (animationDelay > 360 && animationDelay <= 500) {
			if (playerAnimation < 15.0F) playerAnimation += 0.2F;
			else bossBlend -= 5, g_boss[g_select_Stage].y--;
		}*/
		if (AnimeFlg[0] == TRUE) {/*飛び上がる１*/
			g_player.y -= 4;
			if (g_player.y < 400) AnimeFlg[0] = FALSE, AnimeFlg[1] = TRUE;
		}
		if (AnimeFlg[1] == TRUE) {/*飛び上がる２*/
			g_player.y -= 10;
			playerAnimation = 1;
			if (g_player.y < g_boss[g_select_Stage].y - 100) AnimeFlg[1] = FALSE, AnimeFlg[2] = TRUE;
		}
		if (AnimeFlg[2] == TRUE) {/*少し下がる*/
			PlaySoundMem(g_sound[VOICE_SPECIAL], DX_PLAYTYPE_BACK, FALSE);			//SE再生
			g_player.x += 2;
			if (g_select_Stage != 2) g_player.y += 5;
			else g_player.y += 10;
			playerAnimation = 2;
			if (g_select_Stage != 2) {//カエル以外
				if (g_player.y > g_boss[g_select_Stage].y + 80) AnimeFlg[2] = FALSE, AnimeFlg[3] = TRUE;
			} else {//カエルの場合
				if (g_player.y > g_boss[g_select_Stage].y + 200) AnimeFlg[2] = FALSE, AnimeFlg[3] = TRUE;
			}
		}
		if (AnimeFlg[3] == TRUE) {/*横に切りつけ*/
			g_player.x += 5;
			if (g_player.y < GROUND - PLAYER_HEIGHT) g_player.y++;
			if (playerAnimation < 5.0F) playerAnimation += 0.2F;
			else playerAnimation = 3.0F;
			if (g_player.x > g_boss[g_select_Stage].x + 300) AnimeFlg[3] = FALSE, AnimeFlg[4] = TRUE;
		}
		if (AnimeFlg[4] == TRUE) {/*切り終わる*/
			g_player.x++;
			if (g_player.y < GROUND - PLAYER_HEIGHT) g_player.y += 4;
			animationDelay++;
			if(animationDelay < 10) playerAnimation = 6;
			else playerAnimation = 7;
			if (animationDelay > 20) animationDelay = 0, AnimeFlg[4] = FALSE, AnimeFlg[5] = TRUE;
		}
		if (AnimeFlg[5] == TRUE) {/*着地まで下がる*/
			g_player.x++;
			g_player.y += 6;
			playerAnimation = 8;
			if(g_player.y > GROUND - PLAYER_HEIGHT) AnimeFlg[5] = FALSE, AnimeFlg[6] = TRUE;
		}
		if (AnimeFlg[6] == TRUE) {/*着地*/
			g_player.y = GROUND - PLAYER_HEIGHT;
			playerAnimation = 11;
			animationDelay++;
			if (animationDelay > 10) AnimeFlg[6] = FALSE, AnimeFlg[7] = TRUE;
		}
		if (AnimeFlg[7] == TRUE) {/*納刀*/
			if (playerAnimation < 15.0F) playerAnimation += 0.2F;
			else bossBlend -= 5, g_boss[g_select_Stage].y--,
				PlaySoundMem(g_sound[SE_ENEMY_DOWN], DX_PLAYTYPE_BACK, TRUE);			//SE再生
			if (bossBlend <= 0) AnimeFlg[7] = FALSE, AnimeFlg[8] = TRUE;
		}
	}
	

	// アニメーション時間の管理
	if (AnimeFlg[8] == TRUE) {			// アニメーション終了時の初期化処理
		animationDelay = 0;
		playerAnimation = 0;
		bossBlend = 255;
		g_animationScene = TRUE;
		g_husumaFlg = TRUE;
		animationFlg = FALSE;
		AnimeFlg[8] = FALSE;
	}
}

void StageClearInit() {
	g_clearText.x = 311;
	g_clearText.y = -237;

}