#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
#include "projectile.h"
#include "node.h"
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

	bool getEnyDead() const;
	void setEnyDead(bool bol);

	/*int getNodeCounter() const;
	void setNodeCounter(int node);*/
	void nodeCatcher(std::vector<Node> *& nodeArray);
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

	bool deBug = false;
	int nodeCounter = 0;
	std::vector<Node> * nodeArray = new std::vector<Node>[1];
	float dxDe = 0;
	float dyDe = 0;
	float walkRotation = 0;

	bool enyDead = false;
	bool enyTest = false;
	sf::Time enyTime;
};



#endif // !ENEMY_H
