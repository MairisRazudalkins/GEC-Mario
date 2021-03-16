#pragma once
#include "SceneObject.h"

class UIButton;
class CollisionSelector;
class UISlider;
class Map;

#define SPRITE_SHEET_DISPLAY_LENGTH 576

class EditorMenu : public SceneObject
{
	Map* map;

	Texture2D* customTileTexture;
	Rect2D customTileRect;
	CustomPlacementTileType customTileType;
	CollisionType collisionType;

	Texture2D* optionsTexture;
	UIButton* deleteButton;
	UIButton* collisionButton;
	UIButton* startPosButton;
	UIButton* endPosButton;

	Texture2D* spriteSelector;
	Rect2D selectedSpriteRect;
	Vector2D selectorPos;

	CollisionSelector* collisionSelector;
	UISlider* textureSlider;
	UISlider* levelSlider;

	float spriteSheetXPos = 0.f;
	
public:
	EditorMenu(Map* map);
	~EditorMenu();
	
	void Update(float deltaTime) override;
	void Draw() override;
	void PlaceTile();

	void OnDeleteButtonPressed();
	void OnCollisionButtonPressed();
	void OnStartPosButtonPressed();
	void OnEndPosButtonPressed();
};