#include <iostream>
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	levelMap = nullptr;
	SetLevelMap();
	SetUpLevel();

	screenShake = false;
	backgroundYPos = 0.f;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete backgroundTexture;
	backgroundTexture = nullptr;

	delete mario;
	mario = nullptr;
	
	delete powBlock;
	powBlock = nullptr;

	enemies.clear();
}

void GameScreenLevel1::Render()
{
	backgroundTexture->Render(Vector2D(0, backgroundYPos), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
	powBlock->Render();
	levelMap->Render();

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();

	if (Collisions::GetInst()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		
	}

	if (screenShake)
	{
		shakeTime -= deltaTime;
		wobble++;
		backgroundYPos = sin(wobble);
		backgroundYPos *= 3.0f;

		if (shakeTime <= 0.f)
		{
			screenShake = false;
			shakeTime = 0.f;
			backgroundYPos = 0.f;
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!enemies.empty())
	{
		int enemyIndexToDelete = -1;

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->GetPosition().y > 300.f)
			{
				//if (e)
				//{
				//	
				//}
				
				if (enemies[i]->GetPosition().x < (float)(enemies[i]->GetCollisionBox().width * 0.5f) || enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(enemies[i]->GetCollisionBox().width * 0.55))
				{
					//enemies[i]->SetIsAlive(false);

					if (enemies[i]->GetFacingDir() == DIR_RIGHT)
					{
						enemies[i]->ChangeMovementDir(DIR_LEFT);
					}
					else
					{
						enemies[i]->ChangeMovementDir(DIR_RIGHT);
					}
					
					//enemies[i]->ChangeMovementDir(enemies[i]->GetFacingDir() == DIR_RIGHT ? DIR_LEFT : DIR_RIGHT);
				}
			}

			//enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((enemies[i]->GetPosition().y > 300.0f || enemies[i]->GetPosition().y <= 64.0f) && (enemies[i]->GetPosition().x < 64.0f || enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::GetInst()->Circle(enemies[i], mario))
				{
					if (enemies[i]->GetIsInjured())
					{
						enemies[i]->SetIsAlive(false);
					}
					else
					{
						//kill mario
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!enemies[i]->GetIsAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			enemies.erase(enemies.begin() + enemyIndexToDelete);
		}
	}
}


void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::GetInst()->Box(mario->GetCollisionBox(), powBlock->GetCollisionBox()) && powBlock->IsAvaliable())
	{
		if (mario->IsJumping())
		{
			DoScreenShake();
			mario->CancelJump();
			std::cout << mario->IsJumping() << std::endl;
			powBlock->TakeHit();

			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->TakeDamage();
			}	
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	backgroundTexture = new Texture2D(renderer);
	
	if (!backgroundTexture->LoadTextureFromFile("Images/TestImg.bmp"))
	{	
		std::cout << "Failed to load background texture\n";
		return false;
	}

	mario = new CharacterMario(renderer, "Images/Mario.png", Vector2D(64, 100), levelMap);
	luigi = new CharacterLuigi(renderer, "Images/Luigi.png", Vector2D(100, 100), levelMap);
	powBlock = new PowBlock(renderer, levelMap);

	CreateKoopa(Vector2D(150, 32), DIR_RIGHT, 96.f);
	CreateKoopa(Vector2D(325, 32), DIR_LEFT, 96.f);

	Vector2D gridPos = LevelMap::ScreenPosToGridPos(mario->GetPosition());

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int tempMap[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (levelMap != nullptr)
		delete levelMap;

	levelMap = new LevelMap(tempMap, renderer);
}

void GameScreenLevel1::DoScreenShake()
{
	screenShake = true;
	shakeTime = SHAKE_DURATION;
	wobble = 0.f;
}

void GameScreenLevel1::CreateKoopa(Vector2D pos, FacingDirection dir, float speed)
{
	enemies.push_back(new CharacterKoopa(renderer, "Images/Koopa.png", pos, levelMap, dir, speed));
}