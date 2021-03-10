#pragma once
#include "SceneObject.h"
#include "Texture2D.h"

class Map;

class Character : public SceneObject
{
	FacingDirection facingDir = DIR_RIGHT;
	Map* map;
	
protected:
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void ApplyPhysics(float deltaTime);
	virtual void CheckCollision();
	void Jump();
	
	const float movementSpeed = 200.f;
	const float accelerationRate = 0.0003f;
	const float airControl = 0.0005f;
	const float friction = 0.0002f;

	float jumpForce = 0.f;
	float movement = 0.f;

	bool isGrounded = false;
	bool isMovingRight = false;
	bool isMovingLeft = false;

	Vector2D velocity;

public:
	Character();
	Character(Vector2D position, std::string path, Map* map);
	~Character();
	
	void Draw() override;
	void Update(float deltaTime) override;
	Rect2D GetCollisionBox() { return Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight()); }
};

