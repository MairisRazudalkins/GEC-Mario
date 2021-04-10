#include "CharacterGoomba.h"
#include "TextureAnimation.h"
#include "Constants.h"
#include "CharacterMario.h"
#include "ScreenManager.h"
#include "GameLevel.h"

CharacterGoomba::CharacterGoomba(Vector2D position, Map* map, CharacterMario* player) : Character(position, "Images/EnemySpriteSheet.png", map, 15.f, 1.f, 0.1f)
{
	objTag = "E Goomba";
	this->player = player;
	facingDir = DIR_LEFT;
	
	SetSrcRect(Rect2D(0.f, 0.f, TILE_SIZE, TILE_SIZE));
	
	characterAnim = new TextureAnimation(this, texture);
	characterAnim->ChangeAnim(2, 0);
	characterAnim->SetPlayRate(2.5f);
}

CharacterGoomba::~CharacterGoomba()
{
	delete characterAnim;
	
	player = nullptr;
}

void CharacterGoomba::Update(float deltaTime)
{
	if (!isAlive)
		return;
	
	isMovingRight = facingDir == DIR_RIGHT && !isDamaged ? true : false;
	isMovingLeft = !isMovingRight && !isDamaged;
	
	Character::Update(deltaTime);
	characterAnim->Update(deltaTime);
	
	if (acceleration.x == 0.f)
		facingDir = facingDir == DIR_RIGHT ? DIR_LEFT : DIR_RIGHT;

	if (isDamaged)
	{
		damagedTimer += deltaTime;

		if (damagedTimer >= 0.2f)
		{
			GameLevel* lvl = (GameLevel*)ScreenManager::GetInst()->GetCurrentLevel();
			lvl->AddScore(100);
			KillCharacter();
		}
	}
	
	if (Collisions::Box(player->GetDstRect(), GetDstRect()))
	{
		if (player->GetDstRect().y + player->GetDstRect().height <= position.y + 1.f && !player->IsGrounded() && player->IsFalling())
		{
			if (!isDamaged)
			{
				isDamaged = true;
				characterAnim->ChangeAnim(1, 2);
				player->LaunchY(-250.f);
			}
		}
		else if (!isDamaged)
		{
			player->OnObjectHit(this);
		}
	}
}

void CharacterGoomba::Draw()
{
	if (isAlive)
		characterAnim->Draw();
}