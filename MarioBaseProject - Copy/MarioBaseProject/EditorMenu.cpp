#include "EditorMenu.h"
#include "Collisions.h"
#include "Input.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Map.h"
#include "ScreenManager.h"
#include "UIButton.h"
#include "UISlider.h"
#include "CollisionSelector.h"

EditorMenu::EditorMenu(Map* map) : SceneObject(Vector2D(0, EDITOR_SCREEN_HEIGHT - (EDITOR_SCREEN_HEIGHT - SCREEN_HEIGHT)), "Images/SpriteSheet.png")
{
	this->map = map;
	
	spriteSelector = new Texture2D();
	spriteSelector->LoadTextureFromFile("Images/SpriteSelector.png");

	collisionSelector = new CollisionSelector(Vector2D((SCREEN_WIDTH / 2) - CollisionSelector::cSelectorWidth / 2, SCREEN_HEIGHT), "Images/UICollisionButtons.png");
	textureSlider = new UISlider(Vector2D(0, position.y + texture->GetHeight() + 8.f), SPRITE_SHEET_DISPLAY_LENGTH);
	levelSlider = new UISlider(Vector2D((SCREEN_WIDTH / 2) - (600.f / 2), 10.f), 640.f);
}

EditorMenu::~EditorMenu()
{
	map = nullptr;
	
	delete spriteSelector;
	spriteSelector = nullptr;

	delete textureSlider;
	textureSlider = nullptr;

	delete levelSlider;
	levelSlider = nullptr;

	delete collisionSelector;
	collisionSelector = nullptr;
}

void EditorMenu::Update(float deltaTime)
{
	if (collisionSelector->IsVisible())
	{
		collisionSelector->Update(deltaTime);
		return;
	}

	levelSlider->Update(deltaTime);
	textureSlider->Update(deltaTime);
	
	Vector2D mousePos = Input::GetMousePos();
	
	selectorPos.x = (int)(mousePos.x / TILE_SIZE) * TILE_SIZE;
	selectorPos.y = (int)(mousePos.y / TILE_SIZE) * TILE_SIZE;

	if (levelSlider->IsBeingHeld())
	{
		float camXPos = (int)((levelSlider->GetSliderPercent() * (map->GetLength() - SCREEN_WIDTH)) / TILE_SIZE) * TILE_SIZE;
		ScreenManager::SetCameraPos(Vector2D(camXPos, 0.f));
	}	
	else if (Input::IsLeftMouseDown())
	{
		if (Collisions::GetInst()->Box(Rect2D(selectorPos.x, selectorPos.y, 0, 0), Rect2D(GetPosition().x, GetPosition().y, texture->GetWidth(), texture->GetHeight())))
			selectedSpriteRect = Rect2D(selectorPos.x + spriteSheetXPos, selectorPos.y - SCREEN_HEIGHT, TILE_SIZE, TILE_SIZE);
		else
			PlaceTile();
	}
	else if (Input::IsRightMouseDown())
	{
		Vector2D camPos = ScreenManager::GetCameraPos();
		collisionSelector->BeginChange(map->GetTileAt((selectorPos.x + camPos.x) / TILE_SIZE, (selectorPos.y + camPos.y) / TILE_SIZE));
	}
	else if (Input::IsLeftMouseHeld())
	{
		if (!Collisions::GetInst()->Box(Rect2D(selectorPos.x, selectorPos.y, 0, 0), Rect2D(GetPosition().x, GetPosition().y, texture->GetWidth(), texture->GetHeight())))
			PlaceTile();
	}
}

void EditorMenu::Draw()
{
	if (collisionSelector->IsVisible())
	{
		collisionSelector->Draw();
		return;
	}
	
	if ((selectorPos.y < SCREEN_HEIGHT && !levelSlider->IsBeingHeld()) && (selectorPos.y))	// render selected Tile
		texture->DrawToScreen(Rect2D(selectedSpriteRect.x, selectedSpriteRect.y, TILE_SIZE, TILE_SIZE), Rect2D(selectorPos.x, selectorPos.y, TILE_SIZE, TILE_SIZE));

	spriteSheetXPos = (int)((texture->GetWidth() - SPRITE_SHEET_DISPLAY_LENGTH) * textureSlider->GetSliderPercent() / TILE_SIZE ) * TILE_SIZE;
	texture->DrawToScreen(Rect2D(spriteSheetXPos, 0, SPRITE_SHEET_DISPLAY_LENGTH, texture->GetHeight()), Rect2D(GetPosition().x, GetPosition().y, SPRITE_SHEET_DISPLAY_LENGTH, texture->GetHeight()));

	if (selectorPos.y < 576 && !levelSlider->IsBeingHeld())
		spriteSelector->DrawToScreen(selectorPos);
	
	textureSlider->Draw();
	levelSlider->Draw();
}

void EditorMenu::PlaceTile()
{
	Vector2D mousePos = Input::GetMousePos();
	Vector2D camPos = ScreenManager::GetCameraPos();
	
	int tileX = (mousePos.x + camPos.x) / TILE_SIZE, tileY = (mousePos.y + camPos.y) / TILE_SIZE;
	SceneObject* obj = map->GetTileAt(tileX, tileY);

	if (obj != nullptr)
		obj->SetSrcRect(selectedSpriteRect);
	else
		map->ChangeTileAt(tileX, tileY, new SceneObject(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y), selectedSpriteRect, texture));
}