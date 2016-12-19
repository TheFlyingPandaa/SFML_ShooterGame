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


void Hostage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circ);
}
