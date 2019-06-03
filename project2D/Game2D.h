#pragma once

#include "Game.h"
#include "Renderer2D.h"

class Player;
class SimonSquare;

enum Colours
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
};

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D*	m_2dRenderer;

	// Example textures.
	aie::Texture*		m_texture;
	aie::Texture*		m_texture2;
	aie::Font*			m_font;

	// Player.
	Player* m_Player;

	// Simon Square
	SimonSquare* simonSquare[4];

	//add array of enum
	Colours sequence[256];
	//int to store which colour in the sequence they are up to
	int sequenceNumber;
	bool gameOver;

	int score;
	float timer;
};