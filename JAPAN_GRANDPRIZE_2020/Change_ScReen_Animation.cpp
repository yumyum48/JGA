#include"DxLib.h"
#include "Macro.h"
#include "Change_ScReen_Animation.h"
void ChangeScreen_Animation() {
	scene_animaInput anima = Get_NowDisp(0, 0);
	DrawGraph(0, 0, anima.nowDisp, TRUE);
}

scene_animaInput Get_NowDisp(int nextScene, int animeType) {	// シーンを変える時のアニメーションの情報を格納して返り値として返す関数 引数 (int 次のシーン, int 使用するアニメーションの番号)
	
	static scene_animaInput animation_Info;	// アニメーションに必要な情報を格納する変数

	if(animeType != 0) {
		SaveDrawScreenToPNG(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "image/SceneChange_InputImage/imageBuf.png");	// アニメーション用の画像を一旦フォルダへ保存
		animation_Info.nowDisp = LoadGraph("image/SceneChange_InputImage/imageBuf.png");//アニメーション画像をロード
		animation_Info.nextScene = nextScene;
		animation_Info.animeType = animeType;
	
	}

	return animation_Info;

}
