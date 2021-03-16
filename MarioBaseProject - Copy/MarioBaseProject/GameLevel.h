#pragma once
#include "BaseLevel.h"

class CharacterMario;
class FinishPoint;

class GameLevel : public BaseLevel
{
	bool SetupLevel() override;

	CharacterMario* characterMario;
	FinishPoint* finishPoint;

public:
	GameLevel(SDL_Renderer* renderer, const std::string &mapName);
	~GameLevel();

	void Draw() override;
	void Update(float deltaTime) override;

	CharacterMario* GetMario() { return characterMario; }
};