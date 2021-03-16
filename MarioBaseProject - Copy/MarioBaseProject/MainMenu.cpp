#include "MainMenu.h"
#include "ScreenManager.h"
#include "Input.h"

MainMenu::MainMenu(ScreenManager* screenManager) : SceneObject(Vector2D(), "Images/MainMenu.png")
{
	this->screenManager = screenManager;
	
	selectorIndicator = new Texture2D();
	selectorIndicator->LoadTextureFromFile("Images/MenuSelector.png");
}

MainMenu::~MainMenu()
{
	delete selectorIndicator;
}

void MainMenu::Update(float deltaTime)
{
	if (Input::WasKeyDown(Key_UP) || Input::WasKeyDown(Key_W))
		isPlaySelected = true;
	else if (Input::WasKeyDown(Key_DOWN) || Input::WasKeyDown(Key_S))
		isPlaySelected = false;

	if (Input::WasKeyDown(Key_E))
		screenManager->ChangeScreen(isPlaySelected ? SCREEN_LEVEL : SCREEN_EDITOR, "TestMap.txt");
}

void MainMenu::Draw()
{
	texture->DrawToScreen(Vector2D());
	selectorIndicator->DrawToScreen(Vector2D(330.f, isPlaySelected ? 260.f : 295.f));
}
