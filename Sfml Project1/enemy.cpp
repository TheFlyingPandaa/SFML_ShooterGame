#include "enemy.h"
#include <iostream>
#define PI 3.14159265

Enemy::Enemy()
{
	
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(10.f);
	circ.setPosition(sf::Vector2f(200, 200));
	circ.setOrigin(sf::Vector2f(10, 10));
	
}

void Enemy::update(const sf::Vector2f& PlayerPlace) {
	circ.getPosition();

	dx = pow(abs(PlayerPlace.x - circ.getPosition().x), 2);
	dy = pow(abs(PlayerPlace.y - circ.getPosition().y), 2);
	distanceToPlayer = sqrt(dx + dy);
	//std::cout << this->rotation << std::endl;
	std::cout << this->getProjectileArray().size() << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {

		if (distanceToPlayer < 100)
		{
			//this->speed = 1;
			//enemyShoot(PlayerPlace);
		}
		else
		{
			this->speed = 0.2;
		}
	}
	if (this->hitPoints <= 0)
	{
		circ.setFillColor(sf::Color::Transparent);
	}
	if (direc == 0)
	{
		circ.move(sf::Vector2f(this->speed, 0));
		count++;
		if (count >= 1000)
		{
			direc = 1;
			count = 0;
		}
	}
	if (direc == 1)
	{
		circ.move(sf::Vector2f(-this->speed, 0));
		count++;
		if (count >= 1000)
		{
			direc = 0;
			count = 0;
		}
	}
}

Enemy::~Enemy()
{
}

void Enemy::setProjectileArray(std::vector<Projectile>&pro)
{
	this->getProjectileArray() = pro;
}


void Enemy::enemyHit(bool hs) {
	if (hs == true)
	{
		this->hitPoints -= 100;
	}
	else
	{
		this->hitPoints -= 50;
	}
	
}

void Enemy::enemyShoot(const sf::Vector2f& PlayerPlace)
{
	
	dx1 = PlayerPlace.x - circ.getPosition().x;
	dy1 = PlayerPlace.x - circ.getPosition().y;

	this->rotation = (atan2(dy, dx)) * 360 / PI;

	circ.setRotation(-90 + this->rotation);

	projectile.rect.setPosition(circ.getPosition());
	projectile.direction = circ.getRotation();
	enemyProjectArray.push_back(projectile);

}

std::vector<Projectile> Enemy::getProjectileArray()
{
	return this->enemyProjectArray;
}

std::vector<Projectile>::const_iterator Enemy::getProjectileIter()
{
	return this->iter;
}
