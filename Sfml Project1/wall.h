#ifndef WALL_H
#define WALL_H
#include "entity.h"
class Wall: public Entity, sf::Drawable
{
public:
	Wall();
	~Wall();

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};




#endif
