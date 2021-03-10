#pragma once
#include "Commons.h"

class WidgetComponent
{
	WidgetComponent* parent;
	Rect2D rect;
	
public:
	WidgetComponent(Rect2D rect) { this->rect = rect; }
	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetPosition(Vector2D newPos);
	Vector2D GetPosition();
	
	static Anchor ScreenPosToAnchor(Vector2D screenPos);
	static Vector2D AnchorToScreenPos(Anchor anchor);
};