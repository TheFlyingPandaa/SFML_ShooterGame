#ifndef GLAS_H
#define GLAS_H
#include "entity.h"

class Glas: public Entity, public sf::Drawable
{
public:
	Glas();
	~Glas();

	void glasShatter();

	bool getShatterd() const;
	void setShatterd(bool shat);
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	bool shatterd = false;
	sf::Texture glasShaterTexture;
	sf::Sprite glasShaterSprite;
};

#endif
