#ifndef HOSTAGE_H
#define HOSTAGE_H
#include "entity.h"
class Hostage: public sf::Drawable, public Entity
{
public:
	Hostage();
	~Hostage();

	void takeDamage(const int damage);
private:

	int hp = 100;
	bool  dead = false;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
