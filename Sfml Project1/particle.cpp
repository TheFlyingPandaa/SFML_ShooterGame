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

void ParticleSystem::update(sf::Time elapsed, Player &player)
{
	for (std::size_t i = 0; i < this->m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i, player);
		}
			if (p.lifetime <= sf::Time::Zero)
			{
				m_vertices[i].color = sf::Color::Transparent;
			}

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
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
		float angle = (std::rand() % 30 + player.rotation) * 3.14f / 180.f;
		float speed = (std::rand() % 20) + 20.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle+200) * speed, std::sin(angle+200) * speed);
		//m_particles[index].velocity = sf::Vector2f(std::cos(angle), std::sin(angle));
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1110);
		
		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}
