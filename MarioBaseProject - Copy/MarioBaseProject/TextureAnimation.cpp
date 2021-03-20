#include "TextureAnimation.h"
#include "Texture2D.h"

TextureAnimation::TextureAnimation(SceneObject* srcObject, Texture2D* srcTexture) : SceneObject(srcObject->GetPosition(), srcObject->GetSrcRect(), srcTexture)
{
	this->srcObject = srcObject;
}

TextureAnimation::~TextureAnimation()
{
	srcObject = nullptr;
}

void TextureAnimation::Update(float deltaTime)
{
	if (srcObject && texture)
	{
		timeValue += playRate * deltaTime;

		if (timeValue >= 1.f)
		{
			timeValue = 0.f;

			if (shouldReverse && playingInReverse)
			{
				currentFrame--;
				
				if (currentFrame <= startFrame)
					playingInReverse = false;
			}
			else
			{
				currentFrame++;
				
				if (currentFrame >= startFrame + numOfFrames)
				{
					currentFrame = shouldReverse ? currentFrame - 1 : startFrame;
					playingInReverse = shouldReverse;
				}
			}

			SetSrcRect(Rect2D(currentFrame * GetSrcRect().width, GetSrcRect().y, GetSrcRect().width, GetSrcRect().height));
		}
	}
}

void TextureAnimation::Draw()
{
	texture->DrawToWorld(GetSrcRect(), srcObject->GetDstRect(), srcObject->GetFlip());
}

void TextureAnimation::ChangeAnim(int numOfFrames, int startFrame, bool shouldReverse)
{
	if (this->numOfFrames == numOfFrames && this->startFrame == startFrame)
		return;

	this->numOfFrames = numOfFrames;
	this->startFrame = startFrame;
	this->shouldReverse = shouldReverse;
	currentFrame = startFrame;
	
	SetSrcRect(Rect2D(currentFrame * GetSrcRect().width, srcObject->GetSrcRect().y, srcObject->GetSrcRect().width, srcObject->GetSrcRect().height));
}

void TextureAnimation::ChangeAnim(int numOfFrames, int startFrame, Rect2D srcRect, bool shouldReverse)
{
	ChangeAnim(numOfFrames, startFrame, shouldReverse);
	SetSrcRect(srcRect);
}