#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "wall.h"
#include "enemy.h"
#include "projectile.h"
#include "particle.h"
using namespace std;

void screenRender(sf::RenderWindow &window, Player&player, Wall &wall, Enemy &enemy1);
int main() {
	float rotation = 0;
	int counter = 0;
	sf::RenderWindow window(sf::VideoMode(800, 740), "SFML Application"); //Window name + Standard screen
	window.setFramerateLimit(240);
	window.setMouseCursorVisible(false);

	

	Wall wall1;
	Enemy enemy1;
	Player player;
	sf::Texture backgroud;
	if (!backgroud.loadFromFile("backgound.jpg"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite backgroundSP;
	backgroundSP.setTexture(backgroud);
	
	sf::Clock clock;
	sf::Clock ptclock;
	sf::Time time, timeTest;

	bool test = false;

	vector<Projectile>::const_iterator iter;
	vector<Projectile> projectileArray;

	Projectile projectile1;
	ParticleSystem particles(1000);

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
			
		}
		//cout << player.getAmmo() << endl;
		if (time >= (timeTest + sf::seconds(0.2)))
		{
			test = false;
		}
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy1.circ.getGlobalBounds()))
			{
				enemy1.enemyHit(projectileArray[counter].headShoot);
				particles.setEmitter(enemy1.circ.getPosition());
				particles.execute(player);
				projectileArray[counter].destory = true;
			}
			counter++;
		}
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].destory == true)
			{
				projectileArray.erase(iter);
				break;
			}
			counter++;
		}

		

		enemy1.update(player.circ.getPosition());
		player.update(window, wall1);
		player.movement();

		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		//particles.setEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = ptclock.restart();
		particles.update(elapsed,player);

		window.clear();
		window.draw(backgroundSP);
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update();
			window.draw(projectileArray[counter].rect);

			counter++;
		}
		counter = 0;
		/*vector<Projectile> testt = enemy1.getProjectileArray();
		for (iter = enemy1.getProjectileArray().begin(); iter != enemy1.getProjectileArray().end(); iter++)
		{
			testt[counter].update();
			window.draw(enemy1.getProjectileArray()[counter].rect);
			
			counter++;
		}
		enemy1.setProjectileArray(testt);*/
		screenRender(window,player,wall1,enemy1);
		window.draw(particles);
		window.display();

	}

}

void screenRender(sf::RenderWindow &window, Player&player, Wall &wall1, Enemy &enemy1) {

	window.draw(player.pointer);
	window.draw(player.circ);
	window.draw(enemy1.circ);
	window.draw(wall1.rect);
	window.draw(player.curser);

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