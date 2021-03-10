#pragma once
#include <functional>
#include "SceneObject.h"

class UIButton : public SceneObject
{
	
public:
	UIButton(Vector2D position, std::string path);
	UIButton(Vector2D position, Rect2D srcRect, Texture2D* texture);
	void Draw() override;
	void Update(float deltaTime) override;

	std::function<void(void)> onPressedCallback;
	std::function<void(void)> onHeldCallback;
	
	void OnPressed();
	void OnHeld();
};