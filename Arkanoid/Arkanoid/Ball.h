#pragma once

#include "GameObject.h"
#include "Paddle.h"
#include "Block.h"

enum class EBallState
{
	ON_START,
	STARTED
};

class Ball : public GameObject
{
public:
	Ball(const std::string& textureName, sf::Vector2f position);
	~Ball();

	void SetState(EBallState state);

	void CheckPaddle(Paddle& paddle);
	bool CheckBlock(Block& block);

	void Update(const float time);

private:
	float m_speed = 1.0f;
	sf::Vector2<int> m_direction = sf::Vector2<int>(-1, -1);
	EBallState m_state = EBallState::ON_START;
};