#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "Commons.h"

class SceneObject;
class CharacterMario;
class Character;
class Texture2D;

class Map : public GameObject
{
	std::vector<std::vector<SceneObject*>>* sceneObjects;
	std::string backgroundName;
	Texture2D* backgroundTexture;
	Texture2D* collisionViewTexture;

	Vector2D startPos;
	Vector2D endPos;
	
	int mapLength;
	bool isEditing = false;

	static CharacterMario* LoadMario(Vector2D pos);

public:
	Map(std::string mapName);
	~Map();

	void Draw() override;
	void Update(float deltaTime) override;

	void SetIsEditing(bool isEditing);
	void ChangeLength(int newLength);
	void ChangeTileAt(int x, int y, SceneObject* newObj);
	int GetLength() { return mapLength; }
	
	SceneObject* GetTileAt(int x, int y);

	void SaveMap(std::string mapName);
	void LoadMap(std::string mapName);
	
	Vector2D GetStartPos() { return startPos; }
	void SetStartPos(Vector2D newStartPos) { startPos = newStartPos; }

	Vector2D GetEndPos() { return endPos; }
	void SetEndPos(Vector2D newEndPos) { endPos = newEndPos; }

	void LoadCustomTile(CustomPlacementTileType tileType, Vector2D pos, Rect2D srcRect = Rect2D(), int colIndex = 0);
};