#pragma once
#include "Character.h"

class CharacterMario : public Character
{
	void ApplyPhysics(float deltaTime) override;
	
public:
	CharacterMario(Vector2D position, std::string path, Map* map);
	~CharacterMario();
	
	void Update(float deltaTime) override;
	void Draw() override;
};

