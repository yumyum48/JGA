/******************************************************************************************
**		作品制作
*******************************************************************************************/
#include "DxLib.h"

/**********************************************************************
**　定数の宣言
***********************************************************************/

/******************************************************************************************
**	列挙体の宣言
*******************************************************************************************/
enum {

};

/******************************************************************************************
**	変数の宣言
*******************************************************************************************/
int g_OldKey;			//前回の入力キー
int g_NowKey;			//今回の入力キー
int g_KeyFlg;			//入力キー情報

int g_GameState;

/******************************************************************************************
**	関数のプロトタイプ宣言
*******************************************************************************************/
void Main(void);			//メイン処理
void SceneManage(int scene); //シーン処理

/******************************************************************************************
**	プログラムの開始
*******************************************************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);					//ウィンドウモードで起動

	//SetWindowSize(840, 680);

	if (DxLib_Init() == -1) return -1;		//DXライブラリの初期化処理


	Main();

	return 0;				//ソフトの終了
}

/***********************************************
 * メインプログラム
 ***********************************************/
void Main(void) {
	SetDrawScreen(DX_SCREEN_BACK);			//画面を裏にする

	//ゲームループ
	while (ProcessMessage() == 0 && g_GameState != END && CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

		ClearDrawScreen();		//画面の初期化

		SceneManage(g_GameState);


		ScreenFlip();		//裏画面の内容を表画面に反映
	}

	DxLib_End();			//DXライブラリ使用の終了処理

}

/***********************************************
 * ゲームループ
 ***********************************************/
void SceneManage(int scene) {
	switch (scene) {

	}
}
