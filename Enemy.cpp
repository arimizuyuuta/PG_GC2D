#include "Enemy.h"
#include <Novice.h>

void Enemy::Initialize() {
	posX_ = 1000.0f;
	posY_ = 360.0f;
	size_ = 48.0f;
	hp_ = 10;
	vx_ = 3.0f;
}

void Enemy::Update() {
	posX_ += vx_;
	if (posX_ > 1150.0f)
		vx_ = -vx_;
	if (posX_ < 700.0f)
		vx_ = -vx_;
}

void Enemy::Draw() const {
	int x = static_cast<int>(posX_ - size_ * 0.5f);
	int y = static_cast<int>(posY_ - size_ * 0.5f);
	int s = static_cast<int>(size_);
	Novice::DrawBox(x, y, s, s, 0.0f, 0xFF6666FF, kFillModeSolid);

	// HP表示
	Novice::ScreenPrintf(940, 40, "ENEMY HP: %d", hp_);
}

void Enemy::Hit(int dmg) {
	hp_ -= dmg;
	if (hp_ < 0)
		hp_ = 0;
}
