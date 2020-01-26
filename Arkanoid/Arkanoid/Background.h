#pragma once

#include "GameObject.h"

class Background : public GameObject
{
public:
	Background(const std::string& textureName, sf::Vector2f position);
	~Background();

	void Draw(sf::RenderWindow& window) override;

private:
	sf::Texture m_spaceTexture;
	sf::Sprite m_spaseSprite;
};