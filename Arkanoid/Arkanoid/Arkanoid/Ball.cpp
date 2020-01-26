#include "Ball.h"
#include "Game.h"

Ball::Ball(const std::string& textureName, sf::Vector2f position)
	:
	GameObject(textureName, position)
{
}

Ball::~Ball()
{
}

void Ball::CheckPaddle(Paddle& paddle)
{
	if (m_state == EBallState::STARTED)
	{
		if (m_sprite.getGlobalBounds().intersects(paddle.GetSprite().getGlobalBounds()))
		{
			m_direction.y = -1;
			if (m_sprite.getGlobalBounds().intersects(paddle.GetLeftRect()) ||
				m_sprite.getGlobalBounds().intersects(paddle.GetRigthRect()))
			{
				m_direction.x *= (-1);
			}
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_state = EBallState::STARTED;
		}
		m_position.x = paddle.GetPosition().x + paddle.GetSprite().getGlobalBounds().width / 2 - m_sprite.getGlobalBounds().width / 2;
		m_position.y = paddle.GetPosition().y - paddle.GetSprite().getGlobalBounds().height ;
	}
}

bool Ball::CheckBlock(Block& block)
{
	if (m_sprite.getGlobalBounds().intersects(block.GetSprite().getGlobalBounds()))
	{
		m_direction.y *= (-1);
		if (m_sprite.getGlobalBounds().intersects(block.GetLeftRect()) ||
			m_sprite.getGlobalBounds().intersects(block.GetRigthRect()))
		{
			m_direction.x *= (-1);
		}
		return block.TakeLife();
	}
	return false;
}

void Ball::Update(const float time)
{
	if (m_state == EBallState::STARTED)
	{
		// if ((m_position.x >= 410.0f) || (m_position.x <= 26.0f)) is not good for this
		if (m_position.x >= 410.0f)
		{
			m_direction.x = -1;
		}
		else
		{
			if (m_position.x <= 26.0f)
			{
				m_direction.x = 1;
			}
			else
			{
				if (m_position.y <= 30.0f)
				{
					m_direction.y *= (-1);
				}
				else
				{
					if (m_position.y >= 535.0f)
					{
						Game::TakeLife();
						m_direction.y = -1;
						m_state = EBallState::ON_START;
					}
				}
			}
		}
		m_position.x += (m_speed * m_direction.x) * time;
		m_position.y += (m_speed * m_direction.y) * time;
	}
}
