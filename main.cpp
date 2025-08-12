#include "Player.h"
#include <Novice.h>

Player::Player() { Initialize(); }

void Player::Initialize() {
	pos_ = {100.0f, 360.0f};
	size_ = {32.0f, 32.0f};
	speed_ = 6.0f;
	shootCooldown_ = 0;
}

void Player::Update(char* keys, char* preKeys, std::vector<Bullet>& bullets) {
	// 移動（矢印キー）
	if (keys[DIK_LEFT]) {
		pos_.x -= speed_;
	}
	if (keys[DIK_RIGHT]) {
		pos_.x += speed_;
	}
	if (keys[DIK_UP]) {
		pos_.y -= speed_;
	}
	if (keys[DIK_DOWN]) {
		pos_.y += speed_;
	}

	ClampToScreen();

	if (shootCooldown_ > 0) {
		--shootCooldown_;
	}

	// 発射（スペース：押した瞬間 + 連射間隔）
	bool pressed = (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0);
	if ((pressed || keys[DIK_SPACE]) && shootCooldown_ == 0) {
		Shoot(bullets);
		shootCooldown_ = kShootInterval_;
	}
}

void Player::Draw() const {
	int x = static_cast<int>(pos_.x - size_.x * 0.5f);
	int y = static_cast<int>(pos_.y - size_.y * 0.5f);
	int w = static_cast<int>(size_.x);
	int h = static_cast<int>(size_.y);
	Novice::DrawBox(x, y, w, h, 0.0f, 0x66CCFFFF, kFillModeSolid);
}

void Player::Shoot(std::vector<Bullet>& bullets) {
	Bullet b;
	b.Initialize({pos_.x + size_.x * 0.5f + 8.0f, pos_.y}, {10.0f, 0.0f});
	bullets.emplace_back(b);
}

void Player::ClampToScreen() {
	float halfW = size_.x * 0.5f;
	float halfH = size_.y * 0.5f;
	if (pos_.x < halfW)
		pos_.x = halfW;
	if (pos_.x > 1280.0f - halfW)
		pos_.x = 1280.0f - halfW;
	if (pos_.y < halfH)
		pos_.y = halfH;
	if (pos_.y > 720.0f - halfH)
		pos_.y = 720.0f - halfH;
}
