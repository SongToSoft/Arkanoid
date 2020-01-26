#include "HealthBar.h"
#include "Game.h"

HealthBar::HealthBar()
{
	for (int i = 0; i < Game::GetLives(); ++i)
	{
		m_hearth.push_back(GameObject("C:\\Users\\Dima\\source\\repos\\Arkanoid\\Arkanoid\\Textures\\Heart.png", sf::Vector2f(50 + 35 * i, 550)));
	}
	m_visible = m_hearth.size();
}

HealthBar::~HealthBar()
{
}

void HealthBar::Recovery()
{
	m_visible = m_hearth.size();
}

void HealthBar::TakeHeart()
{
	--m_visible;
}

void HealthBar::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_visible; ++i)
	{
		m_hearth[i].Draw(window);
	}
}
