#pragma once
#include "BaseLevel.h"

class Character;

class GameLevel : public BaseLevel
{
	bool SetupLevel() override;

	Character* testCharacter;

public:
	GameLevel(SDL_Renderer* renderer, const std::string &mapName);
	~GameLevel();

	void Draw() override;
	void Update(float deltaTime) override;
};
