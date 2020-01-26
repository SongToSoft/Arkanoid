#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <vector>
#include "GameObject.h"

class HealthBar
{
public:
	HealthBar();
	~HealthBar();

	void TakeHeart();
	void Recovery();
	void Draw(sf::RenderWindow& window);

private:
	std::vector<GameObject> m_hearth;
	int m_visible;
};