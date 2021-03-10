#pragma once

enum FacingDirection
{
	DIR_LEFT,
	DIR_RIGHT
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
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	static const Vector2D Zero()
	{
		return Vector2D(0, 0);
	}
};

inline Vector2D operator +(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x + b.x, a.y + b.y);
}

inline Vector2D operator *(const Vector2D& a, float b)
{
	return Vector2D(a.x * b, a.y * b);
}

struct Anchor
{
	int min, max;

	Anchor()
	{
		
	}
	
	Anchor(int min, int max)
	{
		this->min = min;
		this->max = max;
	};

	Anchor& operator += (const Anchor& a)
	{
		min += a.min;
		max += a.max;
	}

	Anchor& operator -= (const Anchor& a)
	{
		min -= a.min;
		max -= a.max;
	}
};

inline Anchor operator +(const Anchor& a, const Anchor& b)
{
	return Anchor(a.min + b.min, a.max + b.max);
}

inline Anchor operator -(const Anchor& a, const Anchor& b)
{
	return Anchor(a.min - b.min, a.max - b.max);
}

struct Rect2D
{
	float x, y, width, height;

	Rect2D()
	{
		x = 0.f;
		y = 0.f;
		width = 0.f;
		height = 0.f;
	}
	
	Rect2D(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};