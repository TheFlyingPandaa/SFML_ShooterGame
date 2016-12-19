#ifndef HOSTAGE_H
#define HOSTAGE_H
#include "entity.h"
class Hostage: public sf::Drawable, public Entity
{
public:
	Hostage();
	~Hostage();
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
