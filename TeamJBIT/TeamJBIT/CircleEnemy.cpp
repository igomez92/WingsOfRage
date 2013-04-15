#include "CircleEnemy.h"
#include "Utility.h"

CircleEnemy::CircleEnemy(std::string file, sf::Vector2f pos, int health) : Enemy(file, pos, health), currentTargetAngle(270), localTargetPos(0, -150) {

}

void CircleEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player) {
	float distance2 = vecLen2((player.pos +  localTargetPos) - pos);

	if (distance2 < 75*75) { //rotate target pos around player
		localTargetPos.x = cosf(deg2rad(currentTargetAngle)) * 150;
		localTargetPos.y = sinf(deg2rad(currentTargetAngle)) * 150;

		currentTargetAngle += 90 * deltaTime;
		if (currentTargetAngle >= 360) currentTargetAngle -= 360;

		//shoot
		if (bulletClock.getElapsedTime().asSeconds() > 0.5) {
			eList.push_back(new Bullet("media/bullet.png", pos, 400.f * normalize(player.pos - pos), 5, sf::Color(255, 50, 50)));
			bulletClock.restart();
		}
	}

	//get to target pos
	sf::Vector2f direction = normalize((player.pos + localTargetPos) - pos);
	pos += direction * (150 * deltaTime);
	sprite.setPosition(pos);
}