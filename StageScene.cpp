#include "StageScene.h"
#include "Bullet.h"
#include "Enemy.h"
#include "IScene.h"
#include "Player.h"
#include <Novice.h>
#include <algorithm>

void StageScene::Initialize() {
	player_ = std::make_unique<Player>();
	enemy_ = std::make_unique<Enemy>();
	bullets_.clear();

	player_->Initialize();
	enemy_->Initialize();
}

void StageScene::Update(char* keys, char* preKeys) {
	// プレイヤー更新（弾発射は内部で bullets_ に積む）
	player_->Update(keys, preKeys, bullets_);

	// 弾更新
	for (auto& b : bullets_)
		b.Update();

	// 敵更新
	if (enemy_)
		enemy_->Update();

	// 弾 × 敵 当たり判定
	if (enemy_) {
		for (auto& b : bullets_) {
			if (!b.IsAlive())
				continue;
			if (AABB(b.Left(), b.Top(), b.Right(), b.Bottom(), enemy_->Left(), enemy_->Top(), enemy_->Right(), enemy_->Bottom())) {
				b.Kill();
				enemy_->Hit(1);
			}
		}
		if (enemy_->IsDead()) {
			// 敵を倒したので CLEAR シーンへ（State 切替）
			sceneNo = CLEAR;
		}
	}

	// 死んだ弾の掃除
	bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(), [](const Bullet& b) { return !b.IsAlive(); }), bullets_.end());

	// ※（任意）ESCでタイトルに戻る等のショートカットが欲しければここで sceneNo=TITLE;
}

void StageScene::Draw() {
	Novice::ScreenPrintf(10, 10, "Current Scene : Stage");
	Novice::ScreenPrintf(10, 30, "ARROW: Move   SPACE: Shoot   Kill the enemy -> CLEAR");

	// 描画
	if (enemy_)
		enemy_->Draw();
	if (player_)
		player_->Draw();
	for (auto& b : bullets_)
		b.Draw();

	// 当たり判定可視化（必要なら）
	// Novice::DrawBox((int)enemy_->Left(), (int)enemy_->Top(),
	//                 (int)(enemy_->Right()-enemy_->Left()), (int)(enemy_->Bottom()-enemy_->Top()),
	//                 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
}
