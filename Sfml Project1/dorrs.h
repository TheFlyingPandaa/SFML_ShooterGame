#ifndef DOORS_H
#define DOORS_H
#include "entity.h"

class Doors: public sf::Drawable, public Entity
{
public:
	Doors();
	~Doors();

	void doorSlide();
	void doorSlideBack();
	bool moving = false;
	bool moved = false;
private:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	int slideCap = 50;
	float counter;
	bool locked = false;
	
};

#endif

