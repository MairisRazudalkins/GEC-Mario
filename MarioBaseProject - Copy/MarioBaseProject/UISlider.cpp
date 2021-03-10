#include "UISlider.h"
#include "Input.h"
#include "Texture2D.h"
#include "UIButton.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "Utility.h"

UISlider::UISlider(Vector2D position, float sliderWidth) : SceneObject(position, "Images/UISliderBG.png")
{
	sliderButton = new UIButton(Vector2D(position.x, position.y), "Images/UISliderButton.png");
	sliderButton->onHeldCallback = std::bind(&UISlider::OnSliderHeld, this);
	sliderButton->SetSrcRect(Rect2D(0, 0, TILE_SIZE, TILE_SIZE));
	sliderButton->SetPosition(Vector2D(position.x, position.y - sliderButton->GetSrcRect().height / 3));

	SetSrcRect(Rect2D(0, 0, sliderWidth, texture->GetHeight()));
}

UISlider::~UISlider()
{
	delete sliderButton;
}

void UISlider::Draw()
{
	texture->DrawToScreen(srcRect, Rect2D(position.x, position.y, srcRect.width, srcRect.height));
	sliderButton->Draw();
}

void UISlider::Update(float deltaTime)
{
	isBeingHeld = false;
	sliderButton->Update(deltaTime);
}

void UISlider::OnSliderHeld()
{
	isBeingHeld = true;
	
	float mousePosX = Input::GetMousePos().x;
	Vector2D newPos = Vector2D(mousePosX - sliderButton->GetSrcRect().width / 2, sliderButton->GetPosition().y);

	SDL_WarpMouseInWindow(ScreenManager::GetWindow(), mousePosX, newPos.y + (sliderButton->GetSrcRect().height / 2));
	
	if (newPos.x <= position.x)
	{
		newPos.x = position.x;
		SDL_WarpMouseInWindow(ScreenManager::GetWindow(), newPos.x + sliderButton->GetSrcRect().width / 2, newPos.y + (sliderButton->GetSrcRect().height / 2));
	}
	else if (newPos.x + sliderButton->GetSrcRect().width >= position.x + GetSrcRect().width)
	{
		newPos.x = (position.x + GetSrcRect().width) - sliderButton->GetSrcRect().width;
		SDL_WarpMouseInWindow(ScreenManager::GetWindow(), newPos.x + sliderButton->GetSrcRect().width / 2, newPos.y + (sliderButton->GetSrcRect().height / 2));
	}
	
	sliderButton->SetPosition(newPos);
	sliderPercentage = Utils::Clamp((newPos.x - position.x) / (GetSrcRect().width - sliderButton->GetSrcRect().width), 0.f, 1.f);
}
