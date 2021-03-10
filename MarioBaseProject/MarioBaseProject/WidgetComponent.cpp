#include "WidgetComponent.h"
#include "Constants.h"

void WidgetComponent::Update(float deltaTime)
{
}

void WidgetComponent::Draw()
{
}

void WidgetComponent::SetPosition(Vector2D newPos)
{
	if (parent != nullptr)
	{
		//Anchor parentMin = { parent->rect.x, parent->rect.y };
		//Anchor parentMax = { parent->rect.width, parent->rect.height };
		

		return;
	}

	Anchor anchorMin = ScreenPosToAnchor(newPos);

	rect.x = anchorMin.min;
	rect.y = anchorMin.max;
}

Vector2D WidgetComponent::GetPosition()
{
	return Vector2D(rect.x, rect.y);
}

Anchor WidgetComponent::ScreenPosToAnchor(Vector2D screenPos)
{
	return Anchor(screenPos.x / SCREEN_WIDTH, screenPos.y / SCREEN_HEIGHT);
}

Vector2D WidgetComponent::AnchorToScreenPos(Anchor anchor)
{
	return Vector2D(anchor.min * SCREEN_WIDTH, anchor.max * SCREEN_HEIGHT);
}