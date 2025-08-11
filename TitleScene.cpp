#include "TitleScene.h"
#include "IScene.h"
#include <Novice.h>

void TitleScene::Initialize() {}

void TitleScene::Update(char* keys, char* preKeys) {
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw() {
	Novice::ScreenPrintf(0, 0, "Current Scene : Title");
	Novice::ScreenPrintf(0, 30, "Push Space : Next Scene");
}
