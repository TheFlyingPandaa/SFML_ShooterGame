#ifndef GAMELOGI_H
#define GAMELOGI_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include "wall.h"
#include "projectile.h"
#include "enemy.h"
#include "flashBang.h"
#include "glas.h"
#include "node.h"
#include "dorrs.h"
#include <vector>
class Game: public sf::Drawable
{
public:
	Game();
	~Game();
	std::vector<Projectile> getProVector() const;
	std::vector<Projectile> getEnyProVector() const;
	std::vector<Enemy> getEnyVector() const;
	int getEnyAmount() const;

	void update(float dt, sf::RenderWindow &window);
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void calcRotation();
	Player mPlayer;
	std::vector<Projectile> projectileArray;
	std::vector<Projectile>::const_iterator proIter;
	Projectile mProjectile;
	sf::Vector2f playerPos;
	bool enyTest = false;
	bool testt = false;
	bool justonce = true;
	void colisionTest();
	int k = 0;
	bool first = true;

	//Nodes
	Node node;
	std::vector<Node> * nodeArray;
	void nodeMap();
	int amountOfEnemyNodes = 0;
	void enemyNodeCatcher();

	//Walls
	Wall wall;
	int wallAmount = 0;
	std::vector<Wall> wallArray;
	void wallMap(int & wallAmount, Wall & wall, std::vector<Wall>& wallArray);

	Doors door;
	void doorMap();

	Glas glas;
	std::vector<Glas> glasArray;
	int glasAmount = 0;
	void glasMap();

	Enemy objEnemy;
	std::vector<Enemy> enemyArray;
	std::vector<Enemy>::const_iterator enyIter;
	int enemyAmount = 0;
	void enemyMap(int & enemyAmount, Enemy &objEnemy, std::vector<Enemy>& enemyArray);

	Projectile eProjectile;
	std::vector<Projectile> enemyProjectileArr;
	std::vector<Projectile>::const_iterator enyProIter;

	//Textures
	void loadTextures();
	sf::Texture windowBackground;
	sf::Sprite windowBGSprite;

	Flashbang flashbang;
	float flashLenght;

	sf::Clock clock;
	sf::Time time, timeTest, enyTimeTest;
};

#endif

