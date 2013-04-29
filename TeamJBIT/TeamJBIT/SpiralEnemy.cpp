#include "Utility.h"
#include "SpiralEnemy.h"

SpiralEnemy::SpiralEnemy(std::string file, sf::Vector2f pos, int health = 500, float coolTime = 1.25)
	: Enemy(file, pos, health), coolTime(coolTime), currentTime(0), fireSpiral(false), bulletSpeed(350)
{
	
	sprite.setColor(sf::Color::Red);
}

SpiralEnemy::~SpiralEnemy()
{

}

void SpiralEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	currentTime++;
	sf::Vector2f vel;
	if(abs(pos.x - (SCREEN_WIDTH/2)) > 0)
		vel.x = -(pos.x - SCREEN_WIDTH/2) * .5 * deltaTime;
	if(abs(pos.y - (SCREEN_HEIGHT/2)) > 0)
		vel.y = -(pos.y - SCREEN_HEIGHT/2) * .5 * deltaTime;
	pos += vel;
	sprite.setPosition(pos);
	sprite.setRotation((-atan2f(vel.x, vel.y) * (180 / 3.1415926f)) + 180.f);

	if(currentTime % 100 == 0)
		fireSpiral = true;
	
	if(fireSpiral)
	{
		currentTime = 0;
		fireSpiral = false;
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(0, bulletSpeed), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed, 0), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(0, -bulletSpeed), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed, 0), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * (sqrt(3) / 2), bulletSpeed * .5), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * (sqrt(3) / 2), bulletSpeed * .5), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * (sqrt(3) / 2), -bulletSpeed * .5), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * (sqrt(3) / 2), -bulletSpeed * .5), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * (sqrt(2)/ 2),bulletSpeed * (sqrt(2)/ 2)) , 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * (sqrt(2)/ 2),bulletSpeed * (sqrt(2)/ 2)) , 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * (sqrt(2)/ 2),-bulletSpeed * (sqrt(2)/ 2)) , 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * (sqrt(2)/ 2),-bulletSpeed * (sqrt(2)/ 2)) , 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .5, bulletSpeed * (sqrt(3) / 2)), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .5, bulletSpeed * (sqrt(3) / 2)), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .5, -bulletSpeed * (sqrt(3) / 2)), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .5, -bulletSpeed * (sqrt(3) / 2)), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .965, bulletSpeed *.259), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .965, bulletSpeed *.259), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .965, -bulletSpeed *.259), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .965, -bulletSpeed *.259), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .259, bulletSpeed *.965), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .259, bulletSpeed *.965), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(bulletSpeed * .259, -bulletSpeed *.965), 5, sf::Color(255, 50, 50)));
		eList.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-bulletSpeed * .259, -bulletSpeed *.965), 5, sf::Color(255, 50, 50)));
	}

		
}