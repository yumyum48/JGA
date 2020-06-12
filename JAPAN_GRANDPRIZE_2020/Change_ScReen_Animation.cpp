#include"DxLib.h"
#include "Macro.h"
#include "Change_ScReen_Animation.h"
#include "Struct.h"
#include "GameScene.h"
#include "Map.h"
#include "Player.h"
#include "Rain.h"
animationInfo g_disp[2];
void ChangeScreen_Animation() {
	
	MapDisp();			// マップの表示
	RainDisp();			// 雨の表示
	RainMove();			// 雨の動き
	PlayerDisp();		// プレイヤーの表示
	scene_animaInput anima = Get_NowDisp(0, 0);
	if (anima.animeType == 1) {
		DrawGraph(g_disp[0].x, g_disp[0].y, anima.nowDisp[0], TRUE);
	}
	else if (anima.animeType == 2) {

		DrawRotaGraph2(g_disp[0].x, g_disp[0].y, 0, 0, 2.0, 0.0, anima.nowDisp[0], TRUE);
		DrawRotaGraph2(g_disp[1].x, g_disp[1].y, 0, 0, 2.0, 0.0, anima.nowDisp[1], TRUE);
		Scene_Animation_Shoji(anima.nextScene);

	}



}
void Scene_Animation_Shoji(int nextScene) {
	static bool openFlg = FALSE;
	if (openFlg == FALSE) {		// 閉めるアニメーション
		if (g_disp[1].x < WINDOW_WIDTH) {

		}
	}
	if ((g_disp[0].x + (WINDOW_WIDTH / 2)) + WINDOW_WIDTH > 0) {		// 左の障子
		g_disp[0].x -= 10;
	}

	if (g_disp[1].x< WINDOW_WIDTH) {									// 右の障子
		g_disp[1].x += 10;
	}
	else {
		ChangeScreen_Animation_Init();									// アニメーションが終了していたら初期化
		g_gameScene = nextScene;
	}

}
scene_animaInput Get_NowDisp(int nextScene, int animeType) {	// シーンを変える時のアニメーションの情報を格納して返り値として返す関数 引数 (int 次のシーン, int 使用するアニメーションの番号)
	
	static scene_animaInput animation_Info;	// アニメーションに必要な情報を格納する変数

	if(animeType == 1) {
		SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// アニメーション用の画像を一旦フォルダへ保存
		animation_Info.nowDisp[0] = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//アニメーション画像をロード
		animation_Info.nextScene = nextScene;	// 受け取った次のシーンを格納
		animation_Info.animeType = animeType;	// 受け取ったアニメーションタイプを格納
	
	}
	else if (animeType == 2) {
		//SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// アニメーション用の画像を一旦フォルダへ保存
		LoadDivGraph("image/ふすま.png", 2, 2, 1, 80, 96, animation_Info.nowDisp, 0);//アニメーション画像をロード
		for (int i = 0; i < 2; i++) {
			g_disp[i].ShoujiInit(i);
		}
		animation_Info.nextScene = nextScene;	// 受け取った次のシーンを格納
		animation_Info.animeType = animeType;	// 受け取ったアニメーションタイプを格納
	}

	//switch (animeType) {
	//case 1:
	//	SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// アニメーション用の画像を一旦フォルダへ保存
	//	animation_Info.nowDisp = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//アニメーション画像をロード
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
		g_disp[i].Init(i);
	}
}