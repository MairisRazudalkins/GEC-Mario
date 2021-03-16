#pragma once
#include <string>
#include "GameObject.h"

class Map;
class SDL_Renderer;

class BaseLevel : public GameObject
{
	virtual bool SetupLevel();
	
protected:
	SDL_Renderer* renderer;
	Map* map;
	std::string currentMapName;
	
public:
	BaseLevel(SDL_Renderer* renderer, const std::string& mapName);
	~BaseLevel();

	void Draw() override;
	void Update(float deltaTime) override;
	int GetCurMapLength();
};