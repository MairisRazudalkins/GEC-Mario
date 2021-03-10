#include "CharacterKoopa.h"
#include "Constants.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map, FacingDirection startFacingDir, float initMoveSpeed) : BaseCharacter(renderer, imagePath, startPos, map)
{
	facingDir = startFacingDir;
	position = startPos;
	this->movementSpeed = initMoveSpeed;
	isInjured = false;

	singleSpriteHeight = texture->GetHeight();
	singleSpriteWidth = texture->GetWidth() / 2;
}

CharacterKoopa::~CharacterKoopa()
{
	
}

void CharacterKoopa::Render()
{
	float left = isInjured ? singleSpriteWidth : 0.f;

	SDL_Rect src = { left, 0, singleSpriteWidth, singleSpriteHeight };
	SDL_Rect dst = { position.x, position.y, singleSpriteWidth, singleSpriteHeight };

	texture->Render(src, dst, facingDir == DIR_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void CharacterKoopa::Update(float deltaSeconds, SDL_Event e)
{
	BaseCharacter::Update(deltaSeconds, e);

	if (!isInjured)
	{
		if (facingDir == DIR_LEFT)
		{
			isMovingLeft = true;
			isMovingRight = false;
		}
		else if (facingDir == DIR_RIGHT)
		{
			isMovingLeft = false;
			isMovingRight = true;
		}
	}
	else
	{
		isMovingRight = false;
		isMovingLeft = false;

		injuredTime -= deltaSeconds;

		if (injuredTime <= 0.f)
			FlipRightWayUp();
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	facingDir == DIR_RIGHT ? DIR_LEFT : DIR_RIGHT;
	isInjured = false;
	Jump();
}


void CharacterKoopa::TakeDamage()
{
	isInjured = true;
	injuredTime = INJURED_DURATION;
	Jump();
}

void CharacterKoopa::Jump()
{
	//if (!jumping)
	//{
	//	jumpForce = INITIAL_JUMP_FORCE;
	//	jumping = true;
	//	canjump = false;
	//}
}
