#pragma once
#include "SceneObject.h"
#include "Texture2D.h"

class Map;

class Character : public SceneObject
{
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	float Decelerate();
	
protected:
	virtual void ApplyPhysics(float deltaTime);
	virtual void CheckCollision();
	virtual void Jump();

	Map* map;
	
	FacingDirection facingDir = DIR_RIGHT;
	Vector2D acceleration;
	Vector2D velocity;

	float movement = 0.f;
	float movementSpeed = 75.f;
	
	const float mass = 1.f;
	const float airControl = 0.0015f;
	const float accelerationRate = 0.0007f;
	const float friction = 0.0008f;
	const float initialJumpVelocity = -275.f;

	bool isGrounded = false;
	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isAlive = true;

public:
	Character(Vector2D position, std::string path, Map* map, float movementSpeed = 75.f, float mass = 1.f, float accelerationRate = 0.0007f);
	~Character();
	
	void Draw() override;
	void Update(float deltaTime) override;

	void KillCharacter();
	bool IsGrounded() { return isGrounded; }
	bool IsFalling() { return velocity.y > 0.f; }
	bool IsAlive() { return isAlive; }
};

