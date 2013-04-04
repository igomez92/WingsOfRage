#pragma once
#include "ParticleManager.h"


ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::doExplosion(std::list<Particle*>& allParticles, sf::Vector2f pos, sf::Color particleColor, float lifeExpectancy)
{
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f (0,-600), particleColor, lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(0, 600), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(600,0), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(-600, 0), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(600,600), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(600,-600), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(-600,600), particleColor,lifeExpectancy));
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(-600,-600), particleColor,lifeExpectancy));
}

void ParticleManager::doHitParticle(std::list<Particle*>& allParticles, sf::Vector2f pos, sf::Vector2f vel, sf::Color particleColor, float lifeExpectancy)
{
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(vel.x,vel.y), particleColor, lifeExpectancy));
}

void ParticleManager::doEnginePartcle(std::list<Particle*>& allParticles, sf::Vector2f pos, sf::Color particleColor, float lifeExpectancy)
{
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(rand() % 180 - 90, rand() % 400 + 30), particleColor, lifeExpectancy)); 
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(rand() % 180 - 90, rand() % 400 + 30), sf::Color::Color(0, 255, 108, 255), lifeExpectancy)); 
	allParticles.push_back(new Particle("media/particle.png", pos, sf::Vector2f(rand() % 180 - 90, rand() % 400 + 30), sf::Color::Color(0, 106, 255, 255), lifeExpectancy)); 

}

void ParticleManager::doLaserParticleEffect(std::list<Particle*>& allParticles, sf::Vector2f pos, sf::Vector2f vel, sf::Color particleColor, float lifeExpectancy)
{
	
}



