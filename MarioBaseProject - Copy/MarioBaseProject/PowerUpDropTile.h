#pragma once
#include "SceneObject.h"
#include "Commons.h"


class TextureAnimation;
class PowerUp;

class PowerUpDropTile : public SceneObject
{
	static Texture2D* editorPowerUpVisual;

	TextureAnimation* tileAnim;
	
	bool playingHitAnim = false;
	bool reverse = false;
	bool wasHit = false;

	PowerUpType powerUpType;
	PowerUp* spawnedPowerUp;
	
	float animTimeValue = 0.f;
	const float maxYOffset = 0.5f;
	const Vector2D startPos;
	
	static Texture2D* GetPowerUpVisual();
	
public:
	PowerUpDropTile(Vector2D position, Rect2D srcRect, Texture2D* texture, PowerUpType powerUpType);
	~PowerUpDropTile();
	
	void Update(float deltaTime) override;
	void Draw() override;
	void OnObjectHit(SceneObject* other) override;
	void SpawnPowerUp();
	void OnPickUpCollected();

	PowerUpType GetPowerType() { return powerUpType; }
	void ChangePowerUp(PowerUpType powerUpType);
};
