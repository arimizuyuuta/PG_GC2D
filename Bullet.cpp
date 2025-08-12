#include "Bullet.h"
#include <Novice.h>

struct Vec2 {
	float x, y;
};

void Bullet::Initialize(const Vec2& pos, const Vec2& vel) {
	posX_ = pos.x;
	posY_ = pos.y;
	velX_ = vel.x;
	velY_ = vel.y;
	radius_ = 6.0f;
	alive_ = true;
}

void Bullet::Update() {
	if (!alive_)
		return;
	posX_ += velX_;
	posY_ += velY_;

	// 画面外で消滅
	if (posX_ < -20.0f || posX_ > 1300.0f || posY_ < -20.0f || posY_ > 740.0f) {
		alive_ = false;
	}
}

void Bullet::Draw() const {
	if (!alive_)
		return;
	Novice::DrawEllipse(static_cast<int>(posX_), static_cast<int>(posY_), static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, 0xFFFFFFFF, kFillModeSolid);
}
