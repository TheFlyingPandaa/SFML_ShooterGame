#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "entity.h"

class Projectile: public sf::Drawable, public Entity
{
public:
	
	Projectile();
	~Projectile();
	float direction = 0;
	bool destory = false;
	void update();

	bool headShoot = false;
	int lifeTimeCounter = 0;
	int lifeTime = 1000;
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};



#endif
