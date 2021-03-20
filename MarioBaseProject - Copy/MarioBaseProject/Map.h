#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "Commons.h"
#include "AudioManager.h"

class FinishPoint;
class SceneObject;
class CharacterMario;
class Character;
class Texture2D;

class Map : public GameObject
{
	CharacterMario* mario;
	FinishPoint* finishPoint;
	
	std::vector<std::vector<SceneObject*>>* sceneObjects;
	std::vector<Character*>* enemies;
	std::string backgroundName;
	
	Texture2D* backgroundTexture;
	Texture2D* collisionViewTexture;

	Vector2D startPos;
	Vector2D endPos;

	Mix_Music* levelMusic;
	
	int mapLength;

	static CharacterMario* LoadMario(Vector2D pos);

public:
	Map(std::string mapName, bool isEditing = false);
	~Map();

	void Draw() override;
	void Update(float deltaTime) override;

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

	CharacterMario* GetMario() { return mario; }
	
	void LoadCustomTile(CustomPlacementTileType tileType, Vector2D pos, Rect2D srcRect = Rect2D(), int colIndex = 0, int index = 0);
	void AddEnemy(Character* enemy);
	
	const std::string levelName;
	const bool isEditing = false;
};