#pragma once

extern int g_gameScene;	// ゲームシーン管理

enum {	// ゲームシーン情報
	GAME_TITLE,						// ゲームタイトル
	GAME_SELECT,					//	ゲームセレクト
	GAME_PLAY,						// ゲームプレイ
	GAME_OVER,						// ゲームオーバー
	GAME_CLEAR,						// ゲームクリア
	GAME_STAGE_CLEAR,				// ゲームステージクリア
	GAME_SAVE,						// ゲームデータの保存
	GAME_LOAD,						// セーブデータのロード
	GAME_CHANGE_SCREEN_ANIMATION,	// 画面切り替えの際のアニメーション
};
