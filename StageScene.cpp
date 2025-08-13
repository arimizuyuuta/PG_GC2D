#include "StageScene.h"
#include "IScene.h"
#include <Novice.h>
#include <algorithm>
#include <cmath>

void StageScene::Initialize() {

	 stageBGTex_ = Novice::LoadTexture("STAGE.png");

	// プレイヤー
	player_ = {
	    {640.0f, 620.0f},
        6.0f, 16.0f
    };

	// 弾
	bullets_.clear();
	shotCooldown_ = 0;

	// 敵を5体配置（横ゆらぎ移動）
	enemies_.clear();
	for (int i = 0; i < 5; ++i) {
		Enemy e{};
		e.base = {180.0f + i * 180.0f, 120.0f};
		e.pos = e.base;
		e.t = 0.0f;
		e.radius = 16.0f;
		e.alive = true;
		e.deadTimer = 0;
		enemies_.push_back(e);
	}
}

void StageScene::Update(char* keys, char* preKeys) {
	// ===== プレイヤー移動 =====
	float vx = 0, vy = 0;
	if (keys[DIK_LEFT])
		vx -= 1.0f;
	if (keys[DIK_RIGHT])
		vx += 1.0f;
	if (keys[DIK_UP])
		vy -= 1.0f;
	if (keys[DIK_DOWN])
		vy += 1.0f;
	player_.pos.x += vx * player_.speed;
	player_.pos.y += vy * player_.speed;
	// 画面内に拘束
	player_.pos.x = std::clamp(player_.pos.x, player_.radius, 1280.0f - player_.radius);
	player_.pos.y = std::clamp(player_.pos.y, player_.radius, 720.0f - player_.radius);

	// ===== ショット（Zで単発）=====
	if (shotCooldown_ > 0)
		--shotCooldown_;
	bool shotPressed = (preKeys[DIK_Z] == 0 && keys[DIK_Z] != 0);
	if (shotPressed && shotCooldown_ == 0) {
		Bullet b{};
		b.pos = {player_.pos.x, player_.pos.y - player_.radius};
		b.vel = {0.0f, -12.0f};
		b.radius = 6.0f;
		b.alive = true;
		bullets_.push_back(b);
		shotCooldown_ = 6; // 連打防止
	}

	// 弾更新
	for (auto& b : bullets_) {
		if (!b.alive)
			continue;
		b.pos.x += b.vel.x;
		b.pos.y += b.vel.y;
		if (b.pos.y < -20.0f)
			b.alive = false;
	}

	// ===== 敵の挙動 =====
	for (auto& e : enemies_) {
		if (!e.alive) {
			if (e.deadTimer > 0)
				--e.deadTimer; // 爆発表示用
			continue;
		}
		e.t += 0.03f;
		e.pos.x = e.base.x + std::sin(e.t * 1.7f) * 60.0f;
		e.pos.y = e.base.y + std::sin(e.t) * 8.0f;
	}

	// ===== 当たり判定（弾×敵：距離の二乗で判定）=====
	for (auto& e : enemies_) {
		if (!e.alive)
			continue;
		for (auto& b : bullets_) {
			if (!b.alive)
				continue;
			float rr = (e.radius + b.radius);
			if (LengthSq(e.pos, b.pos) <= rr * rr) {
				e.alive = false;
				e.deadTimer = 20; // 20フレームだけ爆発風表示
				b.alive = false;
				break;
			}
		}
	}

	// 死亡した弾を除去
	bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(), [](const Bullet& b) { return !b.alive; }), bullets_.end());

	// ===== クリア判定（全敵撃破）=====
	bool anyAlive = false;
	for (auto& e : enemies_) {
		if (e.alive || e.deadTimer > 0) {
			anyAlive = true;
			break;
		}
	}
	if (!anyAlive) {
		sceneNo = CLEAR; // クリアシーンへ
	}
}

void StageScene::Draw() {
	// 背景
	if (stageBGTex_ != -1) {
		Novice::DrawSprite(0, 0, stageBGTex_, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	}

	// UI
	Novice::ScreenPrintf(16, 16, "Stage: Arrow Move, Z: Shot");
	Novice::ScreenPrintf(16, 40, "Beat all enemies to clear!");

	// プレイヤー
	Novice::DrawEllipse((int)player_.pos.x, (int)player_.pos.y, (int)player_.radius, (int)player_.radius, 0.0f, 0x66CCFFFF, kFillModeSolid);

	// 弾
	for (auto& b : bullets_) {
		if (!b.alive)
			continue;
		Novice::DrawEllipse((int)b.pos.x, (int)b.pos.y, (int)b.radius, (int)b.radius, 0.0f, 0xFFFF88FF, kFillModeSolid);
	}

	// 敵（生存：赤／爆発中：オレンジ）
	for (auto& e : enemies_) {
		if (e.alive) {
			Novice::DrawEllipse((int)e.pos.x, (int)e.pos.y, (int)e.radius, (int)e.radius, 0.0f, 0xFF4444FF, kFillModeSolid);
		} else if (e.deadTimer > 0) {
			int r = (int)(e.radius + (20 - e.deadTimer) * 0.8f);
			Novice::DrawEllipse((int)e.pos.x, (int)e.pos.y, r, r, 0.0f, 0xFFA000FF, kFillModeSolid);
		}
	}
}
