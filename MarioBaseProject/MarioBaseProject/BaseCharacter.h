#pragma once
#include <SDL.h>
#include <string>
#include "Texture2D.h"
#include "Commons.h"

class LevelMap;

class BaseCharacter
{
protected:
	SDL_Renderer* renderer;
	Vector2D position;
	Vector2D velocity;
	Texture2D* texture;

	FacingDirection facingDir;
	LevelMap* currentMap;
	
	Texture2D* testTile;
	Vector2D testTilePos;

	float collisionRadius;

	float movementSpeed = 300.f;
	
	//float jumpForce = 5.f;
	float decelerationRate = 5.f;

	bool isAlive;
	bool isGrounded;
	bool isMovingRight;
	bool isMovingLeft;

	bool canJump;
	bool jumping;
	float jumpForce;

	int testInt = 0;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);

	void AddGravity(float deltaTime);
	void ApplyPhysics(float deltaTime);

public:
	BaseCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map);
	~BaseCharacter();

	virtual void Render();
	virtual void Update(float deltaSeconds, SDL_Event e);
	void SetPosition(Vector2D newPos);
	void SetIsAlive(bool alive) { isAlive = alive; }
	bool GetIsAlive() { return isAlive; }
	void CancelJump();
	FacingDirection GetFacingDir() { return facingDir; }
	void ChangeMovementDir(FacingDirection movementDir);

	float GetCollisionRadius() { return collisionRadius; }
	bool IsJumping() { return jumping; }
	Rect2D GetCollisionBox() { return Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight()); }
	Vector2D GetPosition() { return position; }
};

