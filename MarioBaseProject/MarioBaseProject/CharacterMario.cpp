#include "CharacterMario.h"
#include "Input.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "TextureAnimation.h"
#include "Utility.h"
#include "Map.h"

CharacterMario::CharacterMario(Vector2D position, Map* map) : Character(position, "Images/MarioSpriteSheet.png", map)
{
	SetSrcRect(Rect2D(0.f, 0.f, TILE_SIZE, TILE_SIZE));
	
	objTag = "Mario";
	characterAnim = new TextureAnimation(this, texture);

	jumpClip = AudioManager::LoadClip("Jump.wav");
	deathClip = AudioManager::LoadClip("PlayerDeath.wav");
	powerUpClip = AudioManager::LoadClip("PowerUp.wav");
}

CharacterMario::~CharacterMario()
{
	Mix_FreeChunk(jumpClip);
	Mix_FreeChunk(deathClip);
	
	delete characterAnim;
}

void CharacterMario::Update(float deltaTime)
{
	if (levelComplete)
	{
		movement = 0.f;
		acceleration.x = 0.f;

		levelCompleteTimer += deltaTime;
		
		if (levelCompleteTimer < .5f)
			Jump();

		Character::Update(deltaTime);
		velocity.x = 0.f; // fixed issue
		UpdateAnimation(deltaTime);
		return;
	}
	
	if (!isAlive)
	{
		if (!Mix_Playing(deathClip->allocated))
		{
			AudioManager::PlayClip(deathClip);
			Mix_HaltMusic();
		}
		
		movement = 0.f;
		deathTimer += deltaTime;

		if (deathTimer > 1.f)
		{
			if (deathTimer < 3.2f)
				Jump();
			else
				ScreenManager::GetInst()->ChangeScreen(SCREEN_MENU);
			
			acceleration.y = Utils::Clamp(acceleration.y + (GRAVITY_RATE / mass), acceleration.y + (GRAVITY_RATE / mass), 300.f);
			velocity.y = Utils::Clamp(acceleration.y * deltaTime, acceleration.y * deltaTime, 300.f);
			
			position.y += velocity.y;
		}
		
		return;
	}

	if (isInvincible)
	{
		invincibleTimer += deltaTime;

		if (invincibleTimer >= 2.f)
		{
			isInvincible = false;
			invincibleTimer = 0.f;
		}
	}
	
	isMovingLeft = Input::IsKeyHeld(Key_A) || Input::IsKeyHeld(Key_LEFT) ? true : false;
	isMovingRight = Input::IsKeyHeld(Key_D) || Input::IsKeyHeld(Key_RIGHT) ? true : false;

	if (Input::IsKeyHeld(Key_SPACE) || Input::IsKeyHeld(Key_UP))
		Jump();

	Character::Update(deltaTime);
	UpdateAnimation(deltaTime);

	if (position.x <= ScreenManager::GetInst()->GetCameraPos().x)
	{
		position.x = ScreenManager::GetInst()->GetCameraPos().x;
		acceleration.x = 0.f;
	}
	else if (position.x + srcRect.width >= ScreenManager::GetInst()->GetCurrentMapLength())
	{
		position.x = ScreenManager::GetInst()->GetCurrentMapLength() - srcRect.width;
		acceleration.x = 0.f;
	}


	Vector2D cameraPos = ScreenManager::GetInst()->GetCameraPos();

	if (cameraPos.x + SCREEN_WIDTH >= ScreenManager::GetInst()->GetCurrentMapLength())
		ScreenManager::GetInst()->SetCameraPos(Vector2D(ScreenManager::GetInst()->GetCurrentMapLength() - SCREEN_WIDTH, 0.f));
	else if ((cameraPos.x + SCREEN_WIDTH / 2) < position.x)
		ScreenManager::GetInst()->SetCameraPos(Vector2D(position.x - (SCREEN_WIDTH / 2), 0.f));
}

void CharacterMario::UpdateAnimation(float deltaTime)
{
	if (!isGrounded)
	{
		characterAnim->ChangeAnim(1, 3);
	}
	else if (velocity.x > 0.f || velocity.x < 0.f)
	{
		if (currentPowerUp != POWER_UP_NONE)
			characterAnim->ChangeAnim(3, 0, true);
		else
			characterAnim->ChangeAnim(2, 1);
	}
	else
	{
		characterAnim->ChangeAnim(0, 0);
	}

	float playRate = velocity.x < 0.f ? (velocity.x * -1) * movementSpeed : velocity.x * movementSpeed;
	characterAnim->SetPlayRate(playRate * 2.f);
	characterAnim->Update(deltaTime);
}

void CharacterMario::Draw()
{
	characterAnim->Draw();
}

void CharacterMario::GivePowerUp(PowerUpType powerUpType)
{
	currentPowerUp = powerUpType;
	
	if (powerUpType == SUPER_SHROOM || powerUpType == FIRE_FLOWER)
	{
		SetSrcRect(Rect2D(0.f, TILE_SIZE, TILE_SIZE, 53.f));
		characterAnim->ChangeAnim(3, 0, true);

		AudioManager::PlayClip(powerUpClip);
	}
	else
	{
		SetSrcRect(Rect2D(0.f, 0.f, TILE_SIZE, TILE_SIZE));
	}
}

void CharacterMario::OnObjectHit(SceneObject* other)
{
	if (other->GetTag()[0] == 'E' && !isInvincible)
	{
		if (currentPowerUp == POWER_UP_NONE)
		{
			KillCharacter();
			characterAnim->ChangeAnim(1, 4);
		}
		else
		{
			GivePowerUp(POWER_UP_NONE);
		}

		isInvincible = true;
	}
}

void CharacterMario::LaunchY(float amount)
{
	acceleration.y = amount;
	AudioManager::PlayClip(jumpClip);
}

void CharacterMario::OnLevelComplete()
{
	levelComplete = true;
}

void CharacterMario::Jump()
{
	if (isGrounded && isAlive)
		AudioManager::PlayClip(jumpClip);
	
	Character::Jump();
}