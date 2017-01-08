#include "hostage.h"

Hostage::Hostage()
{
	circ.setFillColor(sf::Color::Blue);
	circ.setOutlineThickness(2.f);
	circ.setOutlineColor(sf::Color::Black);
	circ.setRadius(10.f);
	circ.setOrigin(10, 10);

	circ.setPosition(200, 300);
}

Hostage::~Hostage()
{
	
}

void Hostage::takeDamage(const int damage)
{
	this->hp = hp - damage;

	if (hp <= 0)
	{
		circ.setFillColor(sf::Color(0,0,255,150));
		dead = true;
	}
}


void Hostage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circ);
}
