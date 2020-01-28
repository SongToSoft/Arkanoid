#include "Background.h"

Background::Background(const std::string& textureName, sf::Vector2f position)
	:
	GameObject(textureName, position)
{
	if (!m_spaceTexture.loadFromFile("Textures\\Space.png"))
	{
		std::cout << "Texture don't found in path: Textures\\Space.png" << std::endl;
	}
}

Background::~Background()
{
}

void Background::Draw(sf::RenderWindow& window)
{
	m_spaseSprite = sf::Sprite(m_spaceTexture);
	window.draw(m_spaseSprite);
	GameObject::Draw(window);
}

void Background::DrawOnlySpace(sf::RenderWindow& window)
{
	m_spaseSprite = sf::Sprite(m_spaceTexture);
	window.draw(m_spaseSprite);
}