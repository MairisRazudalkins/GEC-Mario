#pragma once
#include <string>
#include "GameObject.h"

class Map;
class SDL_Renderer;

class BaseLevel : public GameObject
{
	
protected:
	virtual void SetupLevel();
	
	SDL_Renderer* renderer;
	std::string currentMapName;
	Map* map;
	
public:
	BaseLevel(SDL_Renderer* renderer, const std::string& mapName);
	~BaseLevel();

	void Draw() override;
	void Update(float deltaTime) override;
	int GetCurMapLength();
	bool GetIsEditor();
};