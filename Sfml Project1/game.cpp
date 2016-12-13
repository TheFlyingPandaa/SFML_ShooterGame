#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
#include "projectile.h"
#include "particle.h"
#include "GameLogi.h"
using namespace std;


int main() {
	float rotation = 0;
	int counter = 0;
	sf::RenderWindow window(sf::VideoMode(900, 800), "SFML Application"); //Window name + Standard screen
	window.setFramerateLimit(240);
	window.setMouseCursorVisible(false);

	

	/*Enemy enemy1;
	*/
	
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
	
		time = clock.getElapsedTime();
		
		game.update(gameTime.restart().asSeconds(), window);

		
		if (time >= (timeTest + sf::seconds(0.2)))
		{
			test = false;
		}


		sf::Time elapsed = ptclock.restart();
		//particles.update(elapsed,player); //DONT REMOVE

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

	
		window.draw(particles);
		window.display();

	}

}

