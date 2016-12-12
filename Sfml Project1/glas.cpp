#include "glas.h"

Glas::Glas()
{
	rect.setSize(sf::Vector2f(25, 50));
	rect.setPosition(525, 500);
	rect.setFillColor(sf::Color(79, 145, 249,125));
	rect.setOrigin(12.5, 25);
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(sf::Color(11, 69, 163, 255));

	if (!glasShaterTexture.loadFromFile("glasShater.png"))
	{
		
	}
	glasShaterSprite.setTexture(glasShaterTexture);
	glasShaterSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	//glasShaterSprite.setColor(sf::Color::Transparent);
	glasShaterSprite.setOrigin(10, 20);
}

Glas::~Glas()
{
	
}

void Glas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
	target.draw(glasShaterSprite);
}

void Glas::setShatterd(bool shat)
{
	this->shatterd = shat;
}

bool Glas::getShatterd() const
{
	return this->shatterd;
}

void Glas::glasShatter()
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition((rect.getPosition().x - 12.5), rect.getPosition().y);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Transparent);
	glasShaterSprite.setPosition(rect.getPosition());
}
