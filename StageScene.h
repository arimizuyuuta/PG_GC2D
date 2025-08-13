#pragma once
#include "IScene.h"
#include <vector>

class StageScene : public IScene {
public:
	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	struct Vec2 {
		float x, y;
	};

	struct Player {
		Vec2 pos;
		float speed;
		float radius;
	} player_;

	struct Bullet {
		Vec2 pos, vel;
		float radius;
		bool alive;
	};
	std::vector<Bullet> bullets_;
	int shotCooldown_; // 連射抑制（フレーム）

	struct Enemy {
		Vec2 pos;
		Vec2 base;
		float t; // 動き用タイマ
		float radius;
		bool alive;
		int deadTimer; // 撃破アニメ用
	};
	std::vector<Enemy> enemies_;

	// ユーティリティ
	static float LengthSq(const Vec2& a, const Vec2& b) {
		float dx = a.x - b.x, dy = a.y - b.y;
		return dx * dx + dy * dy;
	}
};
