#ifndef ENTITY_H
#define ENTITY_H
#include <SFML\Graphics.hpp>



class Entity
{
public:

	sf::Sprite sprite;
	sf::CircleShape circ;
	sf::RectangleShape rect;
	sf::Text text;

	Entity();
	~Entity();

private:

};




#endif
