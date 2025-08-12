#pragma once

struct Vec2;

class Bullet {
public:
	void Initialize(const Vec2& pos, const Vec2& vel);
	void Update();
	void Draw() const;

	bool IsAlive() const { return alive_; }
	void Kill() { alive_ = false; }

	// AABB
	float Left() const { return posX_ - radius_; }
	float Right() const { return posX_ + radius_; }
	float Top() const { return posY_ - radius_; }
	float Bottom() const { return posY_ + radius_; }

private:
	float posX_ = 0.0f;
	float posY_ = 0.0f;
	float velX_ = 0.0f;
	float velY_ = 0.0f;
	float radius_ = 6.0f;
	bool alive_ = false;
};
