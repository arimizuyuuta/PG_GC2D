#pragma once

class Enemy {
public:
	void Initialize();
	void Update();
	void Draw() const;

	// ダメージ
	void Hit(int dmg);
	bool IsDead() const { return hp_ <= 0; }

	// AABB
	float Left() const { return posX_ - size_ * 0.5f; }
	float Right() const { return posX_ + size_ * 0.5f; }
	float Top() const { return posY_ - size_ * 0.5f; }
	float Bottom() const { return posY_ + size_ * 0.5f; }

private:
	float posX_ = 0.0f;
	float posY_ = 0.0f;
	float size_ = 48.0f;
	int hp_ = 10;

	// 簡単な左右パトロール
	float vx_ = 3.0f;
};
