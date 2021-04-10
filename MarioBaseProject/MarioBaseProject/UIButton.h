#pragma once
#include <functional>
#include "SceneObject.h"

class UIButton : public SceneObject
{
	bool shouldDrawToWorld;
	
public:
	UIButton(Vector2D position, std::string path, bool drawToWorld = false);
	UIButton(Vector2D position, Rect2D srcRect, Texture2D* texture, bool drawToWorld = false);
	void Draw() override;
	void Update(float deltaTime) override;

	std::function<void(void)> onPressedCallback;
	std::function<void(void)> onHeldCallback;
	
	void OnPressed();
	void OnHeld();
};