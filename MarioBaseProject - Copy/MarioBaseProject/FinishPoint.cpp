#include "FinishPoint.h"
#include "CharacterMario.h"

FinishPoint::FinishPoint(Vector2D position, std::string path, CharacterMario* player) : SceneObject(position, path)
{
	this->player = player;
}

FinishPoint::~FinishPoint()
{
	player = nullptr;
}

void FinishPoint::Draw()
{
	SceneObject::Draw();
}

void FinishPoint::Update(float deltaTime)
{
	if (Collisions::Box(GetSrcRect(), player->GetDstRect()))
		OnInteractWithPlayer();
}

void FinishPoint::OnInteractWithPlayer()
{
	//complete level
}