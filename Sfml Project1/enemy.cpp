#include "enemy.h"
#include <iostream>
Enemy::Enemy()
{
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(10.f);
	circ.setPosition(sf::Vector2f(200, 200));
	circ.setOrigin(sf::Vector2f(10, 10));
	
}

void Enemy::update() {
	circ.getPosition();
	
	if (this->hitPoints <= 0)
	{
		circ.setFillColor(sf::Color::Transparent);
	}
	if (direc == 0)
	{
		circ.move(sf::Vector2f(0.2, 0));
		count++;
		if (count >= 1000)
		{
			direc = 1;
			count = 0;
		}
	}
	if (direc == 1)
	{
		circ.move(sf::Vector2f(-0.2, 0));
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