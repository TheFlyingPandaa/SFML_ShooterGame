#include "GameLogi.h"
#include <iostream>

Game::Game()
{
	loadTextures();
	wallMap(this->wallAmount, this->wall, this->wallArray);
	enemyMap(this->enemyAmount, this->objEnemy, this->enemyArray);
	glasMap();
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
	mPlayer.update(window, this->wallArray, this->wallAmount, this->glasArray, this->glasAmount);
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
		if (enemyArray[i].getEnyDead() == false)
		{
			if (enemyArray[i].getDistanceToPlayer() < 150)
			{
				if (enemyArray[i].getBlinded() == false)
				{
					if (enemyArray[i].getEnyTest() != true)
					{
						enemyArray[i].enemyShoot(sf::Vector2f(mPlayer.circ.getPosition()));
						eProjectile.rect.setPosition(enemyArray[i].circ.getPosition());
						eProjectile.direction = enemyArray[i].getRotation();
						enemyProjectileArr.push_back(eProjectile);
						enemyArray[i].setEnyTest(true);

						enemyArray[i].setEnyTime((time + sf::seconds(0.4)));
					}
				}
			}
		}
	}
	if (time >= timeTest)
	{
		testt = false;
	}
	for (size_t i = 0; i < this->enemyAmount; i++) {
		if (time >= enemyArray[i].getEnyTime())
		{
			enemyArray[i].setEnyTest(false);
		}
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
		if (enemyArray[i].getEnyDead() == false)
		{
			enemyArray[i].update(mPlayer.circ.getPosition());
			if (flashbang.bangs == true)
			{
				if (enemyArray[i].circ.getGlobalBounds().intersects(flashbang.circ.getGlobalBounds()))
				{
					enemyArray[i].setBlinded(true);
				}
			}
			if (flashbang.bangs == false)
			{
				enemyArray[i].setBlinded(false);
			}
		}
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
		for (size_t t = 0; t < this->glasAmount; t++)
		{
			if (glasArray[t].getShatterd() == false)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(glasArray[t].rect.getGlobalBounds()))
				{
					projectileArray[counter].destory = true;
					glasArray[t].setShatterd(true);
					glasArray[t].glasShatter();
				}
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

	counter = 0;
	for (enyProIter = enemyProjectileArr.begin(); enyProIter != enemyProjectileArr.end(); enyProIter++)
	{
		for (size_t i = 0; i < this->wallAmount; i++) {
			if (enemyProjectileArr[counter].rect.getGlobalBounds().intersects(wallArray[i].rect.getGlobalBounds()));
			{
			//	enemyProjectileArr[counter].destory = true;
			}
		}
		if (enemyProjectileArr[counter].rect.getPosition().x < 0)
		{
			enemyProjectileArr[counter].destory = true;
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
	for (size_t i = 0; i < this->glasAmount; i++)
	{
		target.draw(glasArray[i]);
	}
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
	wall.rect.setPosition(0, 50*0.5);
	wall.rect.setSize(sf::Vector2f(50 * 19, 50 * 1));
	wallArray.push_back(wall);

	wall.rect.setPosition(50 * 18.5, 50 * 0);
	wall.rect.setSize(sf::Vector2f(50 * 1, 50 * 17));
	wallArray.push_back(wall);

	wall.rect.setPosition(50*0.5, 50*1);
	wall.rect.setSize(sf::Vector2f(50 * 1, 50 * 17));
	wallArray.push_back(wall);

	wall.rect.setPosition(50 * 0, 50 * 16.5);
	wall.rect.setSize(sf::Vector2f(50 * 19, 50 * 1));
	wallArray.push_back(wall);

	wall.rect.setPosition(50 * 1, 50 * 4);
	wall.rect.setSize(sf::Vector2f(50 * 6, 50 * 1));
	wallArray.push_back(wall);

	wall.rect.setPosition(50 * 1, 50 * 10);
	wall.rect.setSize(sf::Vector2f(50 * 6, 50 * 1));
	wallArray.push_back(wall);

	wallAmount = 6;
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

void Game::glasMap()
{
	glas.rect.setPosition(50 * 5.5, 50 * 5.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 6.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 7.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 8.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);
	glasAmount = 4;
}

