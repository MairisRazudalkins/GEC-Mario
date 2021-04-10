#include "FinishPoint.h"
#include "CharacterMario.h"
#include "ScreenManager.h"

FinishPoint::FinishPoint(Vector2D position, CharacterMario* player) : SceneObject(position, "Images/FinishTile.png")
{
	this->player = player;
	levelCompleteSound = AudioManager::LoadClip("LevelCleared.wav");
}

FinishPoint::~FinishPoint()
{
	player = nullptr;
}

void FinishPoint::Draw()
{
	SceneObject::Draw();
}

void FinishPoint::Update(float deltaTime)
{
	if (isFinished)
	{
		if (!Mix_Playing(levelCompleteSound->allocated))
		{
			Mix_HaltMusic();
			AudioManager::PlayClip(levelCompleteSound);
		}
		
		finishTimer += deltaTime;

		if (finishTimer > 3.f)
			ScreenManager::GetInst()->ChangeScreen(ScreenType::SCREEN_MENU);
	}
	else if (Collisions::Box(player->GetDstRect(), GetDstRect()))
	{
		player->OnLevelComplete();
		isFinished = true;
	}
}
