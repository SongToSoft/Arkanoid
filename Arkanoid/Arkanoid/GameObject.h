#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include <iostream>

class GameObject
{
public:
	GameObject(std::string textureName, sf::Vector2f position);
	~GameObject();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	sf::FloatRect GetRigthRect();
	sf::FloatRect GetLeftRect();
	sf::Sprite GetSprite();

	void Draw(sf::RenderWindow& window);

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};