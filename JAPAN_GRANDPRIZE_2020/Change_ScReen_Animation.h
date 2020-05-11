#pragma once

struct scene_animaInput{	// アニメーションに必要な情報

	int nextScene;		// アニメーションを終了した後に切り替えるシーン
	int animeType;		// アニメーションのタイプ	0:未定 1:未定...
	int nowDisp;		// アニメーションを行う画面を保存する
	

};
void ChangeScreen_Animation();								// アニメーションを行う関数
scene_animaInput Get_NowDisp(int nextScene, int animeType);	// シーンを変える時のアニメーションを起動する関数 引数 (int 次のシーン, int 使用するアニメーションの番号 (0番目は使わないで下さい！))