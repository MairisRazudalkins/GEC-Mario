#include "Input.h"
#include "Commons.h"

Input* Input::inst = nullptr;

void Input::UpdateKeyboardState(SDL_KeyboardEvent* event)
{
	if (keyboardEvent != nullptr)
		previousKeyboardEvent = *keyboardEvent;
	
	keyboardEvent = event;
}

bool Input::WasKeyDown(SDL_Scancode scancode)
{
	if (GetInst()->keyboardEvent != nullptr)
	{
		bool wasPreviouslyPressed = GetInst()->previousKeyboardEvent.keysym.scancode == scancode && GetInst()->previousKeyboardEvent.state == SDL_PRESSED;
		bool wasCurrentlyPressed = GetInst()->keyboardEvent != nullptr ? GetInst()->keyboardEvent->keysym.scancode == scancode : false;
	
		return !wasPreviouslyPressed && wasCurrentlyPressed;
	}
	
	return false;
}

Vector2D Input::GetMousePos()
{
	int mousePosX, mousePosY;
	SDL_GetMouseState(&mousePosX, &mousePosY);
	return Vector2D(mousePosX, mousePosY);
}
