#include "Game2D.h"
#include "SimonSquare.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include <time.h> 
#include <iostream>



Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	srand(time(NULL));

	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_texture = new aie::Texture("./textures/hero.png");
	m_texture2 = new aie::Texture("./textures/rock_large.png");
	m_font = new aie::Font("./font/consolas.ttf", 40);
	aie::Application* application = aie::Application::GetInstance();
	unsigned int windowWidth = application->GetWindowWidth();
	unsigned int windowHeight = application->GetWindowHeight();

	simonSquare[0] = new SimonSquare((float)windowWidth / 2 - 125, (float)windowHeight / 2 - 125, 250.0f, 250.0f);
	simonSquare[1] = new SimonSquare((float)windowWidth / 2 + 125, (float)windowHeight / 2 - 125, 250.0f, 250.0f);
	simonSquare[2] = new SimonSquare((float)windowWidth / 2 - 125, (float)windowHeight / 2 + 125, 250.0f, 250.0f);
	simonSquare[3] = new SimonSquare((float)windowWidth / 2 + 125, (float)windowHeight / 2 + 125, 250.0f, 250.0f);

	//fill array of enums with sequence
	for (int i = 0; i < 256; i++)
	{
		sequence[i] = (Colours)(rand() % 4);
	}

	//set that int to zero
	sequenceNumber = 0;

	gameOver = false;

	score = 0;
	//initialise timer to zero
	timer = 0.0f;
}

Game2D::~Game2D()
{

	// Deleted the textures.
	delete m_font;
	delete m_texture;
	delete m_texture2;

	// Delete the renderer.
	delete m_2dRenderer;

	for (int i = 0; i < 4; i++)
	{
		delete simonSquare[i];
	}
}

void Game2D::Update(float deltaTime)
{
	// Update the player.
	m_Player->Update(deltaTime);

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();
	

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	//increase timer by deltatime
	timer += deltaTime;

	if (sequence[sequenceNumber] == BLUE)
	{
		if (simonSquare[0]->ButtonUpdate(deltaTime))
		{
			score++;
			sequenceNumber++;
			//set timer back to zero
			timer = 0.0f;
		}
		else if ((simonSquare[1]->ButtonUpdate(deltaTime)) || (simonSquare[2]->ButtonUpdate(deltaTime)) || (simonSquare[3]->ButtonUpdate(deltaTime)))
		{
		
			aie::Application* application = aie::Application::GetInstance();
			application->Quit();
		}
	}


	else if (sequence[sequenceNumber] == YELLOW)
	{
		if (simonSquare[1]->ButtonUpdate(deltaTime))
		{
			score++;
			sequenceNumber++;
			timer = 0.0f;
		}
		else if ((simonSquare[0]->ButtonUpdate(deltaTime)) || (simonSquare[2]->ButtonUpdate(deltaTime)) || (simonSquare[3]->ButtonUpdate(deltaTime)))
		{
			aie::Application* application = aie::Application::GetInstance();
			application->Quit();
		}
	}

	else if (sequence[sequenceNumber] == RED)
	{
		if (simonSquare[2]->ButtonUpdate(deltaTime))
		{
			score++;
			sequenceNumber++;
			timer = 0.0f;
		}
		else if ((simonSquare[0]->ButtonUpdate(deltaTime)) || (simonSquare[1]->ButtonUpdate(deltaTime)) || (simonSquare[3]->ButtonUpdate(deltaTime)))
		{
			aie::Application* application = aie::Application::GetInstance();
			application->Quit();
		}
	}

	else if (sequence[sequenceNumber] == GREEN)
	{
		if (simonSquare[3]->ButtonUpdate(deltaTime))
		{
			score++;
			sequenceNumber++;
			timer = 0.0f;
		}
		else if ((simonSquare[0]->ButtonUpdate(deltaTime)) || (simonSquare[1]->ButtonUpdate(deltaTime)) || (simonSquare[2]->ButtonUpdate(deltaTime)))
		{
			aie::Application* application = aie::Application::GetInstance();
			application->Quit();
		}
	}	
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	if(sequence[sequenceNumber] == BLUE && timer <= 1.5f)
		simonSquare[0]->SetColor(m_2dRenderer, 0, 0, 1, 1);
	else
		simonSquare[0]->SetColor(m_2dRenderer, 0, 0, 1, 0.2f);
	simonSquare[0]->Draw(m_2dRenderer);

	if (sequence[sequenceNumber] == YELLOW && timer <= 1.5f)
		simonSquare[1]->SetColor(m_2dRenderer, 1, 1, 0, 1);
	else
		simonSquare[1]->SetColor(m_2dRenderer, 1, 1, 0, 0.2f);
	simonSquare[1]->Draw(m_2dRenderer);
	
	if (sequence[sequenceNumber] == RED && timer <= 1.5f)
		simonSquare[2]->SetColor(m_2dRenderer, 1, 0, 0, 1);
	else
		simonSquare[2]->SetColor(m_2dRenderer, 1, 0, 0, 0.2f);
	simonSquare[2]->Draw(m_2dRenderer);
	
	if (sequence[sequenceNumber] == GREEN && timer <= 1.5f)
		simonSquare[3]->SetColor(m_2dRenderer, 0, 1, 0, 1);
	else
		simonSquare[3]->SetColor(m_2dRenderer, 0, 1, 0, 0.2f);
	simonSquare[3]->Draw(m_2dRenderer);

	m_2dRenderer->SetRenderColour(1, 1, 1, 1);

	char scoreArray[256];
	sprintf(scoreArray, "Score: %i", score);
	//m_2dRenderer->DrawText2D(m_font, scoreArray, 100, 100, 1);
	m_2dRenderer->DrawText2D(m_font, scoreArray, application->GetWindowWidth() - 200, application->GetWindowHeight() - 50, 1);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}