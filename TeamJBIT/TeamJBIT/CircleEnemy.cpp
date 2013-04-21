#include "CircleEnemy.h"
#include "Utility.h"

CircleEnemy::CircleEnemy(std::string file, sf::Vector2f pos, int health) : Enemy(file, pos, health), currentTargetAngle(270), localTargetPos(0, -150) {
	currentTargetDistance = std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
}

void CircleEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player) {
	float distance = vecLen(player.pos - pos);

	//rotate target pos around player
	localTargetPos.x = cosf(deg2rad(currentTargetAngle)) * currentTargetDistance;
	localTargetPos.y = sinf(deg2rad(currentTargetAngle)) * currentTargetDistance;

	float angleIncrease = ((75 / currentTargetDistance) * 180) * deltaTime;
	currentTargetAngle += angleIncrease;
	if (currentTargetAngle >= 360) currentTargetAngle -= 360;

	if (currentTargetDistance > 100)
		currentTargetDistance-= 40 * deltaTime;

	//shoot
	if (bulletClock.getElapsedTime().asSeconds() > 0.5) {
		eList.push_back(new Bullet("media/bullet.png", pos, 400.f * normalize(player.pos - pos), 5, sf::Color(255, 50, 50)));
		bulletClock.restart();
	}

	//get to target pos
	sf::Vector2f direction = (player.pos + localTargetPos) - pos;
	float targetDist = vecLen(direction);
	direction = normalize(direction);

	float speed = (deg2rad(angleIncrease) * currentTargetDistance);
	float dist = std::min(speed, targetDist); //don't overshoot
	pos += direction * dist;
	sprite.setPosition(pos);
}