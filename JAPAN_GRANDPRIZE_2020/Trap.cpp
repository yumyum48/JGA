#include "DxLib.h" 
#include "Struct.h"
#include "control.h"
struct trapInfo {
	
	int x, y;
	void Init() {
		x = 1300;
		y = 610;
	}
};
trapInfo g_trap;
void TrapDisp() {
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + 10, g_mouseInfo.mouseY + 10, 0xFF0000, TRUE);

}

void TrapMove() {

}

void TrapInit() {
	g_trap.Init();
}