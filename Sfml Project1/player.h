#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "wall.h"
class Player: public Entity
{
public:
	int movementSpeed = 1;
	float lenght = 100;
	sf::RectangleShape pointer;
	sf::RectangleShape curser;

	
	void rotateUpdate(sf::RenderWindow &window);
	Player();
	~Player();
	void movement();
	void update(sf::RenderWindow &window, Wall & wall);
	float rotation = 0;
	int direction = 0;

	int getAmmoCap() const;
	int getAmmo() const;
	void ammoTick();
private:
	int ammoCap = 30;
	int ammo = 0;

	void reload();
};



#endif