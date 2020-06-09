#pragma once
#include "Struct.h"

extern trapInfo g_trap;	// トラップの情報

void TrapDisp();		// トラップ表示
void TrapMove();		// トラップの動き
void TrapInit();		// トラップの初期化