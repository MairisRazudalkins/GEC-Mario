#include "UIButton.h"
#include "Collisions.h"
#include "Input.h"
#include "Texture2D.h"


UIButton::UIButton(Vector2D position, std::string path) : SceneObject(position, path)
{
	
}

UIButton::UIButton(Vector2D position, Rect2D srcRect, Texture2D* texture) : SceneObject(position, srcRect, texture)
{
	
}

void UIButton::Draw()
{
	texture->DrawToScreen(GetSrcRect(), Rect2D(position.x, position.y, GetSrcRect().width, GetSrcRect().height));
}

void UIButton::Update(float deltaTime)
{
	Vector2D mousePos = Input::GetMousePos();

	
	if (Input::IsLeftMouseHeld()) // This is a weird but had to do it to fix an issue.
	{
		if (Collisions::Box(Rect2D(mousePos.x, mousePos.y, 0, 0), Rect2D(position.x, position.y, GetSrcRect().width, GetSrcRect().height)))
			OnHeld();
	}
	
	if (Input::IsLeftMouseDown())
	{
		if (Collisions::Box(Rect2D(mousePos.x, mousePos.y, 0, 0), Rect2D(position.x, position.y, GetSrcRect().width, GetSrcRect().height)))
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
