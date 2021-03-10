#pragma once

class BaseCharacter;
class Rect2D;
class Vector2D;

class Collisions
{
	Collisions();

	static Collisions* instance;
		
public:
	~Collisions();
	static Collisions* GetInst();
	bool Circle(Vector2D pos1, Vector2D pos2, float radius1, float radius2);
	bool Circle(BaseCharacter* character1, BaseCharacter* character2);
	bool Box (Rect2D rect1, Rect2D rect2);
};