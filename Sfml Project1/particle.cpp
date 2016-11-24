#include "particle.h"


ParticleSystem::ParticleSystem(unsigned int count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(sf::seconds(3)),
	m_emitter(0, 0)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::execute(Player& player)
{
	
	for (std::size_t i = 0; i < this->m_particles.size(); ++i)
	{
			Particle& p = m_particles[i];

			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i, player);

	}
	
}


void ParticleSystem::update(sf::Time elapsed, Player &player)
{
	for (std::size_t i = 0; i < this->m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

	/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i, player);
		}*/
			if (p.lifetime <= sf::Time::Zero)
			{
				m_vertices[i].color = sf::Color::Transparent;
			}
		if (p.lifetime.asSeconds() <= m_lifetime.asSeconds()/2)
		{
			float speed = (std::rand() % 5) + 5.f;
			m_particles[i].velocity = sf::Vector2f(std::cos(this->angle) * speed, std::sin(this->angle) * speed);
		}

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();


		//Sets the color of the particle
		if (p.lifetime >= sf::Time::Zero)
		{
			m_vertices[i].color = sf::Color::Red;
		}
		
	}
}


	//virtual void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	

void ParticleSystem::resetParticle(std::size_t index, Player &player)
{
		// give a random velocity and lifetime to the particle
	this->angle = (std::rand() % 30 + player.rotation+165) * 3.14f / 180.f;
	float speed = (std::rand() % 50) + 50.f;
	m_particles[index].velocity = sf::Vector2f(std::cos(this->angle) * speed, std::sin(this->angle) * speed);
	//m_particles[index].velocity = sf::Vector2f(std::cos(angle), std::sin(angle));
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + 1110);
		
	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter;
}
