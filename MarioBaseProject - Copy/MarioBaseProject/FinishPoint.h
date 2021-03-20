#pragma once
#include "SceneObject.h"

class CharacterMario;
class Mix_Chunk;

class FinishPoint : public SceneObject
{
	CharacterMario* player;
	
	bool isFinished = false;
	float finishTimer = 0.f;

	Mix_Chunk* levelCompleteSound;
	
public:
	FinishPoint(Vector2D position,  CharacterMario* player);
	~FinishPoint();
	void Draw() override;
	void Update(float deltaTime) override;
};

