#pragma once

class Character;
class Rect2D;
class Vector2D;

enum CollisionType
{
	NONE = 0,
	PLATFORM,
	BLOCK
};


class Collisions
{

public:
	static bool Circle(Vector2D pos1, Vector2D pos2, float radius1, float radius2);
	static bool Circle(Character* character1, Character* character2);
	static bool Box(Rect2D rect1, Rect2D rect2);
};