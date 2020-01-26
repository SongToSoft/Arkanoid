#include "GameObject.h"

#define SIDE_WIDTH 2

GameObject::GameObject(std::string textureName, sf::Vector2f position)
	:
	m_position(position)
{
	if (!m_texture.loadFromFile(textureName))
	{
		std::cout << "Texture don't found in path: " << textureName << std::endl;
	}
}

GameObject::~GameObject()
{
}

sf::Vector2f GameObject::GetPosition()
{
	return m_position;
}

void GameObject::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::FloatRect GameObject::GetRigthRect()
{
	return sf::FloatRect(m_position.x, m_position.y, SIDE_WIDTH, m_sprite.getGlobalBounds().height);
}

sf::FloatRect GameObject::GetLeftRect()
{
	return sf::FloatRect(m_position.x + m_sprite.getGlobalBounds().width, m_position.y, SIDE_WIDTH, m_sprite.getGlobalBounds().height);
}

sf::Sprite GameObject::GetSprite()
{
	return m_sprite;
}

void GameObject::Draw(sf::RenderWindow& window)
{
	m_sprite = sf::Sprite(m_texture);
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}
 