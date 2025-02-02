#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// タイトル画像
	if ((g_pic.title[0] = LoadGraph("image/titleimage5a.png")) == -1) return -1;

	// タイトルのテキスト画像
	if ((g_pic.titleText[0] = LoadGraph("image/Title_Text2.png")) == -1) return -1;		// タイトルロゴ
	if ((g_pic.titleText[1] = LoadGraph("image/NewGame1.png")) == -1) return -1;			// タイトルロゴ
	if ((g_pic.titleText[2] = LoadGraph("image/Continue1.png")) == -1) return -1;		// タイトルロゴ
	if ((g_pic.titleText[3] = LoadGraph("image/fin1.png")) == -1) return -1;		// タイトルロゴ
	
	// ボタンUIの画像
	if (LoadDivGraph("image/Button_UI2.png", 3, 3, 1, 100, 100, g_pic.button, 0) == -1) return -1;

	// プレイヤー画像の読み込み
	if (LoadDivGraph("image/player3.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	//スキルモーション画像
	if (LoadDivGraph("image/Skill_player.png", 15, 3, 5, 280, 200, g_pic.SkillMotion, 0) == -1) return -1;
	//UI画像
	if ((g_pic.PlayerUI = LoadGraph("image/Aicon2.png")) == -1) return -1;
	//Life画像
	if (LoadDivGraph("image/Life.png", 2, 2, 1, 100, 100, g_pic.Life, 0) == -1) return -1;

	//ゲージ画像
	if ((g_pic.gauge = LoadGraph("image/AiconGauge.png")) == -1) return -1;

	//スキル2モーション(仮)
	//if (LoadDivGraph("image/skill2.png", 4, 4, 1, 200, 200, g_pic.skill2, 0) == -1) return -1;
	//スキル3モーション(仮)
	//if (LoadDivGraph("image/skill3.png", 5, 5, 1, 1443/5, 289, g_pic.skill3, 0) == -1) return -1;
	//スキルエフェクト
	if (LoadDivGraph("image/Skill_effect.png", 35, 5, 7, 400, 400, g_pic.skillEffect, 0) == -1) return -1;
	//スキル5エフェクト
	if (LoadDivGraph("image/Skill_5_Electric_ALL.png", 4, 4, 1, 280, 200, g_pic.skill5Effect, 0) == -1) return -1;
	//スキル7の複製プレイヤー
	if (LoadDivGraph("image/Skill_7_Effect.png", 56, 8, 7, 280, 200, g_pic.skill7_Effect, 0) == -1) return -1;
	//finishMotion
	if (LoadDivGraph("image/Enemy_Finish_player3.png", 16, 4, 4, 280, 200, g_pic.finishMotion, 0) == -1) return -1;

	//ふすま
	if (LoadDivGraph("image/ふすま.png", 2, 2, 1, 80, 96, g_pic.husuma, 0) == -1) return -1;

	//スキルアイコン
	if (LoadDivGraph("image/SkillAicon.png", 8, 8, 1, 100, 100, g_pic.skillAicon, 0) == -1) return -1;
	//スキルアイコン装飾(仮)
	if ((g_pic.skillRing[0] = LoadGraph("image/ring.png")) == -1) return -1;
	if ((g_pic.skillRing[1] = LoadGraph("image/magatama.png")) == -1) return -1;

	//スキル選択画面のセットボックス
	if ((g_pic.skilChoiceBox = LoadGraph("image/SkillChoiceBox.png")) == -1) return -1;
	//スキル選択画面の背景
	if ((g_pic.customBackimage = LoadGraph("image/skillcustom_back.png")) == -1) return -1;

	//bossアイコン
	if (LoadDivGraph("image/IconAll.png", 7, 7, 1, 64, 64, g_pic.bossIcon, 0) == -1) return -1;

	// 歩く雑魚敵画像の読み込み
	if (LoadDivGraph("image/EnemyZako1.png", 4, 4, 1, 100, 100, g_pic.enemy_walk, 0) == -1)return -1;

	// 飛ぶ雑魚敵
	if (LoadDivGraph("image/zkfry.png", 4, 4, 1, 574, 545, g_pic.enemy_fly, 0) == -1)return -1;

	// ミニクラゲ雑魚敵
	if (LoadDivGraph("image/MiniJelly.png", 4, 4, 1, 64, 64, g_pic.enemy_kurage, 0) == -1)return -1;

	/*//マップの読み込み
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// マップ読み込み
	if (LoadDivGraph("image/Stage_main_ALL.png", 28, 4, 7, 250, 400, g_pic.map, 0) == -1)
		return -1;
	//// マップ背景読み込み
	//if ((g_pic.backMap = LoadGraph("image/Stage1_Back2.png")) == -1) return -1;
	
		// マップ背景読み込み
	if (LoadDivGraph("image/Stage_back_ALL.png", 28, 4, 7, 250, 400, g_pic.backMap, 0) == -1)
		return -1;
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// 雨の画像の読み込み
	if ((g_pic.rain = LoadGraph("image/RainLarge.png")) == -1) return -1;

	if ((g_pic.trap = LoadGraph("image/toge.png")) == -1) return -1;
	// レティクル画像の読み込み
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;

	// ボス_１の画像読み込み
	if (LoadDivGraph("image/Boss_1.png", 16, 8, 2, 280, 200, g_pic.boss_1_1, 0) == -1)return -1;

	// ボス_２の画像読み込み
	if (LoadDivGraph("image/ZakoOPAll.png", 9, 9, 1, 256, 256, g_pic.boss_2_1, 0) == -1)return -1;

	// ボス_３の画像読み込み
	if (LoadDivGraph("image/BossFlog.png", 5, 5, 1, 128, 128, g_pic.boss_3_1, 0) == -1)return -1;

	// ボス_４の画像読み込み
	if (LoadDivGraph("image/SpiderBossAll.png", 6, 6, 1, 550, 500, g_pic.boss_4_1, 0) == -1)return -1;

	// ボス_４の雲から漏れ出ている雷の画像読み込み
	if (LoadDivGraph("image/Boss_5_Electric_ALL.png", 4, 4, 1, 280, 200, g_pic.boss4_Cloud_Rightning, 0) == -1)return -1;

	// ボス_４の雷の画像読み込み
	if ((g_pic.boss4_RightningSmash = LoadGraph("image/Boss_4_Electric.png")) == -1) return -1;

	// ボス_５の画像読み込み
	if (LoadDivGraph("image/JellyFishBossAll.png", 10, 10, 1, 550, 600, g_pic.boss_5_1, 0) == -1)return -1;

	// ボス_５のシールド画像読み込み
	if (LoadDivGraph("image/JellyShieldAll.png", 3, 3, 1, 300, 500, g_pic.boss5_sield, 0) == -1)return -1;

	// ボス_６の画像読み込み
	if (LoadDivGraph("image/playerReverse.png", 16, 8, 2, 280, 200, g_pic.boss_6_1, 0) == -1)return -1;
	// ボス_６の　影の攻撃モーション　画像読み込み
	if (LoadDivGraph("image/skill_playerReverse.png", 6, 3, 2, 280, 200, g_pic.boss_6_2, 0) == -1)return -1;
	// ボス_６の　影の攻撃のエフェクト　画像読み込み
	if (LoadDivGraph("image/Skill_effectReverce.png", 10, 5, 2, 400, 400, g_pic.boss_6_3, 0) == -1)return -1;

	// ボス_ヤマタノの前の7体の蛇の画像読み込み
	if (LoadDivGraph("image/YamasannAll.png", 12, 4, 3, 300, 500, g_pic.boss_Yamatano, 0) == -1)return -1;
		
	// ボス_ヤマタノ画像読み込み
	if (LoadDivGraph("image/LastYamasann.png", 12, 4, 3, 537, 660, g_pic.boss_Last, 0) == -1)return -1;

	//// ボス_１の泡画像読み込み
	//if (LoadDivGraph("image/Boss1_Water.png", 8, 8, 0, 280, 200, g_pic.boss_1_2, 0) == -1)
	//	return -1;
	// セレクト画面の背景読み込み
	//if ((g_pic.selectBack = LoadGraph("image/Select.png")) == -1) return -1;
	if ((g_pic.selectBack = LoadGraph("image/セレクト画面.png")) == -1) return -1;
	//セレクト画面のUI画像読み込み
	if (LoadDivGraph("image/SelectUIChar.png", 4, 1, 4, 200, 100, g_pic.selectUI, 0) == -1)return -1;
	if ((g_pic.selectUI[4] = LoadGraph("image/SelectUI.png")) == -1) return -1;

	// 水弾の画像の読み込み
	if (LoadDivGraph("image/watb1.png", 5, 5, 1, 32, 32, g_pic.waterBullet, 0) == -1)return -1;

	// 敵撃破時の水しぶき
	if (LoadDivGraph("image/bassha.png", 5, 5, 1, 100, 100, g_pic.enemySplashes, 0) == -1)return -1;
	// 敵撃破時の蒸気
	if (LoadDivGraph("image/moku1.png", 5, 5, 1, 100, 100, g_pic.enemyVapour, 0) == -1)return -1;

	// ステージクリア時の[討伐完了]の文字
	if ((g_pic.stageClearText = LoadGraph("image/stageClear.png")) == -1) return -1;

	// ゲームオーバー時の[討伐失敗]の文字
	if ((g_pic.gameOverText = LoadGraph("image/gameOver.png")) == -1) return -1;

	// ボス３の舌の画像
	if ((g_pic.bossTongue = LoadGraph("image/tongue.png")) == -1) return -1;

	// 子蜘蛛の画像
	if (LoadDivGraph("image/SpederKids.png", 4, 4, 1, 64, 64, g_pic.spiderKids, 0) == -1)return -1;

	// 雷雲の画像
	if ((g_pic.thundercloud = LoadGraph("image/Cloud.png")) == -1) return -1;
	// くもの糸の画像
	if ((g_pic.spiderThread = LoadGraph("image/String.png")) == -1) return -1;

	// 剣技を獲得しましたテキストの画像
	if ((g_pic.kengiText = LoadGraph("image/Skill_Get_UI.png")) == -1) return -1;


	return 0;
}