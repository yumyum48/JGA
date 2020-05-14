#include "DxLib.h"
#include "Sounds.h"


int LoadSounds(void) {				//サウンド読み込み

	if ((g_sound[BGM_TITLE] = LoadSoundMem("sounds/Soushi2.mp3")) == -1) return -1;	//タイトルBGM
	if ((g_sound[BGM_SELECT] = LoadSoundMem("sounds/n2.mp3")) == -1) return -1;	//セレクトBGM
	if ((g_sound[BGM_BATTLE] = LoadSoundMem("sounds/Gen-ou-You.mp3")) == -1) return -1;	//バトルBGM
	if ((g_sound[BGM_BOSS] = LoadSoundMem("sounds/senou.mp3")) == -1) return -1;	//バトルBGM
	if ((g_sound[BGM_LAST_BOSS] = LoadSoundMem("sounds/n76.mp3")) == -1) return -1;	//ラスボスBGM
	if ((g_sound[BGM_RAIN] = LoadSoundMem("sounds/towm-torrential-rain1.mp3")) == -1) return -1;	//雨BGM
	if ((g_sound[BGM_OVER] = LoadSoundMem("sounds/Torii.mp3")) == -1) return -1;	//ゲーム完全クリアBGM
	if ((g_sound[BGM_GAMECLEAR] = LoadSoundMem("sounds/n103.mp3")) == -1) return -1;	//ゲーム完全クリアBGM

	if ((g_sound[SE_ENEMY_DOWN] = LoadSoundMem("sounds/sei_ge_jouhatu01.mp3")) == -1) return -1;	//敵蒸発SE
	if ((g_sound[SE_DECISION] = LoadSoundMem("sounds/hyoushigi1.mp3")) == -1) return -1;	//選択SE
	if ((g_sound[SE_KETTEI] = LoadSoundMem("sounds/japanese-style-1.mp3")) == -1) return -1;	//決定SE
	if ((g_sound[SE_STEP] = LoadSoundMem("sounds/footstep-rain.mp3")) == -1) return -1;	//走るSE
	if ((g_sound[SE_JUMP] = LoadSoundMem("sounds/pichan.mp3")) == -1) return -1;	//ジャンプSE
	if ((g_sound[SE_TYAKUTI] = LoadSoundMem("sounds/02.mp3")) == -1) return -1;	//着地SE

	if ((g_sound[VOICE_NORMAL] = LoadSoundMem("sounds/sizukani.mp3")) == -1) return -1;	//主人公攻撃ボイス
	if ((g_sound[VOICE_SPECIAL] = LoadSoundMem("sounds/witch-special1.mp3")) == -1) return -1;	//主人公必殺ボイス
	if ((g_sound[VOICE_DAMAGE] = LoadSoundMem("sounds/thief-boy-damage2.mp3")) == -1) return -1;	//主人公ダメージボイス

	if ((g_sound[BOSS1_ATTACK] = LoadSoundMem("sounds/se_maoudamashii_element_water06.mp3")) == -1) return -1;	//ボス１攻撃音
	if ((g_sound[BOSS3_ATTACK1] = LoadSoundMem("sounds/Boss2_1.mp3")) == -1) return -1;	//ボス３舌攻撃音
	if ((g_sound[BOSS3_ATTACK2] = LoadSoundMem("sounds/boss_born.mp3")) == -1) return -1;	//ボス３毒沼攻撃音
	if ((g_sound[BOSS3_ATTACK2] = LoadSoundMem("sounds/boss_born.mp3")) == -1) return -1;	//ボス４部下生成音
	if ((g_sound[BOSS5_SHIELD] = LoadSoundMem("sounds/shield.mp3")) == -1) return -1;	//ボス５シールド音
	if ((g_sound[BOSS5_ATTACK] = LoadSoundMem("sounds/short_bomb.mp3")) == -1) return -1;	//ボス５クラゲミサイル音




}