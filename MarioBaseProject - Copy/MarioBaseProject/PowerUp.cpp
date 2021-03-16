#include "PowerUp.h"
#include "SceneObject.h"
#include "CharacterMario.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "GameLevel.h"
#include "PowerUpDropTile.h"

PowerUp::PowerUp(Vector2D position, std::string path, PowerUpType powerUpType, PowerUpDropTile* owner) : SceneObject(position, path), startPos(position)
{
	this->powerUpType = powerUpType;
	this->owner = owner;

	if (powerUpType != POWER_UP_NONE)
		SetSrcRect(Rect2D((int)powerUpType * TILE_SIZE, 0.f, TILE_SIZE, TILE_SIZE));
}

PowerUp::~PowerUp()
{
	owner = nullptr;
}

void PowerUp::Update(float deltaTime)
{
	CharacterMario* mario = ((GameLevel*)ScreenManager::GetInst()->GetCurrentLevel())->GetMario();

	if (mario != nullptr && Collisions::Box(mario->GetDstRect(), GetDstRect()))
	{
		OnObjectHit(mario);
		return;
	}

	
	if (!isInPlace)
	{
		animTimeValue += 50.f * deltaTime;

		if (animTimeValue >= TILE_SIZE)
		{
			isInPlace = true;
			position.y = startPos.y - texture->GetHeight();
			return;
		}

		position.y = startPos.y - animTimeValue;
	}
}

void PowerUp::Draw()
{
	SceneObject::Draw();
}

void PowerUp::OnObjectHit(SceneObject* other)
{
	if (other != nullptr && other->GetTag() == "Mario")
	{
		CharacterMario* mario = (CharacterMario*)other;

		mario->GivePowerUp(powerUpType);
		owner->OnPickUpCollected();
	}
}
