#include "GameManager.h"
#include <Novice.h>

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// Noviceの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// ゲームマネージャー生成（1回だけ）
	GameManager* gameManager = new GameManager();

	// ゲーム実行（Run 内でループ）
	gameManager->Run();

	// 解放
	delete gameManager;

	// Noviceの終了
	Novice::Finalize();
	return 0;
}
