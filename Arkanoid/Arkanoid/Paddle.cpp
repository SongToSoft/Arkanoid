#include "Paddle.h"

Paddle::Paddle(const std::string& textureName, sf::Vector2f position)
	:
	GameObject(textureName, position)
{
}

Paddle::~Paddle()
{

}

void Paddle::Update(sf::Event& event, float time)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) &&
		(m_position.x + m_sprite.getGlobalBounds().width < 410.0f))
	{
		m_position.x += m_speed * time;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (m_position.x > 26.0f))
	{
		m_position.x -= m_speed * time;
	}
}
