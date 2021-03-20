#pragma once
#include "BaseLevel.h"

class CharacterMario;

class GameLevel : public BaseLevel
{
	void SetupLevel() override;
	
public:
	GameLevel(SDL_Renderer* renderer, const std::string &mapName);
	~GameLevel();

	void Draw() override;
	void Update(float deltaTime) override;

	CharacterMario* GetMario();
};