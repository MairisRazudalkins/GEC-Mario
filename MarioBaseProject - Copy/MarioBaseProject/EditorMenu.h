#pragma once
#include "SceneObject.h"

class CollisionSelector;
class UISlider;
class Map;

#define SPRITE_SHEET_DISPLAY_LENGTH 576

class EditorMenu : public SceneObject
{
	Map* map;

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
};

