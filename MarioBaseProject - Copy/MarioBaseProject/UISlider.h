#pragma once
#include "SceneObject.h"

class UIButton;

class UISlider : public SceneObject
{
	UIButton* sliderButton;
	float sliderPercentage = 0.f;
	bool isBeingHeld = false;
	
public:
	UISlider(Vector2D position, float sliderWidth);
	~UISlider();
	
	void Draw() override;
	void Update(float deltaTime) override;

	void OnSliderHeld();
	float GetSliderPercent() { return sliderPercentage; }
	bool IsBeingHeld() { return isBeingHeld; }
};

