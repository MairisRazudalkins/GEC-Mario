#pragma once
#include "SceneObject.h"

class GameLevel;
class TextUi;

class ScoreUI : public SceneObject
{
	GameLevel* level;
	
	TextUi* timeText;
	TextUi* scoreText;
	
public:
	ScoreUI(GameLevel* level, Vector2D position, std::string path);
	~ScoreUI();
	
	void Draw() override;
	void Update(float deltaTime) override;

	void UpdateTime(int time);
	void UpdateScore(int score);
};
