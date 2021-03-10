#pragma once

enum FacingDirection
{
	DIR_RIGHT,
	DIR_LEFT
};

enum ScreenType
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

struct Vector2D
{
	float x, y;

	Vector2D() { x = 0.f; y = 0.f; }
	Vector2D(float x, float y) { this->x = x; this->y = y; }

	const Vector2D operator+ (const Vector2D& other) const { Vector2D temp(*this); temp += other; return temp; }
	Vector2D& operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }

	const Vector2D operator* (const float other) const { Vector2D temp(*this); temp.x *= other; temp.y *= other; return temp; }
	const Vector2D operator/ (const float other) const { Vector2D temp(*this); temp.x /= other; temp.y /= other; return temp; }
	const Vector2D operator- (const float other) const { Vector2D temp(*this); temp.x -= other; temp.y -= other; return temp; }
};

struct Rect2D
{
	float x, y;
	int width, height;
	
	Rect2D() { x = 0.f; y = 0.f; width = 0; height = 0; }
	Rect2D(float x, float y, int width, int height) { this->x = x; this->y = y; this->width = width; this->height = height; }
};
