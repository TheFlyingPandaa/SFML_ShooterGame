#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "wall.h"
#include "enemy.h"
#include "projectile.h"
#include "particle.h"
#include "GameLogi.h"
using namespace std;

void screenRender(sf::RenderWindow &window, Player&player, Wall &wall, Enemy &enemy1);
void mapLoad(Wall&wall, vector<Wall>& mapArray);
int main() {
	float rotation = 0;
	int counter = 0;
	sf::RenderWindow window(sf::VideoMode(900, 800), "SFML Application"); //Window name + Standard screen
	window.setFramerateLimit(240);
	window.setMouseCursorVisible(false);

	

	Wall wall1;
	int wallAmount = 3;
	vector<Wall> mapArray;

	mapLoad(wall1, mapArray);

	/*Enemy enemy1;
	*/
	vector<Enemy> enemyArray;

	Player player;
	
	Game game;
	
	sf::Clock clock;
	sf::Clock ptclock;
	sf::Clock gameTime;
	sf::Time time, timeTest;

	bool test = false;
	vector<Projectile>::const_iterator enyPro;
	vector<Projectile> enemyProjectile;

	
	vector<Projectile>::const_iterator iter;
	vector<Projectile> projectileArray;

	/*Projectile projectile1;*/
	ParticleSystem particles(1000);

	/*enemy1.circ.setPosition(50, 50);
	enemyArray.push_back(enemy1);
	enemy1.circ.setPosition(150, 150);
	enemyArray.push_back(enemy1);
	enemy1.circ.setPosition(100, 100);
	enemyArray.push_back(enemy1);*/

	int enemyAmount = game.getEnyAmount();

	while (window.isOpen()) { // When open, DO following

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			//Event test Can be deleted
			switch (event.type)
			{
			default:
				break;

			}
			//Stop delete
		}
		//Self explanitory
		
		time = clock.getElapsedTime();
		//cout << time.asSeconds() << endl;
		//clock.restart();
		//
		game.update(gameTime.restart().asSeconds(), window);

		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (player.getAmmo() < player.getAmmoCap())
			{
				if (test == false)
				{
					projectile1.rect.setPosition(player.circ.getPosition());
					projectile1.direction = player.rotation;
					if (player.curser.getGlobalBounds().intersects(enemy1.circ.getGlobalBounds()))
					{
						projectile1.headShoot = true;
					}
					projectileArray.push_back(projectile1);
					test = true;
					timeTest = time;
					player.ammoTick();
				}
			}
			
		}*/
		//cout << player.getAmmo() << endl;
		if (time >= (timeTest + sf::seconds(0.2)))
		{
			test = false;
		}


		//IF BULLET HITS ENEMY OR WALL DESTORY THAT BULLET//

		//counter = 0;
		//for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		//{
		//	for (size_t i = 0; i < wallAmount; i++)
		//	{
		//		if (projectileArray[counter].rect.getGlobalBounds().intersects(mapArray[i].rect.getGlobalBounds()))
		//		{
		//			projectileArray[counter].destory = true;
		//		}
		//	}

		//	if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy1.circ.getGlobalBounds()))
		//	{
		//		enemy1.enemyHit(projectileArray[counter].headShoot);
		//		//enemyArray.erase(enemyArray.begin()+1);
		//		particles.setEmitter(enemy1.circ.getPosition());
		//		particles.execute(player);
		//		projectileArray[counter].destory = true;
		//	}
		//	counter++;
		//}
		//------------------------------------------------// 
		//If bullet BOOL destroy == true. DESTROY---------//
		/*counter = 0;
		*/
		//------------------------------------------------//
		
		/*for (size_t i = 0; i < enemyAmount; i++)
		{
			enemyArray[i].update(player.circ.getPosition());
		}*/
		//enemy1.update(player.circ.getPosition());
		//player.update(window, mapArray, wallAmount);
		//player.movement();

		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		//particles.setEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = ptclock.restart();
		particles.update(elapsed,player);

		//enemyArray = game.getEnyVector();
		projectileArray = game.getProVector();
		enemyProjectile = game.getEnyProVector();
		window.clear();
		window.draw(game);

		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			window.draw(projectileArray[counter].rect);
			counter++;
		}
		counter = 0;
		for (enyPro = enemyProjectile.begin(); enyPro != enemyProjectile.end(); enyPro++)
		{
			window.draw(enemyProjectile[counter].rect);
			counter++;
		}

		
	
		/*vector<Projectile> testt = enemy1.getProjectileArray();
		std::vector<Projectile>::const_iterator iter15 = enemy1.getProjectileIter();
		for (iter15 = testt.begin(); iter15 != testt.end(); iter15++)
		{
			testt[counter].update();
			window.draw(enemy1.getProjectileArray()[counter].rect);
			
			counter++;
		}
		enemy1.setProjectileArray(testt);*/
		

		

		/*for (size_t i = 0; i < wallAmount; i++)
		{
			window.draw(mapArray[i].rect);
		}*/
		//screenRender(window,player,wall1,enemy1); //Inlagd
		window.draw(particles);
		window.display();

	}

}

void screenRender(sf::RenderWindow &window, Player&player, Wall &wall1, Enemy &enemy1) {

	window.draw(player.pointer);
	window.draw(player.circ);
	//window.draw(enemy1.circ);
	//window.draw(wall1.rect);
	window.draw(player.curser);

}

void mapLoad(Wall &wall, vector<Wall>& mapArray)
{
	wall.rect.setPosition(50*1, 50*8);
	wall.rect.setSize(sf::Vector2f(50 * 8, 50 * 1));
	mapArray.push_back(wall);
	wall.rect.setPosition(50* 11, 50*8);
	wall.rect.setSize(sf::Vector2f(50 * 8, 50 * 1));
	mapArray.push_back(wall);
	wall.rect.setPosition(300, 150);
	mapArray.push_back(wall);
}


/*void rotate(sf::RenderWindow &window, Player &player, float &rotation) {
sf::Vector2f curPos = player.pointer.getPosition();
sf::Vector2i position = sf::Mouse::getPosition(window);

const float PI = 3.14159265;

float dx = curPos.x - position.x;
float dy = curPos.y - position.y;

rotation = (atan2(dy, dx)) * 180 / PI;


player.pointer.setRotation(-90 + rotation);
}*/