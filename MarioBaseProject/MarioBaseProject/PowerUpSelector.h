#pragma once
#include "SceneObject.h"

class PowerUpDropTile;
class UIButton;

class PowerUpSelector : public SceneObject
{
	UIButton* noneButton;
	UIButton* shroomButton;
	UIButton* firePowerButton;

	PowerUpDropTile* selectedTile;

	void ChangePowerUp(PowerUpType powerType);
public:
	PowerUpSelector(Vector2D position, std::string path);
	~PowerUpSelector();
	void Draw() override;
	void Update(float deltaTime) override;

	void BeginChange(PowerUpDropTile* obj);
	
	void OnNoneButtonPressed();
	void OnPlatButtonPressed();
	void OnBlockPressed();

	static const float cSelectorWidth;
};

