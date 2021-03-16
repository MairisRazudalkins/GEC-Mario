#pragma once
#include "SceneObject.h"

class CharacterMario;

class FinishPoint : public SceneObject
{
	CharacterMario* player;
	
public:
	FinishPoint(Vector2D position, std::string path, CharacterMario* player);
	~FinishPoint();
	void Draw() override;
	void Update(float deltaTime) override;

	void OnInteractWithPlayer();
};

