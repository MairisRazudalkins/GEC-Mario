#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "Commons.h"

class SceneObject;
class CharacterMario;

class Map : public GameObject
{
	std::vector<std::vector<SceneObject*>>* sceneObjects;
	std::string backgroundName;
	Texture2D* backgroundTexture;
	Texture2D* collisionViewTexture;
	
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
	
	static void LoadObject(std::string obj, int xPos, int yPos);
};

