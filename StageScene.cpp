#include "StageScene.h"
#include "IScene.h"
#include <Novice.h>

void StageScene::Initialize() {}

void StageScene::Update(char* keys, char* preKeys) {
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = CLEAR;
	}
}

void StageScene::Draw() {
	Novice::ScreenPrintf(0, 0, "Current Scene : Stage");
	Novice::ScreenPrintf(0, 30, "Push Space : Next Scene");
}
