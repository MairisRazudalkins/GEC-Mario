#pragma once
#include "SceneObject.h"
#include "Texture2D.h"

class Map;

class Character : public SceneObject
{
	FacingDirection facingDir = DIR_RIGHT;
	Map* map;

	Texture2D* testTile;
	
protected:
	virtual void ApplyPhysics(float deltaTime);
	virtual void CheckCollision();
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Decelerate(float deltaTime);
	void Jump();
	
	const float movementSpeed = 325.f;
	const float accelerationRate = 5.f;
	const float airControl = 3.f;
	const float friction = 3.f;
	
	const float initialJumpVelocity = -0.225f;

	float movement = 0.f;

	bool isGrounded = false;
	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isAlive = true;

	Vector2D velocity;

public:
	Character(Vector2D position, std::string path, Map* map);
	~Character();
	
	void Draw() override;
	void Update(float deltaTime) override;

	void KillCharacter();
};

