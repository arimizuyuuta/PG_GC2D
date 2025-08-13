#include "TitleScene.h"
#include "IScene.h"
#include <Novice.h>

void TitleScene::Initialize() {
	// プロジェクトの実行フォルダに TITLE.png を配置（または "Resources/TITLE.png" 等に）
	titleTex_ = Novice::LoadTexture("TITLE.png");
}

void TitleScene::Update(char* keys, char* preKeys) {
	// スペースでステージへ（既存仕様）
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw() {
	// 背景画像（1280x720想定）
	if (titleTex_ != -1) {
		Novice::DrawSprite(0, 0, titleTex_, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	}
	// 操作ガイド
	Novice::ScreenPrintf(32, 680, "Press SPACE to Start");
}
