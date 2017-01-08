#include "player.h"
#include <stdlib.h>
#include <math.h>


#define PI 3.14159265;

Player::Player()
{
	circ.setFillColor(sf::Color::Yellow);
	circ.setRadius(10.f);
	circ.setPosition(100, 100);
	circ.setOrigin(sf::Vector2f(10, 10));

	circ.setOutlineThickness(2.f);
	circ.setOutlineColor(sf::Color::Black);

	pointer.setFillColor(sf::Color::Red);
	pointer.setSize(sf::Vector2f(2.5, 300));
	pointer.setOrigin(sf::Vector2f(1.25, 0));


	curser.setSize(sf::Vector2f(2, 2));
	curser.setOrigin(sf::Vector2f(1, 1));
	curser.setFillColor(sf::Color::Cyan);
	curser.setPosition(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	//curser.setPosition(sf::Vector2f(300, 300));
}

int Player::getAmmoCap() const
{
	return this->ammoCap;
}

int Player::getAmmo() const
{
	return this->ammo;
}

void Player::reload() 
{
	this->ammo = 0;
}

void Player::ammoTick()
{
	this->ammo++;
}


Player::~Player()
{
}

void Player::movement() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		reload();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		circ.move(sf::Vector2f(-movementSpeed, 0));
		direction = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		circ.move(sf::Vector2f(movementSpeed, 0));
		direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		circ.move(sf::Vector2f(0, -movementSpeed));
		direction = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		circ.move(sf::Vector2f(0, movementSpeed));
		direction = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = 6;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = 7;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = 8;
	}
}
void Player::update(sf::RenderWindow &window, std::vector<Wall>&mapArray, int wallAmount, std::vector<Glas>&glasArray, int glasAmount) {
	float dx = pow(abs(sf::Mouse::getPosition(window).x - circ.getPosition().x), 2);
	float dy = pow(abs(sf::Mouse::getPosition(window).y - circ.getPosition().y), 2);
	
	lenght = sqrt(dx + dy);
	curser.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
	pointer.setSize(sf::Vector2f(2.5, -lenght));
	
	pointer.setPosition(circ.getPosition());
	
	rotateUpdate(window);

	if (hp <= 0)
	{
		circ.setPosition(100, 600);
		hp = 100;
	}


	for (size_t i = 0; i < wallAmount; i++) {
		if (circ.getGlobalBounds().intersects(mapArray[i].rect.getGlobalBounds()))
		{
			if (direction == 1)
			{
				circ.move(sf::Vector2f(1.5, 0));
			}
			if (direction == 2)
			{
				circ.move(sf::Vector2f(-1.5, 0));
			}
			if (direction == 3)
			{
				circ.move(sf::Vector2f(0, 1.5));
			}
			if (direction == 4)
			{
				circ.move(sf::Vector2f(0, -1.5));
			}
			if (direction == 5)
			{
				circ.move(sf::Vector2f(-1.5, 1.5));
			}
			if (direction == 6)
			{
				circ.move(sf::Vector2f(1.5, 1.5));
			}
			if (direction == 7)
			{
				circ.move(sf::Vector2f(-1.5, -1.5));
			}
			if (direction == 8)
			{
				circ.move(sf::Vector2f(1.5, -1.5));
			}
		}
	}

	for (size_t i = 0; i < glasAmount; i++)
	{
		if (glasArray[i].getShatterd() == false)
		{
			if (circ.getGlobalBounds().intersects(glasArray[i].rect.getGlobalBounds()))
			{
				if (direction == 1)
				{
					circ.move(sf::Vector2f(1.5, 0));
				}
				if (direction == 2)
				{
					circ.move(sf::Vector2f(-1.5, 0));
				}
				if (direction == 3)
				{
					circ.move(sf::Vector2f(0, 1.5));
				}
				if (direction == 4)
				{
					circ.move(sf::Vector2f(0, -1.5));
				}
				if (direction == 5)
				{
					circ.move(sf::Vector2f(-1.5, 1.5));
				}
				if (direction == 6)
				{
					circ.move(sf::Vector2f(1.5, 1.5));
				}
				if (direction == 7)
				{
					circ.move(sf::Vector2f(-1.5, -1.5));
				}
				if (direction == 8)
				{
					circ.move(sf::Vector2f(1.5, -1.5));
				}
			}
		}
	}
}

void Player::rotateUpdate(sf::RenderWindow &window) {
	sf::Vector2f curPos = pointer.getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(window);

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	this->rotation = (atan2(dy, dx)) * 180 / PI;


	pointer.setRotation(-90 + this->rotation);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pointer);
	target.draw(circ);
	target.draw(curser);
}

int Player::getHp() const
{
	return hp;
}

void Player::damagePlayer(const int damage)
{
	this->hp = hp - damage;
}
