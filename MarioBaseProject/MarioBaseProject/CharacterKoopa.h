#pragma once
#include "Character.h"

class TextureAnimation;
class CharacterMario;

class CharacterKoopa : public Character
{
	TextureAnimation* characterAnim;
	CharacterMario* player;

	bool isTucked = false;
	bool isDamaged = false;
	float damagedTimer = 0.f;

	float speedMultiplier = 5.f;

public:
	CharacterKoopa(Vector2D position, Map* map, CharacterMario* player);
	~CharacterKoopa();

	void Draw() override;
	void Update(float deltaTime) override;
};
