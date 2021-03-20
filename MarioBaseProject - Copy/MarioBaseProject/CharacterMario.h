#pragma once
#include "Character.h"
#include "AudioManager.h"

class TextureAnimation;

class CharacterMario : public Character
{
	TextureAnimation* characterAnim;
	PowerUpType currentPowerUp = POWER_UP_NONE;

	bool isInvincible = false;
	bool levelComplete = false;
	float levelCompleteTimer = 0.f;
	float invincibleTimer = 0.f;
	float deathTimer = 0.f;

	Mix_Chunk* jumpClip;
	Mix_Chunk* deathClip;
	Mix_Chunk* powerUpClip;

protected:
	void Jump() override;
	
public:
	CharacterMario(Vector2D position, Map* map);
	~CharacterMario();
	
	void Update(float deltaTime) override;
	void UpdateAnimation(float deltaTime);
	void Draw() override;
	void GivePowerUp(PowerUpType powerUpType);

	void OnObjectHit(SceneObject* other) override;
	void LaunchY(float amount);

	void OnLevelComplete();
};