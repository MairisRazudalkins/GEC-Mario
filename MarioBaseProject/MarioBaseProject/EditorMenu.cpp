#include "EditorMenu.h"
#include "CharacterGoomba.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "Input.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Map.h"
#include "ScreenManager.h"
#include "UIButton.h"
#include "UISlider.h"
#include "PowerUpSelector.h"
#include "PowerUpDropTile.h"

EditorMenu::EditorMenu(Map* map) : SceneObject(Vector2D(0, EDITOR_SCREEN_HEIGHT - (EDITOR_SCREEN_HEIGHT - SCREEN_HEIGHT)), "Images/SpriteSheet.png")
{
	this->map = map;
	customTileTexture = nullptr;
	customTileType = CustomPlacementTileType::TILE_NONE;
	collisionType = CollisionType::NONE;
	selectedSpriteRect.x = -1;
	
	this->SetSrcRect(Rect2D(0.f, 0.f, SPRITE_SHEET_DISPLAY_LENGTH, texture->GetHeight()));
	
	spriteSelector = new Texture2D();
	spriteSelector->LoadTextureFromFile("Images/SpriteSelector.png");

	optionsTexture = new Texture2D();
	optionsTexture->LoadTextureFromFile("Images/UIEditorOptionButtons.png");

	editorBGTexture = new Texture2D();
	editorBGTexture->LoadTextureFromFile("Images/EditorBG.png");
	
	powerUpSelector = new PowerUpSelector(Vector2D((SCREEN_WIDTH / 2) - PowerUpSelector::cSelectorWidth / 2, SCREEN_HEIGHT), "Images/UIPowerUpSelector.png");
	textureSlider = new UISlider(Vector2D(0, position.y + texture->GetHeight() + 8.f), SPRITE_SHEET_DISPLAY_LENGTH);
	levelSlider = new UISlider(Vector2D((SCREEN_WIDTH / 2) - (600.f / 2), 10.f), 640.f);

	deleteButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH, GetPosition().y), Rect2D(0, 0, 48.f, 48.f), optionsTexture);
	collisionButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH, GetPosition().y + 48.f), Rect2D(0, 48.f, 48.f, 48.f), optionsTexture);
	startPosButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH + 48.f, GetPosition().y), Rect2D(48.f, 0.f, 48.f, 48.f), optionsTexture);
	endPosButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH + 48.f, GetPosition().y + 48.f), Rect2D(48.f, 48.f, 48.f, 48.f), optionsTexture);
	goombaButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH + 96.f, GetPosition().y), Rect2D(96.f, 0.f, 48.f, 48.f), optionsTexture);
	koopaButton = new UIButton(Vector2D(SPRITE_SHEET_DISPLAY_LENGTH + 96.f, GetPosition().y + 48.f), Rect2D(96.f, 48.f, 48.f, 48.f), optionsTexture);

	deleteButton->onPressedCallback = std::bind(&EditorMenu::OnDeleteButtonPressed , this);
	collisionButton->onPressedCallback = std::bind(&EditorMenu::OnCollisionButtonPressed, this);
	startPosButton->onPressedCallback = std::bind(&EditorMenu::OnStartPosButtonPressed, this);
	endPosButton->onPressedCallback = std::bind(&EditorMenu::OnEndPosButtonPressed, this);
	goombaButton->onPressedCallback = std::bind(&EditorMenu::OnGoombaButtonPressed, this);
	koopaButton->onPressedCallback = std::bind(&EditorMenu::OnKoopaButtonPressed, this);
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

	delete powerUpSelector;
	powerUpSelector = nullptr;

	delete deleteButton;
	deleteButton = nullptr;

	delete collisionButton;
	collisionButton = nullptr;
	
	delete startPosButton;
	startPosButton = nullptr;

	delete endPosButton;
	endPosButton = nullptr;
	
	delete goombaButton;
	startPosButton = nullptr;

	delete koopaButton;
	endPosButton = nullptr;
}

void EditorMenu::Update(float deltaTime)
{
	if (powerUpSelector->IsVisible())
	{
		powerUpSelector->Update(deltaTime);
		return;
	}

	levelSlider->Update(deltaTime);
	textureSlider->Update(deltaTime);

	deleteButton->Update(deltaTime);
	collisionButton->Update(deltaTime);
	startPosButton->Update(deltaTime);
	endPosButton->Update(deltaTime);
	goombaButton->Update(deltaTime);
	koopaButton->Update(deltaTime);
	
	Vector2D mousePos = Input::GetMousePos();
	
	selectorPos.x = (int)(mousePos.x / TILE_SIZE) * TILE_SIZE;
	selectorPos.y = (int)(mousePos.y / TILE_SIZE) * TILE_SIZE;

	if (levelSlider->IsBeingHeld())
	{
		float camXPos = (int)((levelSlider->GetSliderPercent() * (map->GetLength() - SCREEN_WIDTH)) / TILE_SIZE) * TILE_SIZE;
		ScreenManager::GetInst()->SetCameraPos(Vector2D(camXPos, 0.f));
	}	
	else if (Input::IsLeftMouseDown())
	{
		if (Collisions::Box(Rect2D(selectorPos.x + 1, selectorPos.y + 1, 0, 0), Rect2D(GetPosition().x, GetPosition().y, GetSrcRect().width, GetSrcRect().height)))
		{
			selectedSpriteRect = Rect2D(selectorPos.x + spriteSheetXPos, selectorPos.y - SCREEN_HEIGHT, TILE_SIZE, TILE_SIZE);
			customTileTexture = nullptr;
			customTileType = TILE_NONE;
		}
		else if (Collisions::Box(Rect2D(selectorPos.x + 1, selectorPos.y + 1, 0, 0), Rect2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)))
		{
			PlaceTile();
		}
	}
	else if (Input::IsRightMouseDown())
	{
		Vector2D camPos = ScreenManager::GetInst()->GetCameraPos();

		SceneObject* obj = map->GetTileAt((selectorPos.x + camPos.x) / TILE_SIZE, (selectorPos.y + camPos.y) / TILE_SIZE);
		
		if (obj != nullptr && obj->GetTag() == "PowerUpTile")
		{
			PowerUpDropTile* powerUpTile = (PowerUpDropTile*)obj;
			powerUpSelector->BeginChange(powerUpTile);
		}
	}
	else if (Input::IsLeftMouseHeld())
	{
		if (Collisions::Box(Rect2D(selectorPos.x + 1, selectorPos.y + 1, 0, 0), Rect2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)))
			PlaceTile();
	}

	Vector2D cameraPos = ScreenManager::GetInst()->GetCameraPos();

	if (Input::IsKeyDown(Key_D))
	{
		ScreenManager::GetInst()->SetCameraPos(Vector2D(cameraPos.x + TILE_SIZE, 0));

		if (cameraPos.x + SCREEN_WIDTH >= map->GetLength()) // TODO: replace SCREEN_WIDTH * 1.5 with level length when maps done!!
			ScreenManager::GetInst()->SetCameraPos(Vector2D(map->GetLength() - SCREEN_WIDTH, 0.f));
	}
	else if (Input::IsKeyDown(Key_A))
	{
		ScreenManager::GetInst()->SetCameraPos(Vector2D(cameraPos.x - TILE_SIZE, 0));

		if (cameraPos.x <= 0)
			ScreenManager::GetInst()->SetCameraPos(Vector2D(0.f, 0.f));
	}
}

void EditorMenu::Draw()
{
	editorBGTexture->DrawToScreen(Rect2D(0.f, 0.f, SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT - SCREEN_HEIGHT), Rect2D(0, SCREEN_HEIGHT, SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT - SCREEN_HEIGHT));
	
	if (powerUpSelector->IsVisible())
	{
		powerUpSelector->Draw();
	}

	spriteSheetXPos = (int)((texture->GetWidth() - SPRITE_SHEET_DISPLAY_LENGTH) * textureSlider->GetSliderPercent() / TILE_SIZE) * TILE_SIZE;
	texture->DrawToScreen(Rect2D(spriteSheetXPos, 0, SPRITE_SHEET_DISPLAY_LENGTH, texture->GetHeight()), GetDstRect());

	if (selectorPos.y < SCREEN_HEIGHT && !levelSlider->IsBeingHeld() && customTileType != CustomPlacementTileType::TILE_DELETE)
	{
		if (customTileTexture != nullptr)
			customTileTexture->DrawToScreen(customTileRect, Rect2D(selectorPos.x, selectorPos.y, TILE_SIZE, TILE_SIZE));
		else // render selected Tile
			texture->DrawToScreen(selectedSpriteRect, Rect2D(selectorPos.x, selectorPos.y, TILE_SIZE, TILE_SIZE));
	}

	if (!levelSlider->IsBeingHeld() && (Collisions::Box(GetDstRect(), Rect2D(selectorPos.x + 1, selectorPos.y + 1, 0, 0)) || Collisions::Box(Rect2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Rect2D(selectorPos.x + 1, selectorPos.y + 1, 0, 0)) ) )
		spriteSelector->DrawToScreen(selectorPos);

	optionsTexture->DrawToWorld(Rect2D(48.f, 128.f, TILE_SIZE, TILE_SIZE), Rect2D(map->GetStartPos().x, map->GetStartPos().y, TILE_SIZE, TILE_SIZE));
	optionsTexture->DrawToWorld(Rect2D(48.f, 96.f, TILE_SIZE, TILE_SIZE), Rect2D(map->GetEndPos().x, map->GetEndPos().y, TILE_SIZE, TILE_SIZE));
	
	textureSlider->Draw();
	levelSlider->Draw();

	deleteButton->Draw();
	collisionButton->Draw();
	startPosButton->Draw();
	endPosButton->Draw();
	goombaButton->Draw();
	koopaButton->Draw();
}

void EditorMenu::PlaceTile()
{
	Vector2D mousePos = Input::GetMousePos();
	Vector2D camPos = ScreenManager::GetInst()->GetCameraPos();
	
	int tileX = (mousePos.x + camPos.x) / TILE_SIZE, tileY = (mousePos.y + camPos.y) / TILE_SIZE;

	if (customTileType == TILE_DELETE)
	{
		map->ChangeTileAt(tileX, tileY, nullptr);
		return;
	}
	
	if (customTileTexture != nullptr)
	{
		if (customTileType == TILE_START_POS)
			map->SetStartPos(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y));
		else if (customTileType == TILE_END_POS)
			map->SetEndPos(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y));
		else if (customTileType == TILE_GOOMBA)
			map->AddEnemy(new CharacterGoomba(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y), map, nullptr));
		else if (customTileType == TILE_KOOPA)
			map->AddEnemy(new CharacterKoopa(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y), map, nullptr));
		
		return;
	}

	if (selectedSpriteRect.x != -1)
	{
		SceneObject* obj = map->GetTileAt(tileX, tileY);

		if (obj != nullptr)
		{
			obj->SetSrcRect(selectedSpriteRect);
			obj->SetCollisionType(collisionType);
		}
		else
			map->ChangeTileAt(tileX, tileY, new SceneObject(Vector2D(selectorPos.x + camPos.x, selectorPos.y + camPos.y), selectedSpriteRect, texture, collisionType));
	}
}

void EditorMenu::OnDeleteButtonPressed()
{
	customTileTexture = nullptr;
	customTileType = TILE_DELETE;
}

void EditorMenu::OnCollisionButtonPressed()
{
	customTileTexture = nullptr;
	customTileType = TILE_COLLISION;

	int collisionTypeIndex = (int)(collisionType) + 1;

	if (collisionTypeIndex > 2)
		collisionTypeIndex = 0;
	
	collisionType = (CollisionType)(collisionTypeIndex);
	collisionButton->SetSrcRect(Rect2D(0.f, 48.f + (collisionTypeIndex * 48.f), 48.f, 48.f));
}

void EditorMenu::OnStartPosButtonPressed()
{
	customTileTexture = optionsTexture;
	customTileRect = Rect2D(48.f, 128.f, TILE_SIZE, TILE_SIZE);
	customTileType = TILE_START_POS;
}

void EditorMenu::OnEndPosButtonPressed()
{
	customTileTexture = optionsTexture;
	customTileRect = Rect2D(48.f, 96.f, TILE_SIZE, TILE_SIZE);
	customTileType = TILE_END_POS;
}

void EditorMenu::OnGoombaButtonPressed()
{
	customTileTexture = optionsTexture;
	customTileRect = Rect2D(48.f, 160.f, TILE_SIZE, TILE_SIZE);
	customTileType = TILE_GOOMBA;
}

void EditorMenu::OnKoopaButtonPressed()
{
	customTileTexture = optionsTexture;
	customTileRect = Rect2D(80.f, 96.f, TILE_SIZE, 52.f);
	customTileType = TILE_KOOPA;
}