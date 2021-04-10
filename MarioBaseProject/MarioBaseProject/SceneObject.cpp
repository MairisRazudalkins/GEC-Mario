#include <iostream>
#include "SceneObject.h"
#include "Constants.h"
#include "ScreenManager.h"

SceneObject::SceneObject(Vector2D position, std::string path, CollisionType collisionType)
{
	renderer = ScreenManager::GetInst()->GetRenderer();
	this->collisionType = collisionType;
	this->position = position;
	
	texture = new Texture2D();
	if (!texture->LoadTextureFromFile(path))
		std::cout << "SceneObject::Failed to load texture!\n";

	SetSrcRect(Rect2D(0, 0, texture->GetWidth(), texture->GetHeight()));
}

SceneObject::SceneObject(Vector2D position, Rect2D srcRect, Texture2D* texture, CollisionType collisionType)
{
	renderer = ScreenManager::GetInst()->GetRenderer();
	this->collisionType = collisionType;
	this->position = position;
	this->texture = texture;

	SetSrcRect(srcRect);
}

SceneObject::~SceneObject()
{
	renderer = nullptr;
	texture = nullptr;
}

void SceneObject::Draw()
{
	texture->DrawToWorld(srcRect, Rect2D(position.x, position.y, TILE_SIZE, TILE_SIZE), flip);
}

void SceneObject::Update(float deltaTime)
{
	
}

void SceneObject::OnObjectHit(SceneObject* other)
{
}
