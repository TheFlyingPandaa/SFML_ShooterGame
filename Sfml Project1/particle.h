#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
#include "player.h"

//Yes this particle effect is originaly from the SFML documentation page
//So kinda copied? But it will be heavily edited. Will be removed if this counts as "plagiat"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	
	ParticleSystem(unsigned int count);

	void setEmitter(sf::Vector2f position);

	void update(sf::Time elapsed, Player &player);

	void execute(Player&player);
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		
		states.texture = NULL;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:
	float angle = 0;
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index, Player &player);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
};


#endif // !PARTICLE_H