#include "dorrs.h"

Doors::Doors()
{
	rect.setSize(sf::Vector2f(25, 50));
	rect.setOrigin(sf::Vector2f(12.5, 25));
	rect.setFillColor(sf::Color(142, 59, 0, 255));
	rect.setRotation(0);
	circ.setRadius(100.f);
	circ.setOrigin(100, 100);
	circ.setFillColor(sf::Color::Black);
	circ.setPosition(275, 225);
}

Doors::~Doors()
{
	
}

void Doors::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
	//target.draw(circ);
}

void Doors::doorSlide()
{
	if (locked == false)
	{
		if (slideCap >= counter)
		{
			moved = true;
			if (rect.getRotation() == 0)
			{
				rect.move(sf::Vector2f(0, -0.5));
				counter += 0.5;
			}
			else if (rect.getRotation() == 90)
			{

			}
			else if (rect.getRotation() == 180)
			{

			}
			else if (rect.getRotation() == 270)
			{

			}
		}
	}
}
void Doors::doorSlideBack()
{
	if (counter >= 0)
	{
		if (rect.getRotation() == 0)
		{
			rect.move(sf::Vector2f(0, +0.5));
			counter -= 0.5;
		}
		else if (rect.getRotation() == 90)
		{

		}
		else if (rect.getRotation() == 180)
		{

		}
		else if (rect.getRotation() == 270)
		{

		}
	}
}


