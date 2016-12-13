#ifndef NODE_H
#define NODE_H
#include "entity.h"
class Node: public Entity, public sf::Drawable
{
public:
	Node();
	~Node();
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif

