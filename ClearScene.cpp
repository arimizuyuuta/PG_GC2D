#include "ClearScene.h"
#include "IScene.h"
#include <Novice.h>

void ClearScene::Initialize() {}

void ClearScene::Update(char* keys, char* preKeys) {
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = TITLE;
	}
}

void ClearScene::Draw() {
	Novice::ScreenPrintf(0, 0, "Current Scene : Clear");
	Novice::ScreenPrintf(0, 30, "Push Space : Next Scene");
}
