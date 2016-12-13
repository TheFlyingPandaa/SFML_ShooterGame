#include "node.h"

Node::Node()
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setOrigin(sf::Vector2f(25, 25));
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setFillColor(sf::Color(255, 0, 0, 120));
}

Node::~Node()
{
	
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
}
