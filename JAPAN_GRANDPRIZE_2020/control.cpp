#include "DxLib.h"
#include "Struct.h"
#include "control.h"

// マウスとキーボードの入力状態を管理する
void ControlInfo(mouse* mouseInfo, key* keyInfo) {
	GetMousePoint(&mouseInfo->mouseX, &mouseInfo->mouseY);

	mouseInfo->oldMouse = mouseInfo->nowMouse;
	mouseInfo->nowMouse = GetMouseInput();
	mouseInfo->MouseFlg = mouseInfo->nowMouse & ~mouseInfo->oldMouse;

	// 入力キー取得
	keyInfo->oldKey = keyInfo->nowKey;
	keyInfo->nowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	keyInfo->keyFlg = keyInfo->nowKey & ~keyInfo->oldKey;

}
mouse MousePoint(mouse mouseInfo) {
	
	GetMousePoint(&mouseInfo.mouseX, &mouseInfo.mouseY);

	mouseInfo.oldMouse = mouseInfo.nowMouse;
	mouseInfo.nowMouse = GetMouseInput();
	mouseInfo.MouseFlg = mouseInfo.nowMouse & ~mouseInfo.oldMouse;

	return mouseInfo;
}

key KeyType(key keyInfo) {
	
	// 入力キー取得
	keyInfo.oldKey = keyInfo.nowKey;
	keyInfo.nowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	keyInfo.keyFlg = keyInfo.nowKey & ~keyInfo.oldKey;

	return keyInfo;
}