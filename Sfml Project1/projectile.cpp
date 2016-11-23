#include "projectile.h"
#include <math.h>

#define PI 3.14159265
Projectile::Projectile()
{
	rect.setSize(sf::Vector2f(10,10));
	rect.setOrigin(5, 5);
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(0, 0);

	

}

Projectile::~Projectile()
{
}

void Projectile::update() {
	float x = cos((direction-180) * PI /180);
	float y = sin((direction-180) * PI / 180);
	rect.move(x*5, y*5);

	lifeTimeCounter++;
	if (lifeTimeCounter >= lifeTime)
	{
		destory = true;
	}
	
}