#pragma once
#include "BaseCharacter.h"
class CharacterKoopa : public BaseCharacter
{
	float singleSpriteWidth;
	float singleSpriteHeight;

	bool isInjured;
	float injuredTime;

	void FlipRightWayUp();
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map, FacingDirection startFacingDir, float initMoveSpeed);
	~CharacterKoopa();
	bool GetIsInjured() { return isInjured; }
	
	void Render() override;
	void Update(float deltaSeconds, SDL_Event e) override;
	
	void TakeDamage();
	void Jump();
};

