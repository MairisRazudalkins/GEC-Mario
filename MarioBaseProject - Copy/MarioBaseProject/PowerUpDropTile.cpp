#include "PowerUpDropTile.h"
#include "PowerUp.h"
#include "Constants.h"

PowerUpDropTile::PowerUpDropTile(Vector2D position, Rect2D srcRect, Texture2D* texture, PowerUpType powerUpType) : SceneObject(position, srcRect, texture, CollisionType::BLOCK), startPos(position)
{
	this->powerUpType = PowerUpType::FIRE_FLOWER; // change
}

PowerUpDropTile::~PowerUpDropTile()
{
	if (spawnedPowerUp != nullptr)
	{
		delete spawnedPowerUp;
		spawnedPowerUp = nullptr;
	}
}

void PowerUpDropTile::Update(float deltaTime)
{
	if (spawnedPowerUp != nullptr)
		spawnedPowerUp->Update(deltaTime);
	
	if (playingAnim)
	{
		srcRect.x = 34 * TILE_SIZE;
		
		if (reverse)
		{
			animTimeValue -= 100.f * deltaTime;

			if (animTimeValue < 0.f)
			{
				animTimeValue = 0.f;
				playingAnim = false;
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
}

void PowerUpDropTile::Draw()
{
	if (spawnedPowerUp != nullptr)
		spawnedPowerUp->Draw();
	
	SceneObject::Draw();
}

void PowerUpDropTile::OnObjectHit(SceneObject* other)
{
	if (!playingAnim)
		playingAnim = true;
}

void PowerUpDropTile::SpawnPowerUp()
{
	if (powerUpType != POWER_UP_NONE && !wasHit)
	{
		spawnedPowerUp = new PowerUp(position, "Images/PowerUps.png", powerUpType, this);
		powerUpType = POWER_UP_NONE;
	}

	wasHit = true;
}

void PowerUpDropTile::OnPickUpCollected()
{
	delete spawnedPowerUp;
	spawnedPowerUp = nullptr;
}