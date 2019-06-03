#pragma once
#include "Renderer2D.h"

class SimonSquare
{
public:
	SimonSquare(float x, float y, float width, float height);
	~SimonSquare();

	bool ButtonUpdate(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	void SetColor(aie::Renderer2D* renderer, float red, float green, float blue, float alpha);
private:
	float m_posX;
	float m_posY;

	float height;
	float width;
};

