#include "GameLogi.h"
#include <iostream>

Game::Game()
{
	loadingFont();
	loadTextures();
	wallMap(this->wallAmount, this->wall, this->wallArray);
	enemyMap(this->enemyAmount, this->objEnemy, this->enemyArray);
	nodeArray = new std::vector<Node>[this->amountOfEnemyNodes];
	glasMap();
	nodeMap();
	enemyNodeCatcher();
	doorMap();

	rescueZone.rect.setSize(sf::Vector2f(100, 100));
	rescueZone.rect.setFillColor(sf::Color(0, 255, 0, 120));
	rescueZone.rect.setPosition(800, 700);

	mPlayer.circ.setPosition(sf::Vector2f(100, 600));

}

Game::~Game()
{
	
	delete[] nodeArray;
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
				mProjectile.headShoot = false;
				mProjectile.rect.setFillColor(sf::Color::Green);
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
				enemyArray[i].setPassiveNode(false);
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


	if (mPlayer.circ.getGlobalBounds().intersects(hostage.circ.getGlobalBounds()))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			hostageTagAlong = true;
		}
	}
	if (hostageTagAlong == true)
	{
		hostage.circ.setPosition(mPlayer.circ.getPosition().x - 10, mPlayer.circ.getPosition().y+10);
		if (mPlayer.circ.getGlobalBounds().intersects(rescueZone.rect.getGlobalBounds()))
		{
			winningZone = true;
		}
	}
	
	sgetAmmo = std::to_string(mPlayer.getAmmo());
	sgetAmmoCap = std::to_string(mPlayer.getAmmoCap());
	text.setString(sgetAmmo + "/" + sgetAmmoCap);
	hpText.setString("HP:" + std::to_string(mPlayer.getHp()));

	doorChecker();
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
		if (projectileArray[counter].rect.getGlobalBounds().intersects(hostage.circ.getGlobalBounds()))
		{
			hostage.takeDamage(20);
			projectileArray[counter].destory = true;
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

	//PROJECTILE ARRAY FOR THE ENEMY STARTS HERE

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
	std::cout << enemyProjectileArr.size() << std::endl;
	counter = 0;
	for (enyProIter = enemyProjectileArr.begin(); enyProIter != enemyProjectileArr.end(); enyProIter++)
	{
		
		if (mPlayer.circ.getGlobalBounds().intersects(enemyProjectileArr[counter].rect.getGlobalBounds()))
			{
				enemyProjectileArr[counter].destory = true;
				mPlayer.damagePlayer(20);
			}
		for (size_t i = 0; i < this->wallAmount; i++) {
			if (enemyProjectileArr[counter].rect.getGlobalBounds().intersects(wallArray[i].rect.getGlobalBounds()))
			{
				enemyProjectileArr[counter].destory = true;
			}
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
	if (winningZone == false)
	{
		target.draw(windowBGSprite);
		target.draw(door);
		for (size_t i = 0; i < this->glasAmount; i++)
		{
			target.draw(glasArray[i]);
		}
		if (hostageTagAlong == true)
		{
			target.draw(rescueZone);
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
		target.draw(hostage);
		for (size_t t = 0; t < this->amountOfEnemyNodes; t++) {
			for (size_t i = 0; i < 4; i++)
			{
				target.draw(nodeArray[t][i]);
			}
		}
		target.draw(flashbang);
		target.draw(text);
		target.draw(hpText);
	}
	
	
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
	objEnemy.circ.setPosition(75, 425);
	enemyArray.push_back(objEnemy);
	objEnemy.circ.setPosition(300, 100);
	enemyArray.push_back(objEnemy);
	objEnemy.circ.setPosition(400, 100);
	
	enemyArray.push_back(objEnemy);
	objEnemy.rect.setPosition(100, 100);
	enemyAmount = 3;
	amountOfEnemyNodes = enemyAmount;
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

	glas.rect.setPosition(50 * 5.5, 50 * 10.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 11.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 12.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);

	glas.rect.setPosition(50 * 5.5, 50 * 13.5);
	glas.rect.setSize(sf::Vector2f(50 * 0.5, 50 * 1));
	glasArray.push_back(glas);
	glasAmount = 8;
}

void Game::nodeMap()
{
	node.rect.setPosition(50 * 1.5, 50 * 8.5);
	nodeArray[0].push_back(node);
	node.rect.setPosition(50 * 1.5, 50 * 4.5);
	nodeArray[0].push_back(node);
	node.rect.setPosition(50 * 4.5, 50 * 4.5);
	nodeArray[0].push_back(node);
	node.rect.setPosition(50 * 4.5, 50 * 8.5);
	nodeArray[0].push_back(node);

	node.rect.setPosition(50 * 1, 50 * 2.5);
	nodeArray[1].push_back(node);
	node.rect.setPosition(50 * 1, 50 * 1);
	nodeArray[1].push_back(node);
	node.rect.setPosition(50 * 4.5, 50 * 1);
	nodeArray[1].push_back(node);
	node.rect.setPosition(50 * 4.5, 50 * 2.5);
	nodeArray[1].push_back(node);

	node.rect.setPosition(50 * 8, 50 * 8.5);
	nodeArray[2].push_back(node);
	node.rect.setPosition(50 * 8, 50 * 1);
	nodeArray[2].push_back(node);
	node.rect.setPosition(50 * 13.5, 50 * 1);
	nodeArray[2].push_back(node);
	node.rect.setPosition(50 * 13.5, 50 * 8.5);
	nodeArray[2].push_back(node);
}

void Game::enemyNodeCatcher()
{
	enemyArray[0].nodeCatcher(nodeArray, 0);
	enemyArray[1].nodeCatcher(nodeArray, 1);
	enemyArray[2].nodeCatcher(nodeArray, 2);
}

void Game::doorMap()
{
	door.rect.setPosition(275, 225);
}
void Game::doorChecker()
{
	if (mPlayer.circ.getGlobalBounds().intersects(door.circ.getGlobalBounds()))
	{
		door.doorSlide();
		door.moving = true;
	}
	else
	{
		door.moving = false;
	}

	if (door.moved == true && door.moving == false)
	{
		door.doorSlideBack();
	}
}

void Game::loadingFont()
{
	if (!font.loadFromFile("Font//Hacked.ttf"))
	{
		std::cout << "CANT FIND FONT" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Black);
	text.setPosition(50, 767);

	hpText.setFont(font);
	hpText.setCharacterSize(32);
	hpText.setFillColor(sf::Color::Black);
	hpText.setPosition(130, 767);
}


