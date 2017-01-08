#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "wall.h"
#include "glas.h"
class Player: public sf::Drawable, public Entity
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
	void update(sf::RenderWindow &window, std::vector<Wall>&mapArray, int wallAmount, std::vector<Glas>&glasArray, int glasAmount);
	float rotation = 0;
	int direction = 0;

	int getAmmoCap() const;
	int getAmmo() const;

	int getHp() const;
	void damagePlayer(const int damage);

	void ammoTick();
private:
	int ammoCap = 30;
	int ammo = 0;

	int hp = 100;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void reload();
};



#endif