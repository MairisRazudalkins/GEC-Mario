#pragma once
#include "BaseLevel.h"
#include <iostream>

class ScoreUI;
class CharacterMario;

class GameLevel : public BaseLevel
{
	void SetupLevel() override;

	int score = 0;
	int gameTime = 300;
	float second = 0.f;


	ScoreUI* scoreUi;
	
public:
	GameLevel(SDL_Renderer* renderer, const std::string &mapName);
	~GameLevel();

	void Draw() override;
	void Update(float deltaTime) override;

	CharacterMario* GetMario();

	int GetGameTime() { return gameTime; }
	int GetScore() { return score; }

	void AddScore(int amount);
};