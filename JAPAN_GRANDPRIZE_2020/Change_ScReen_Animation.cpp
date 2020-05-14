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
	
	MapDisp();
	RainDisp();
	RainMove();
	PlayerDisp();
	scene_animaInput anima = Get_NowDisp(0, 0);
	if (anima.animeType == 1) {
		DrawGraph(g_disp[0].x, g_disp[0].y, anima.nowDisp[0], TRUE);
	}
	else if (anima.animeType == 2) {

		DrawGraph(g_disp[0].x, g_disp[0].y, anima.nowDisp[0], TRUE);
		DrawGraph(g_disp[1].x, g_disp[1].y, anima.nowDisp[1], TRUE);
		Scene_Animation_Shoji(anima.nextScene);

	}



}
void Scene_Animation_Shoji(int nextScene) {
	if (g_disp[0].x + WINDOW_WIDTH > 0) {
		g_disp[0].x -= 10;
	}

	if (g_disp[1].x < WINDOW_WIDTH) {
		g_disp[1].x += 10;
	}
	else {
		ChangeScreen_Animation_Init();
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
		SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// アニメーション用の画像を一旦フォルダへ保存
		LoadDivGraph("image/SceneChange_InputImage/imageBuf.png", 2, 2, 1, WINDOW_WIDTH / 2, WINDOW_HEIGHT, animation_Info.nowDisp, 0);//アニメーション画像をロード
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