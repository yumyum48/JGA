#pragma once

struct scene_animaInput{	// アニメーションに必要な情報

	int nextScene;		// アニメーションを終了した後に切り替えるシーン
	int animeType;		// アニメーションのタイプ	0:未定 1:未定...
	int nowDisp[2];		// アニメーションを行う画面を保存する
	

};

struct animationInfo {		// アニメーションに必要な動きなどを再現する場合に使う情報
	int x, y;	// X, Y座標

	void Init(int num) {
		switch (num) {
		case 0: 
			x = 0;
			y = 0;
			break;
		case 1:
			x = WINDOW_WIDTH / 2;
			y = 0;
		default:
			break;
		}
		
	}
};
void ChangeScreen_Animation();								// アニメーションを行う関数
void ChangeScreen_Animation_Init();							// アニメーション用の初期化関数
void Scene_Animation_Shoji(int nextScene);					// 障子が開くようなアニメーション
scene_animaInput Get_NowDisp(int nextScene, int animeType);	// シーンを変える時のアニメーションを起動する関数 引数 (int 次のシーン, int 使用するアニメーションの番号 (0番目は使わないで下さい！))