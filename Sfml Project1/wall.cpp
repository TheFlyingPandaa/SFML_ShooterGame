#include "wall.h"

Wall::Wall()
{
	rect.setFillColor(sf::Color::Color(255, 129, 33));
	rect.setPosition(sf::Vector2f(100,100));
	rect.setSize(sf::Vector2f(100, 100));
	rect.setOrigin(sf::Vector2f(50, 50));
}

Wall::~Wall()
{
}