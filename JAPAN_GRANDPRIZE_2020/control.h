#pragma once
#include "DxLib.h"
#include "Struct.h"
extern mouse g_mouseInfo;	// マウスの状態管理
extern key g_keyInfo;		// キーボードの状態管理
mouse MousePoint(mouse mouseInfo);					// マウスの入力状態管理
key KeyType(key keyInfo);							// キーボードの入力状態管理
void ControlInfo(mouse* mouseInfo, key* keyInfo);	// キーボードとマウスの入力状態を管理