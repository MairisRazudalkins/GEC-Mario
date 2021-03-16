#pragma once
#include "Character.h"

class CharacterMario : public Character
{
	
public:
	CharacterMario(Vector2D position, std::string path, Map* map);
	~CharacterMario();
	
	void Update(float deltaTime) override;

	void GivePowerUp(PowerUpType powerUpType);
};

