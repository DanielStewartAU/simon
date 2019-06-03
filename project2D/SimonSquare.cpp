#include "SimonSquare.h"
#include "Input.h"


SimonSquare::SimonSquare(float x, float y, float newWidth, float newHeight)
{
	m_posX = x;
	m_posY = y;
	width = newWidth;
	height = newHeight;
}

bool SimonSquare::ButtonUpdate(float deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	int mouseX = input->GetMouseX();
	int mouseY = input->GetMouseY();	

	float left = m_posX - (width * 0.5f);
	float right = m_posX + (width * 0.5f);
	float bottom = m_posY - (height * 0.5f);
	float top = m_posY + (height * 0.5f);

	if (mouseX > left && mouseX < right && mouseY > bottom && mouseY < top)
	{
		return input->WasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT);
	}

	return false;
}

SimonSquare::~SimonSquare()
{
}

void SimonSquare::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawSprite(nullptr, m_posX, m_posY, width, height, 0, 0, 0.5, 0.5);
}

void SimonSquare::SetColor(aie::Renderer2D* renderer, float red, float green, float blue, float alpha)
{
	renderer->SetRenderColour(red, green, blue, alpha);
}