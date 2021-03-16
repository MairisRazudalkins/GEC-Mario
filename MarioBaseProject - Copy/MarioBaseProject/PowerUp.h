#pragma once
#include "SceneObject.h"

class PowerUpDropTile;

class PowerUp : public SceneObject
{
	PowerUpDropTile* owner;
	PowerUpType powerUpType;
	
	float animTimeValue = 0.f;
	const Vector2D startPos;
	
public:
	PowerUp(Vector2D position, std::string path, PowerUpType powerUpType, PowerUpDropTile* owner);
	~PowerUp();
	void Update(float deltaTime) override;
	void Draw() override;

	void OnObjectHit(SceneObject* other) override;
	
	bool isInPlace = false;
};