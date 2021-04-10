#pragma once
#include "SceneObject.h"

class ScreenManager;

class MainMenu : public SceneObject
{
	ScreenManager* screenManager;
	Texture2D* selectorIndicator;
	bool isPlaySelected = true;
	
public:
	MainMenu(ScreenManager* screenManager);
	~MainMenu();
	void Update(float deltaTime) override;
	void Draw() override;
};
