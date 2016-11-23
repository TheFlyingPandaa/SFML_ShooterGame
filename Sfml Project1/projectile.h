#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"

class Projectile: public Entity
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

};



#endif
