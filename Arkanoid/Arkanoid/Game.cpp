#include "Game.h"
#include <fstream>

int Game::m_lives = DEFAULT_LIVES_NUMBER;
EGameState Game::m_state = EGameState::MENU;
HealthBar Game::m_healthBar;
sf::Text Game::m_highScoreText;
sf::Text Game::m_menuText;
int Game::m_highScore = 0;
int Game::m_currentScore = 0;

Game::Game()
	:
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid"),
	m_paddle("Textures\\VausSpacecraftLarge.png", sf::Vector2f(200, 500)),
	m_ball("Textures\\EnergyBall.png", sf::Vector2f(0, 0)),
	m_background("Textures\\Field.png", sf::Vector2f(10, 10))
{
	ReadHighScore();
}

Game::~Game()
{
}

void Game::Start()
{
	sf::Font font;
	if (!font.loadFromFile("Fonts\\Aire Exterior.ttf"))
	{
		std::cout << "Font don't found" << std::endl;
	}
	m_highScoreText.setFont(font);
	m_highScoreText.setString("High Score: " + std::to_string(m_highScore));
	m_highScoreText.setCharacterSize(20);
	m_highScoreText.setPosition(450, 50);

	m_currentScoreText.setFont(font);
	m_currentScoreText.setString("Current Score: " + std::to_string(m_currentScore));
	m_currentScoreText.setCharacterSize(20);
	m_currentScoreText.setPosition(450, 100);


	m_menuText.setFont(font);
	m_menuText.setString("  Current High Score: " + std::to_string(m_highScore) + '\n' + '\n' + "Press Enter for Start Game");
	m_menuText.setCharacterSize(30);
	m_menuText.setPosition(250, 200);

	m_gameoverText.setFont(font);
	m_gameoverText.setString("GAME OVER");
	m_gameoverText.setCharacterSize(30);
	m_gameoverText.setPosition(325, 250);

	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_state == EGameState::MENU)
		{
			UpdateMenu(event);
			DrawMenu();
		}
		while (m_state == EGameState::MAIN_GAME)
		{
			float time = m_clock.getElapsedTime().asMicroseconds();
			time /= 3000;
			m_clock.restart();
			UpdateMainGame(event, time);
			DrawMainGame();
		}
		while (m_state == EGameState::GAME_OVER)
		{
			UpdateGameOver(event);
			DrawGameOver();
		}
	}
}

void Game::TakeLife()
{
	--m_lives;
	m_healthBar.TakeHeart();
	if (m_lives == 0)
	{
		m_state = EGameState::GAME_OVER;
	}
}

int Game::GetLives()
{
	return m_lives;
}

void Game::ChangeState(EGameState state)
{
	m_state = state;
}

void Game::ReadHighScore()
{
	std::ifstream file("HighScore.txt", std::ifstream::in);
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		m_highScore = atoi(line.c_str());
		file.close();
	}
}

void Game::SetHighScore()
{
	if (m_currentScore > m_highScore)
	{
		m_highScore = m_currentScore;
		std::ofstream file("HighScore.txt", std::ofstream::out);
		if (file.is_open())
		{
			file.clear();
			file << m_currentScore;
			file.close();
		}
	}
}

void Game::CreateLevel()
{
	m_blocks.clear();
	for (int i = 0; i < BLOCK_IN_COLUMN; ++i)
	{
		int blockLives = (m_currentLevel + i) % 4;
		std::string textureName;
		switch (blockLives)
		{
		case 1:
			textureName = "Textures\\BlueWall.png";
			break;
		case 2:
			textureName = "Textures\\RedWall.png";
			break;
		case 3:
			textureName = "Textures\\GoldWall.png";
			break;
		default:
			blockLives = 1;
			textureName = "Textures\\BlueWall.png";
		}
		for (int j = 0; j < BLOCK_IN_ROW; ++j)
		{
			m_blocks.push_back(Block(textureName, sf::Vector2f(36 + 25 * j, 50 + 25 * i), blockLives));
		}
	}
}

void Game::UpdateMenu(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_lives = DEFAULT_LIVES_NUMBER;
		m_state = EGameState::MAIN_GAME;
		m_currentScore = 0;
		m_currentScoreText.setString("Current Score: " + std::to_string(m_currentScore));
		m_highScoreText.setString("High Score: " + std::to_string(m_highScore));
		m_healthBar.Recovery();
		CreateLevel();
	}
}

void Game::DrawMenu()
{
	m_window.clear(sf::Color::Black);

	m_background.DrawOnlySpace(m_window);
	m_window.draw(m_menuText);
	
	m_window.display();
}


void Game::UpdateMainGame(sf::Event &event, float time)
{
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
	
	m_paddle.Update(event, time);

	m_ball.CheckPaddle(m_paddle);
	for (int i = 0; i < m_blocks.size(); ++i)
	{
		if (m_ball.CheckBlock(m_blocks[i]))
		{
			m_currentScore += m_blocks[i].GetScore();
			m_blocks.erase(m_blocks.begin() + i);
			m_currentScoreText.setString("Current Score: " + std::to_string(m_currentScore));
			if (m_blocks.size() == 0)
			{
				++m_currentLevel;
				if (m_currentLevel == 4)
				{
					m_state = EGameState::GAME_OVER;
				}
				else
				{
					m_ball.SetState(EBallState::ON_START);
					CreateLevel();
				}
			}
		}
	}
	m_ball.Update(time);
}

void Game::DrawMainGame()
{
	m_window.clear(sf::Color::Black);

	m_background.Draw(m_window);

	m_paddle.Draw(m_window);
	m_ball.Draw(m_window);

	for (Block& block : m_blocks)
	{
		block.Draw(m_window);
	}

	m_healthBar.Draw(m_window);

	m_window.draw(m_highScoreText);
	m_window.draw(m_currentScoreText);

	m_window.display();
}

void Game::UpdateGameOver(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		SetHighScore();
		m_menuText.setString("  Current High Score: " + std::to_string(m_highScore) + '\n' + "Press Enter for Start Game");
		m_state = EGameState::MENU;
	}
}

void Game::DrawGameOver()
{
	m_window.clear(sf::Color::Black);

	m_background.DrawOnlySpace(m_window);
	m_window.draw(m_gameoverText);

	m_window.display();
}
