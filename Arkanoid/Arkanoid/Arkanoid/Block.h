#pragma once

#include "GameObject.h"
#include <string>
#include "SFML/Graphics.hpp"

class Block : public GameObject
{
public:
	Block(const std::string& textureName, sf::Vector2f position, int lives);
	~Block();

	bool TakeLife();
	int GetScore();

private:
	int m_lives;
	int m_score;
};