#include "ScoreUI.h"
#include "TextUi.h"
#include "GameLevel.h"
#include "ScreenManager.h"

ScoreUI::ScoreUI(GameLevel* level, Vector2D position, std::string path) : SceneObject(position, path)
{
	this->level = level;
	timeText = new TextUi(Vector2D(position.x + 252, position.y + 26), SDL_Color() = { 255, 255, 255, 255 }, std::to_string(level->GetGameTime()));
	scoreText = new TextUi(Vector2D(position.x + 106, position.y + 26), SDL_Color() = { 255, 255, 255, 255 }, std::to_string(level->GetScore()));
	UpdateScore(level->GetScore());
}

ScoreUI::~ScoreUI()
{
	delete timeText;
	delete scoreText;
}

void ScoreUI::Draw()
{
	texture->DrawToScreen(position);
	timeText->Draw();
	scoreText->Draw();
}

void ScoreUI::Update(float deltaTime)
{
	
}

void ScoreUI::UpdateTime(int time)
{
	timeText->ChangeText(std::to_string(time));
}

void ScoreUI::UpdateScore(int score)
{
	int tScore = score;
	
	int count = 0;
	
	while (score != 0)
	{
		score = score / 10;
		count++;
	}

	scoreText->ChangeText(std::string(7 - (count == 0 ? 0 : count - 1), '0').append(std::to_string(tScore)));
}