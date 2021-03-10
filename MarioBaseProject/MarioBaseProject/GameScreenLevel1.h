#pragma once
#include <vector>

#include "Commons.h"
#include "GameScreen.h"

class LevelMap;
class BaseCharacter;
class Texture2D;
class PowBlock;
class CharacterKoopa;

class GameScreenLevel1 : public GameScreen
{
	Texture2D* backgroundTexture;
	BaseCharacter* mario;
	BaseCharacter* luigi;
	LevelMap* levelMap;

	PowBlock* powBlock;
	std::vector<CharacterKoopa*> enemies;

	bool screenShake;
	float shakeTime;
	float wobble;
	float backgroundYPos;
	
	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void CreateKoopa(Vector2D pos, FacingDirection dir, float speed);

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
};

