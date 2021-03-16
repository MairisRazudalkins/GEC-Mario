#include "CollisionSelector.h"
#include "UIButton.h"
#include "Texture2D.h"
#include "Constants.h"

const float CollisionSelector::cSelectorWidth = 288.f;

CollisionSelector::CollisionSelector(Vector2D position, std::string path) : SceneObject(position, path)
{
	SetVisibility(false);

	int buttonTextureWidth = texture->GetWidth() / 3;
	collisionNoneButton = new UIButton(Vector2D(position.x, position.y), Rect2D(0, 0, buttonTextureWidth, texture->GetHeight()), texture);
	collisionPlatButton = new UIButton(Vector2D(position.x + buttonTextureWidth, position.y), Rect2D(buttonTextureWidth, 0, buttonTextureWidth, texture->GetHeight()), texture);
	collisionBlockButton = new UIButton(Vector2D(position.x + buttonTextureWidth * 2, position.y), Rect2D(buttonTextureWidth * 2, 0, buttonTextureWidth, texture->GetHeight()), texture);

	collisionNoneButton->onPressedCallback = std::bind(&CollisionSelector::OnNoneButtonPressed, this);
	collisionPlatButton->onPressedCallback = std::bind(&CollisionSelector::OnPlatButtonPressed, this);
	collisionBlockButton->onPressedCallback = std::bind(&CollisionSelector::OnBlockPressed, this);
}

CollisionSelector::~CollisionSelector()
{
	delete collisionBlockButton;
	delete collisionPlatButton;
	delete collisionNoneButton;
}

void CollisionSelector::Draw()
{
	texture->DrawToScreen(GetSrcRect(), Rect2D(position.x, position.y, cSelectorWidth, TILE_SIZE));
	collisionNoneButton->Draw();
	collisionPlatButton->Draw();
	collisionBlockButton->Draw();
}

void CollisionSelector::Update(float deltaTime)
{
	collisionNoneButton->Update(deltaTime);
	collisionPlatButton->Update(deltaTime);
	collisionBlockButton->Update(deltaTime);
}

void CollisionSelector::BeginChange(SceneObject* obj)
{
	if (obj == nullptr)
		return;
	
	selectedTile = obj;
	SetVisibility(true);
}

void CollisionSelector::ChangeTileCollision(CollisionType colType)
{
	if (selectedTile != nullptr)
		selectedTile->SetCollisionType(colType);
	
	selectedTile = nullptr;
	SetVisibility(false);
}

void CollisionSelector::OnNoneButtonPressed()
{
	ChangeTileCollision(CollisionType::NONE);
}

void CollisionSelector::OnPlatButtonPressed()
{
	ChangeTileCollision(PLATFORM);
}

void CollisionSelector::OnBlockPressed()
{
	ChangeTileCollision(BLOCK);
}