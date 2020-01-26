#include "Block.h"

Block::Block(const std::string& textureName, sf::Vector2f position, int lives)
	:
	GameObject(textureName, position),
	m_lives(lives)
{
	m_score = m_lives * 50;
}

Block::~Block()
{
}

bool Block::TakeLife()
{
	--m_lives;
	return (m_lives == 0) ? true : false;
}

int Block::GetScore()
{
	return m_score;
}
