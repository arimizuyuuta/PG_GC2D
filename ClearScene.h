#pragma once
#include "IScene.h"
#include <memory>
#include <vector>

class Player;
class Bullet;
class Enemy;

class StageScene : public IScene {
public:
	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	std::unique_ptr<Player> player_;
	std::unique_ptr<Enemy> enemy_;
	std::vector<Bullet> bullets_;

	static bool AABB(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2) { return !(r1 < l2 || r2 < l1 || b1 < t2 || b2 < t1); }
};
