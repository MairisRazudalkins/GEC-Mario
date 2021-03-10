#pragma once
#include <SDL.h>

class Vector2D;

class Input
{
	Input();
	
	static Input* inst;
	const Uint8* keyboardState;
	int mousePosX, mousePosY;
	
public:
	~Input();
	void Update();
	
	static Input* GetInst();
	static bool IsKeyDown(SDL_Scancode scancode);
	static Vector2D GetMousePos();
};