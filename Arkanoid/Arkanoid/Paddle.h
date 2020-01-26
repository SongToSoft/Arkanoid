#pragma once

#include "GameObject.h"

class Paddle : public GameObject
{
public:
	Paddle(const std::string& textureName, sf::Vector2f position);
	~Paddle();

	void Update(sf::Event& event, float time);

private:
	float m_speed = 2.0f;
};