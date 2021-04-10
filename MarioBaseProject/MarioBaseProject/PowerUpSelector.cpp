#include "PowerUpSelector.h"
#include "UIButton.h"
#include "Texture2D.h"
#include "Constants.h"
#include "PowerUpDropTile.h"

const float PowerUpSelector::cSelectorWidth = 288.f;

PowerUpSelector::PowerUpSelector(Vector2D position, std::string path) : SceneObject(position, path)
{
	SetVisibility(false);

	int buttonTextureWidth = texture->GetWidth() / 3;
	noneButton = new UIButton(Vector2D(), Rect2D(0, 0, TILE_SIZE, texture->GetHeight()), texture, true);
	shroomButton = new UIButton(Vector2D(), Rect2D(32.f, 0.f, TILE_SIZE, texture->GetHeight()), texture, true);
	firePowerButton = new UIButton(Vector2D(), Rect2D(64.f, 0.f, TILE_SIZE, texture->GetHeight()), texture, true);

	noneButton->onPressedCallback = std::bind(&PowerUpSelector::OnNoneButtonPressed, this);
	shroomButton->onPressedCallback = std::bind(&PowerUpSelector::OnPlatButtonPressed, this);
	firePowerButton->onPressedCallback = std::bind(&PowerUpSelector::OnBlockPressed, this);
}

PowerUpSelector::~PowerUpSelector()
{
	selectedTile = nullptr;
	
	delete firePowerButton;
	delete shroomButton;
	delete noneButton;
}

void PowerUpSelector::Draw()
{
	if (selectedTile != nullptr)
	{
		noneButton->Draw();
		shroomButton->Draw();
		firePowerButton->Draw();
	}
}

void PowerUpSelector::Update(float deltaTime)
{
	noneButton->Update(deltaTime);
	shroomButton->Update(deltaTime);
	firePowerButton->Update(deltaTime);
}

void PowerUpSelector::BeginChange(PowerUpDropTile* obj)
{
	if (obj == nullptr)
		return;
	
	selectedTile = obj;
	SetVisibility(true);

	Vector2D objPos = obj->GetPosition();
	objPos.y -= 32.f;

	noneButton->SetPosition(Vector2D(objPos.x - 32.f, objPos.y));
	shroomButton->SetPosition(objPos);
	firePowerButton->SetPosition(Vector2D(objPos.x + 32.f, objPos.y));
}

void PowerUpSelector::ChangePowerUp(PowerUpType powerType)
{
	if (selectedTile != nullptr)
		selectedTile->ChangePowerUp(powerType);
	
	selectedTile = nullptr;
	SetVisibility(false);
}

void PowerUpSelector::OnNoneButtonPressed()
{
	ChangePowerUp(POWER_UP_NONE);
}

void PowerUpSelector::OnPlatButtonPressed()
{
	ChangePowerUp(SUPER_SHROOM);
}

void PowerUpSelector::OnBlockPressed()
{
	ChangePowerUp(FIRE_FLOWER);
}