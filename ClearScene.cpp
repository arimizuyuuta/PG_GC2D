#include "ClearScene.h"
#include "IScene.h"
#include <Novice.h>

void ClearScene::Initialize() { clearTex_ = Novice::LoadTexture("CLEAR.png"); }

void ClearScene::Update(char* keys, char* preKeys) {
	// スペースでタイトルへ（既存仕様）
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = TITLE;
	}
}

void ClearScene::Draw() {
	if (clearTex_ != -1) {
		Novice::DrawSprite(0, 0, clearTex_, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	}
	Novice::ScreenPrintf(32, 680, "Press SPACE to Title");
}
