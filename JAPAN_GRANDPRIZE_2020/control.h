#pragma once
#include "DxLib.h"
#include "Struct.h"
extern mouse g_mouseInfo;	// �}�E�X�̏�ԊǗ�
extern key g_keyInfo;		// �L�[�{�[�h�̏�ԊǗ�
mouse MousePoint(mouse mouseInfo);					// �}�E�X�̓��͏�ԊǗ�
key KeyType(key keyInfo);							// �L�[�{�[�h�̓��͏�ԊǗ�
void ControlInfo(mouse* mouseInfo, key* keyInfo);	// �L�[�{�[�h�ƃ}�E�X�̓��͏�Ԃ��Ǘ�