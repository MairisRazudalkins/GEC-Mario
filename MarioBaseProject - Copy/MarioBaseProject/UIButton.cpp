#include "UIButton.h"
#include "Collisions.h"
#include "Input.h"
#include "ScreenManager.h"
#include "Texture2D.h"

UIButton::UIButton(Vector2D position, std::string path, bool drawToWorld) : SceneObject(position, path)
{
	shouldDrawToWorld = drawToWorld;
}

UIButton::UIButton(Vector2D position, Rect2D srcRect, Texture2D* texture, bool drawToWorld) : SceneObject(position, srcRect, texture)
{
	shouldDrawToWorld = drawToWorld;
}

void UIButton::Draw()
{
	if (shouldDrawToWorld)
		texture->DrawToWorld(GetSrcRect(), Rect2D(position.x, position.y, GetSrcRect().width, GetSrcRect().height));
	else
		texture->DrawToScreen(GetSrcRect(), Rect2D(position.x, position.y, GetSrcRect().width, GetSrcRect().height));
}

void UIButton::Update(float deltaTime)
{
	Vector2D mousePos = Input::GetMousePos();

	Vector2D offset = shouldDrawToWorld ? ScreenManager::GetInst()->GetCameraPos() : Vector2D();

	
	if (Input::IsLeftMouseHeld())
	{
		if (Collisions::Box(Rect2D(mousePos.x, mousePos.y, 0, 0), Rect2D(position.x - offset.x, position.y - offset.y, GetSrcRect().width, GetSrcRect().height)))
			OnHeld();
	}
	
	if (Input::IsLeftMouseDown())
	{
		if (Collisions::Box(Rect2D(mousePos.x, mousePos.y, 0, 0), Rect2D(position.x - offset.x, position.y - offset.y, GetSrcRect().width, GetSrcRect().height)))
			OnPressed();
	}
}

void UIButton::OnPressed()
{
	if (onPressedCallback)
		onPressedCallback();
}

void UIButton::OnHeld()
{
	if (onHeldCallback)
		onHeldCallback();
}
