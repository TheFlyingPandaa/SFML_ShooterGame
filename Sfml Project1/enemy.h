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
	
	void setEnyTime(sf::Time enyTime);
	sf::Time getEnyTime() const;
	void setEnyTest(bool enyTest);
	bool getEnyTest() const;

	void setBlinded(bool bol);
	bool getBlinded() const;

	float getDistanceToPlayer();
	float getRotation();
	bool getDead() const;
	void enemyShoot(const sf::Vector2f& PlayerPlace);
private:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	bool blinded = false;
	bool dead = false;

	int hitPoints = 100;
	float distanceToPlayer = 0;
	float dx=0, dy = 0;
	float dx1=0, dy1 = 0;
	double speed = 0.2;
	float rotation = 0;

	bool enyTest = false;
	sf::Time enyTime;
};



#endif // !ENEMY_H
