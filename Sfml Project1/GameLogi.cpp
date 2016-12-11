#include "GameLogi.h"
#include <iostream>

Game::Game()
{
	loadTextures();
	wallMap(this->wallAmount, this->wall, this->wallArray);
	enemyMap(this->enemyAmount, this->objEnemy, this->enemyArray);
}

Game::~Game()
{
	flashbang.rect.setPosition(mPlayer.circ.getPosition());
}

void Game::update(float dt, sf::RenderWindow &window)
{
	//Player
	time += clock.getElapsedTime();
	clock.restart();
	//std::cout << projectileArray.capacity() << std::endl;
	mPlayer.update(window, this->wallArray, this->wallAmount);
	mPlayer.movement();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "pew pew" << std::endl;
		if (mPlayer.getAmmo() < mPlayer.getAmmoCap())
		{
			if (testt != true)
			{
				mProjectile.rect.setPosition(mPlayer.circ.getPosition());
				mProjectile.direction = mPlayer.rotation;
				for (size_t i = 0; i < this->enemyAmount; i++) {
					if (mPlayer.curser.getGlobalBounds().intersects(enemyArray[i].circ.getGlobalBounds()))
					{
						mProjectile.headShoot = true;
						mProjectile.rect.setFillColor(sf::Color::Blue);
					}
				}
				projectileArray.push_back(mProjectile);
				testt = true;
				timeTest = time;
				timeTest += sf::seconds(0.2);
				mPlayer.ammoTick();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		flashbang.active = true;
		flashbang.direction = mPlayer.rotation;
		flashbang.rect.setPosition(mPlayer.circ.getPosition());
		flashLenght = mPlayer.lenght;
	}
	//playerPos = mPlayer.circ.getPosition();
	flashbang.update(sf::Vector2f(mPlayer.circ.getPosition()));
	//std::cout << mPlayer.lenght << std::endl;

	if (flashLenght <= flashbang.dLenght)
	{
		flashbang.active = false;
		if (flashbang.throws == true)
		{
			flashbang.explode();
			flashbang.timeAmount = time;
		}
	}

	if (flashbang.bangs == true)
	{
		if (flashbang.timeAmount + sf::seconds(3) < time)
		{
			flashbang.bangs = false;
		}
	}


	for (size_t i = 0; i < this->enemyAmount; i++)
	{
		if (enemyArray[i].getDistanceToPlayer() < 150)
		{
			if (enyTest != true)
			{
				enemyArray[i].enemyShoot(sf::Vector2f(mPlayer.circ.getPosition()));
				eProjectile.rect.setPosition(enemyArray[i].circ.getPosition());
				eProjectile.direction = enemyArray[i].getRotation();
				enemyProjectileArr.push_back(eProjectile);
				enyTest = true;

				enyTimeTest = time;
				enyTimeTest += sf::seconds(0.2);
			}
		}
	}
	if (time >= timeTest)
	{
		testt = false;
	}
	if (time >= enyTimeTest)
	{
		enyTest = false;
	}

	int counter = 0;

	for (enyProIter = enemyProjectileArr.begin(); enyProIter != enemyProjectileArr.end(); enyProIter++)
	{
		enemyProjectileArr[counter].update();
		counter++;
	}
	counter = 0;
	for (proIter = projectileArray.begin(); proIter != projectileArray.end(); proIter++)
	{
		projectileArray[counter].update();
		//this->test = true;
		counter++;
	}

	for (size_t i = 0; i < enemyAmount; i++)
	{
		enemyArray[i].update(mPlayer.circ.getPosition());
	}

	
	colisionTest();


}

void Game::colisionTest()
{
	
	int counter = 0;
	for (proIter = projectileArray.begin(); proIter != projectileArray.end(); proIter++)
	{
		for (size_t i = 0; i < this->wallAmount; i++)
		{
			if (projectileArray[counter].rect.getGlobalBounds().intersects(wallArray[i].rect.getGlobalBounds()))
			{
				projectileArray[counter].destory = true;
			}
		}
		for (size_t j = 0; j < this->enemyAmount; j++)
		{
			if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[j].circ.getGlobalBounds()))
			{
				enemyArray[j].enemyHit(projectileArray[counter].headShoot);
				projectileArray[counter].destory = true;
			}
		}
		counter++;
	}
	counter = 0;
	for (proIter = projectileArray.begin(); proIter != projectileArray.end(); proIter++)
	{
		if (projectileArray[counter].destory == true)
		{
			projectileArray.erase(proIter);
			break;
		}
		counter++;
	}

	counter = 0;
	for (enyProIter = enemyProjectileArr.begin(); enyProIter != enemyProjectileArr.end(); enyProIter++)
	{
		if (enemyProjectileArr[counter].destory == true)
		{
			enemyProjectileArr.erase(enyProIter);
			break;
		}
		counter++;
	}

	if (flashbang.throws == true)
	{
		for (size_t i = 0; i < this->wallAmount; i++)
		{
			if(flashbang.rect.getGlobalBounds().intersects(wallArray[i].rect.getGlobalBounds()))
			{
				flashbang.explode();
				flashbang.timeAmount = time;
				flashbang.active = false;
			}
		}
	}
}

std::vector<Projectile> Game::getEnyProVector() const
{
	return this->enemyProjectileArr;
}


std::vector<Projectile> Game::getProVector() const
{
	return this->projectileArray;
}

std::vector<Enemy> Game::getEnyVector() const
{
	return this->enemyArray;
}

int Game::getEnyAmount() const
{
	return this->enemyAmount;
}


void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
	target.draw(windowBGSprite);
	target.draw(mPlayer);
	for (size_t i = 0; i < this->wallAmount; i++)
	{
		target.draw(wallArray[i].rect);
	}
	for (size_t i = 0; i < this->enemyAmount; i++)
	{
		target.draw(enemyArray[i]);
	}
	target.draw(flashbang);
}



void Game::loadTextures()
{
	if (!this->windowBackground.loadFromFile("backgound.jpg"))
	{
		std::cout << "Background.jpg Is missing" << std::endl;
	}
	this->windowBGSprite.setTexture(windowBackground);
}

void Game::wallMap(int &wallAmount, Wall &wall, std::vector<Wall> &wallArray)
{
	wall.rect.setPosition(50 * 1, 50 * 8);
	wall.rect.setSize(sf::Vector2f(50 * 8, 50 * 1));
	wallArray.push_back(wall);
	wall.rect.setPosition(50 * 11, 50 * 8);
	wall.rect.setSize(sf::Vector2f(50 * 8, 50 * 1));
	wallArray.push_back(wall);
	wall.rect.setPosition(300, 150);
	wallArray.push_back(wall);
	wallAmount = 3;
}

void Game::enemyMap(int& enemyAmount, Enemy& objEnemy, std::vector<Enemy>& enemyArray)
{
	objEnemy.circ.setPosition(200, 200);
	enemyArray.push_back(objEnemy);
	objEnemy.circ.setPosition(300, 300);
	enemyArray.push_back(objEnemy);
	objEnemy.circ.setPosition(100, 100);
	
	enemyArray.push_back(objEnemy);
	objEnemy.rect.setPosition(100, 100);
	enemyAmount = 3;
}
