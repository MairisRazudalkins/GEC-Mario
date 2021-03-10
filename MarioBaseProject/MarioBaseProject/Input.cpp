#include "Input.h"
#include <SDL.h>
#include "Commons.h"

Input* Input::inst = nullptr;

Input::Input()
{
	
}

Input::~Input()
{
	
}

Input* Input::GetInst()
{
	return inst != nullptr ? inst : inst = new Input();
}

void Input::Update()
{
	keyboardState = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&mousePosX, &mousePosY);
}

bool Input::IsKeyDown(SDL_Scancode scancode)
{
	return GetInst()->keyboardState[scancode];
}

Vector2D Input::GetMousePos()
{
	return Vector2D(GetInst()->mousePosX, GetInst()->mousePosY);
}