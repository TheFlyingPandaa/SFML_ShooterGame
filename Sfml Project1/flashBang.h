#ifndef FLASHBANG_H
#define FLASHBANG_H

#include "enemy.h"

class Flashbang: public sf::Drawable, public Entity
{
public:
	Flashbang();
	~Flashbang();
	float x = 0, y = 0;
	float direction = 0;
	float dx = 0, dy = 0;
	float dLenght =10000;

	bool active = false;
	bool throws = false;
	bool bangs = false;

	sf::Time timeAmount;
	void explode();
	void update(sf::Vector2f&playerPos);
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif

