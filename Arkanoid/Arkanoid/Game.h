#pragma once

#include "SFML/Graphics.hpp"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "HealthBar.h"
#include "Background.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BLOCK_IN_ROW 15
#define BLOCK_IN_COLUMN 8

#define DEFAULT_LIVES_NUMBER 5

enum class EGameState
{
	MENU,
	MAIN_GAME,
	GAME_OVER
};

class Game
{
public:
	Game();
	~Game();
	void Start();

	static void TakeLife();
	static int GetLives();
	static void ChangeState(EGameState);

private:
	static void ReadHighScore();
	static void SetHighScore();

	void CreateLevel();

	void UpdateMenu(sf::Event& event);
	void DrawMenu();

	void UpdateMainGame(sf::Event& event, float time);
	void DrawMainGame();

	void UpdateGameOver(sf::Event& event);
	void DrawGameOver();

private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	Background m_background;
	Paddle m_paddle;
	Ball m_ball;
	std::vector<Block> m_blocks;

	int m_currentLevel = 1;

	sf::Text m_currentScoreText;
	sf::Text m_gameoverText;

	static sf::Text m_menuText;
	static sf::Text m_highScoreText;
	static int m_highScore;
	static int m_currentScore;
	static HealthBar m_healthBar;
	static int m_lives;
	static EGameState m_state;
};