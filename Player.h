#pragma once
#include "Bullet.h"
#include <vector>

struct Vec2 {
	float x, y;
};

class Player {
public:
	Player();
	void Initialize();
	void Update(char* keys, char* preKeys, std::vector<Bullet>& bullets);
	void Draw() const;

	// 当たり判定用
	float Left() const { return pos_.x - size_.x * 0.5f; }
	float Right() const { return pos_.x + size_.x * 0.5f; }
	float Top() const { return pos_.y - size_.y * 0.5f; }
	float Bottom() const { return pos_.y + size_.y * 0.5f; }

private:
	Vec2 pos_{};
	Vec2 size_{};
	float speed_ = 6.0f;

	// 弾発射
	int shootCooldown_ = 0;        // フレーム
	const int kShootInterval_ = 8; // 連射間隔

	void Shoot(std::vector<Bullet>& bullets);
	void ClampToScreen();
};
