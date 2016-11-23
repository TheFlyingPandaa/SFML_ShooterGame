#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
class Enemy: public Entity
{
public:
	Enemy();
	~Enemy();
	void update();
	void enemyHit(bool hs);
	int direc = 0;
	int count = 0;
private:
	int hitPoints = 100;
};



#endif // !ENEMY_H
