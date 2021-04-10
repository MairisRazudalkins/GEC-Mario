#pragma once
#include "BaseLevel.h"

class EditorMenu;

class LevelEditor : public BaseLevel
{
	void SetupLevel() override;
	
	EditorMenu* tileSelector;
	
public:
	LevelEditor(SDL_Renderer* renderer, const std::string& mapName);
	~LevelEditor();

	void Draw() override;
	void Update(float deltaTime) override;
};