#include "Background.h"

Background::Background(const std::string& textureName, sf::Vector2f position)
	:
	GameObject(textureName, position)
{
}

Background::~Background()
{
}

void Background::SetRectangle()
{
	m_sprite.setTextureRect(sf::IntRect(10, 10, 1000, 700));
}