#pragma once
#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Commons.h"
#include "Collisions.h"
#include <iostream>

class Vector2D;

class SceneObject : public GameObject
{
	SDL_Renderer* renderer;
	CollisionType collisionType = CollisionType::NONE;
	bool isVisible = true;

protected:
	Texture2D* texture;
	Rect2D srcRect;
	Vector2D position;

public:
	SceneObject(Vector2D position, std::string path, CollisionType collisionType = CollisionType::NONE);
	SceneObject(Vector2D position, Rect2D srcRect, Texture2D* texture, CollisionType collisionType = CollisionType::NONE);
	~SceneObject();

	void Draw() override;
	void Update(float deltaTime) override;

	void SetPosition(Vector2D newPos) { position = newPos; }
	void SetSrcRect(Rect2D newRect) { srcRect = newRect; }

	Vector2D GetPosition() { return position; }
	Rect2D GetSrcRect() { return srcRect; }

	void SetCollisionType(CollisionType collisionType) { std::cout << collisionType << std::endl; this->collisionType = collisionType; }
	CollisionType GetCollisionType() { return collisionType; }
	
	void SetVisibility(bool visible) { isVisible = visible; }
	bool IsVisible() { return isVisible; }
};