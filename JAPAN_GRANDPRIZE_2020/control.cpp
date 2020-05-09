#include "DxLib.h"
#include "Struct.h"
#include "control.h"

// �}�E�X�ƃL�[�{�[�h�̓��͏�Ԃ��Ǘ�����
void ControlInfo(mouse* mouseInfo, key* keyInfo) {
	GetMousePoint(&mouseInfo->mouseX, &mouseInfo->mouseY);

	mouseInfo->oldMouse = mouseInfo->nowMouse;
	mouseInfo->nowMouse = GetMouseInput();
	mouseInfo->MouseFlg = mouseInfo->nowMouse & ~mouseInfo->oldMouse;

	// ���̓L�[�擾
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
	
	// ���̓L�[�擾
	keyInfo.oldKey = keyInfo.nowKey;
	keyInfo.nowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	keyInfo.keyFlg = keyInfo.nowKey & ~keyInfo.oldKey;

	return keyInfo;
}