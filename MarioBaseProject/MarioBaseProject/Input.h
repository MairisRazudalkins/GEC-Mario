#pragma once
#include <iostream>
#include <SDL.h>

class Vector2D;

class Input
{
	Input() {};
	static Input* inst;
	SDL_MouseButtonEvent* mouseEvent;
	SDL_KeyboardEvent previousKeyboardEvent;
	SDL_KeyboardEvent* keyboardEvent;
	
public:
	~Input() { inst = nullptr; }
	void UpdateMouseState(SDL_MouseButtonEvent* event) { mouseEvent = event; }
	void UpdateKeyboardState(SDL_KeyboardEvent* event);

	static Input* GetInst() { return inst != nullptr ? inst : inst = new Input(); }
	
	static bool IsKeyHeld(SDL_Scancode scancode) { return SDL_GetKeyboardState(NULL)[scancode]; }
	static bool IsKeyDown(SDL_Scancode scancode) { return GetInst()->keyboardEvent != nullptr ? GetInst()->keyboardEvent->keysym.scancode == scancode : false; }
	static bool WasKeyDown(SDL_Scancode scancode);
	
	//bit of a stretch doing it this way bit it works so whatever
	static bool IsLeftMouseDown() { return GetInst()->mouseEvent != nullptr ? GetInst()->mouseEvent->button == SDL_BUTTON_LEFT && GetInst()->mouseEvent->state == SDL_PRESSED : false; }
	static bool IsRightMouseDown() { return GetInst()->mouseEvent != nullptr ? GetInst()->mouseEvent->button == SDL_BUTTON_RIGHT && GetInst()->mouseEvent->state == SDL_PRESSED : false; }
	static bool IsLeftMouseHeld() { return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT; }

	static Vector2D GetMousePos();
};