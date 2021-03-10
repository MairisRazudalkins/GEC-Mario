#pragma once
#include "SceneObject.h"

class UIButton;

class CollisionSelector : public SceneObject
{
	UIButton* collisionNoneButton;
	UIButton* collisionPlatButton;
	UIButton* collisionBlockButton;

	SceneObject* selectedTile;

	void ChangeTileCollision(CollisionType colType);
public:
	CollisionSelector(Vector2D position, std::string path);
	~CollisionSelector();
	void Draw() override;
	void Update(float deltaTime) override;

	void BeginChange(SceneObject* obj);
	
	void OnNoneButtonPressed();
	void OnPlatButtonPressed();
	void OnBlockPressed();

	static const float cSelectorWidth;
};

