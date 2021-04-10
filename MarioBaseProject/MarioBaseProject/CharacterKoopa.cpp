#include "CharacterKoopa.h"
#include "CharacterMario.h"
#include "TextureAnimation.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "GameLevel.h"

CharacterKoopa::CharacterKoopa(Vector2D position, Map* map, CharacterMario* player) : Character(position, "Images/EnemySpriteSheet.png", map, 15.f, 1.f, 1.f)
{
	this->player = player;
	objTag = "E Koopa";
	facingDir = DIR_LEFT;
	flip = SDL_FLIP_HORIZONTAL;
	
	SetSrcRect(Rect2D(0.f, TILE_SIZE, TILE_SIZE, 64.f));
	
	characterAnim = new TextureAnimation(this, texture);
	characterAnim->ChangeAnim(2, 0);
	characterAnim->SetPlayRate(5.f);
}

CharacterKoopa::~CharacterKoopa()
{
	delete characterAnim;

	player = nullptr;
}

void CharacterKoopa::Draw()
{
	if (isAlive)
		characterAnim->Draw();
}

void CharacterKoopa::Update(float deltaTime)
{
	if (!isAlive)
		return;
	
	isMovingRight = facingDir == DIR_RIGHT && (!isDamaged || isTucked) ? true : false;
	isMovingLeft = !isMovingRight && (!isDamaged || isTucked);

	Character::Update(deltaTime);
	characterAnim->Update(deltaTime);

	if (acceleration.x == 0.f)
		facingDir = facingDir == DIR_RIGHT ? DIR_LEFT : DIR_RIGHT;

	if (isDamaged && !isTucked)
	{
		damagedTimer += deltaTime;

		if (damagedTimer >= 2.f)
		{
			damagedTimer = 0.f;
			isDamaged = false;
			srcRect.height = 64.f;
			srcRect.y = 32.f;
			position.y -= TILE_SIZE;
			characterAnim->ChangeAnim(2, 0);
		}
	}

	if (Collisions::Box(player->GetDstRect(), GetDstRect()))
	{
		if (player->GetDstRect().y + player->GetDstRect().height <= position.y + 1.f && !player->IsGrounded() && player->IsFalling())
		{
			if (isDamaged)
			{
				isTucked = true;
				movementSpeed = 150.f;

				GameLevel* lvl = (GameLevel*)ScreenManager::GetInst()->GetCurrentLevel();
				lvl->AddScore(300);
			}
			else
			{
				isDamaged = true;
				srcRect.y = TILE_SIZE * 2;
				srcRect.height = 32.f;
				characterAnim->ChangeAnim(1, 2);
			}

			player->LaunchY(-200.f);
		}
		else if (!isDamaged || isTucked)
		{
			player->OnObjectHit(this);
		}
		else
		{
			isTucked = true;
			movementSpeed = 150.f;
			facingDir = player->GetPosition().x < position.x ? DIR_RIGHT : DIR_LEFT;
		}
	}
}