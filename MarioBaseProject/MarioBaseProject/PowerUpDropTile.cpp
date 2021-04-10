#include "PowerUpDropTile.h"
#include "PowerUp.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "GameLevel.h"
#include "TextureAnimation.h"

Texture2D* PowerUpDropTile::editorPowerUpVisual = nullptr;

PowerUpDropTile::PowerUpDropTile(Vector2D position, Rect2D srcRect, Texture2D* texture, PowerUpType powerUpType) : SceneObject(position, srcRect, texture, CollisionType::BLOCK), startPos(position)
{
	objTag = "PowerUpTile";
	this->powerUpType = powerUpType;
	
	tileAnim = new TextureAnimation(this, texture);
	tileAnim->ChangeAnim(4, 30);
	tileAnim->SetPlayRate(5.f);
}

PowerUpDropTile::~PowerUpDropTile()
{
	delete tileAnim;
	delete editorPowerUpVisual;
	
	delete spawnedPowerUp;
	spawnedPowerUp = nullptr;
}

void PowerUpDropTile::Update(float deltaTime)
{
	if (spawnedPowerUp != nullptr)
		spawnedPowerUp->Update(deltaTime);
	
	if (playingHitAnim)
	{
		srcRect.x = 34 * TILE_SIZE;
		
		if (reverse)
		{
			animTimeValue -= 100.f * deltaTime;

			if (animTimeValue < 0.f)
			{
				animTimeValue = 0.f;
				playingHitAnim = false;
				reverse = false;
				SpawnPowerUp();
				return;
			}
		}
		else
		{
			animTimeValue += 100.f * deltaTime;

			if (animTimeValue > 5.f)
			{
				animTimeValue = 5.f;
				reverse = true;
			}
		}
		position.y = startPos.y - animTimeValue;

		if (spawnedPowerUp != nullptr)
		{
			spawnedPowerUp->SetPosition(Vector2D(spawnedPowerUp->GetPosition().x, position.y - TILE_SIZE));
			spawnedPowerUp->isInPlace = true;
		}
	}

	tileAnim->Update(deltaTime);
}

void PowerUpDropTile::Draw()
{
	if (spawnedPowerUp != nullptr)
		spawnedPowerUp->Draw();
	
	tileAnim->Draw();
	
	if (ScreenManager::GetInst()->GetCurrentLevel()->GetIsEditor() && powerUpType != POWER_UP_NONE)
		GetPowerUpVisual()->DrawToWorld(Rect2D((int)powerUpType * TILE_SIZE, 0.f, TILE_SIZE, TILE_SIZE), Rect2D(position.x, position.y, TILE_SIZE, TILE_SIZE));
}

void PowerUpDropTile::OnObjectHit(SceneObject* other)
{
	if (!playingHitAnim)
		playingHitAnim = true;
}

void PowerUpDropTile::SpawnPowerUp()
{
	if (powerUpType != POWER_UP_NONE && !wasHit)
	{
		spawnedPowerUp = new PowerUp(position, "Images/PowerUps.png", powerUpType, this);
		powerUpType = POWER_UP_NONE;
	}

	wasHit = true;
	tileAnim->ChangeAnim(1, 34);
}

void PowerUpDropTile::OnPickUpCollected()
{
	delete spawnedPowerUp;
	spawnedPowerUp = nullptr;
}

void PowerUpDropTile::ChangePowerUp(PowerUpType powerUpType)
{
	this->powerUpType = powerUpType;
}

Texture2D* PowerUpDropTile::GetPowerUpVisual()
{
	if (editorPowerUpVisual == nullptr)
	{
		editorPowerUpVisual = new Texture2D();
		editorPowerUpVisual->LoadTextureFromFile("Images/PowerUps.png");
	}

	return editorPowerUpVisual;
}