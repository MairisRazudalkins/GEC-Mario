#pragma once
#include "Commons.h"
#include "SceneObject.h"

class Texture2D;

class TextureAnimation : public SceneObject
{
	SceneObject* srcObject;
	
	int startFrame = 0;
	int numOfFrames = 0;
	int currentFrame = 0;

	bool shouldReverse = false;
	bool playingInReverse = false;

	float playRate = 1.f;
	float timeValue = 0.f;
	
public:
	TextureAnimation(SceneObject* srcObject, Texture2D* srcTexture);
	~TextureAnimation();
	void Update(float deltaTime) override;
	void Draw() override;

	void ChangeAnim(int numOfFrames, int startFrame, bool shouldReverse = false);
	void ChangeAnim(int numOfFrames, int startFrame, Rect2D newRect, bool shouldReverse = false);
	
	void SetPlayRate(float playRate) { this->playRate = playRate; }
};
