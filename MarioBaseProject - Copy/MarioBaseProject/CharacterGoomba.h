#pragma once
#include "Character.h"

class CharacterMario;
class GameLevel;
class TextureAnimation;

class CharacterGoomba : public Character
{	
	TextureAnimation* characterAnim;
	CharacterMario* player;

	bool isDamaged = false;
	float damagedTimer = 0.f;
	
public:
	CharacterGoomba(Vector2D position, Map* map, CharacterMario* player);
	~CharacterGoomba();
	void Update(float deltaTime) override;
	void Draw() override;
};