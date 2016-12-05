#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
#include "projectile.h"

class Enemy: public sf::Drawable, public Entity
{
public:
	Enemy();
	~Enemy();
	void update(const sf::Vector2f& PlayerPlace);
	void enemyHit(bool hs);
	int direc = 0;
	int count = 0;

	float getDistanceToPlayer();
private:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::vector<Projectile>::const_iterator iter;
	std::vector<Projectile> enemyProjectArray;
	Projectile projectile;

	void enemyShoot(const sf::Vector2f& PlayerPlace);

	int hitPoints = 100;
	float distanceToPlayer = 0;
	float dx=0, dy = 0;
	float dx1=0, dy1 = 0;
	double speed = 0.2;
	float rotation = 0;
};



#endif // !ENEMY_H
