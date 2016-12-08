#include "flashBang.h"
#include <iostream>
#define PI 3.14159265
Flashbang::Flashbang()
{
	rect.setSize(sf::Vector2f(10, 10));
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(5, 5);
	circ.setRadius(100.f);
	circ.setFillColor(sf::Color::Transparent);
	circ.setPosition(300, 300);
	circ.setOrigin(100, 100);
}

Flashbang::~Flashbang()
{
	
}

void Flashbang::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
	target.draw(circ);
}

void Flashbang::update(sf::Vector2f&playerPos)
{
	if (active == false)
	{
		rect.setPosition(playerPos);
		throws = false;
	}
	
	dx = pow(abs(playerPos.x - rect.getPosition().x), 2);
	dy = pow(abs(playerPos.y - rect.getPosition().y), 2);

	dLenght = sqrt(dx + dy);
	if (active == true)
	{
		x = cos((direction - 180) * PI / 180);
		y = sin((direction - 180) * PI / 180);
		rect.move(x * 2, y * 2);
		throws = true;
	}
	if (bangs == false)
	{
		circ.setFillColor(sf::Color::Transparent);
	}
}

void Flashbang::explode()
{
	bangs = true;
	circ.setFillColor(sf::Color::Yellow);
	circ.setPosition(rect.getPosition());
	std::cout << "AWESHEIPQWE" << std::endl;
}

