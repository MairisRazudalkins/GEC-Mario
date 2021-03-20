#include <iostream>
#include <fstream>
#include "Map.h"
#include "CharacterGoomba.h"
#include "CharacterKoopa.h"
#include "SceneObject.h"
#include "Constants.h"
#include "ScreenManager.h"
#include "Texture2D.h"
#include "PowerUpDropTile.h"
#include "CharacterMario.h"
#include "FinishPoint.h"

Map::Map(std::string mapName, bool isEditing) : levelName(mapName), isEditing(isEditing)
{
	std::fstream inFile;
	inFile.open("Data/Maps/" + mapName);

	collisionViewTexture = new Texture2D();
	collisionViewTexture->LoadTextureFromFile("Images/UICollisionType.png");
	
	if (!inFile.is_open())
	{
		mapLength = SCREEN_WIDTH;
		backgroundName = "None";
		
		startPos = Vector2D(0, 0);
		endPos = Vector2D(TILE_SIZE, 0.f);

		mario = new CharacterMario(startPos, this);
		finishPoint = new FinishPoint(endPos, mario);
		sceneObjects = new std::vector<std::vector<SceneObject*>>(MAP_HEIGHT, std::vector<SceneObject*>(mapLength / TILE_SIZE));
		
		std::cout << "Failed to load map: " << "Data/Maps/" + mapName << "  Loaded empty map instead!\n";
		return;
	}
	
	LoadMap(mapName);

	if (!isEditing)
	{
		levelMusic = AudioManager::LoadMusic("Mario.mp3");
		AudioManager::PlayMusic(levelMusic);
	}
	
	inFile.close();
}

Map::~Map()
{
	Mix_FreeMusic(levelMusic);

	delete collisionViewTexture;
	collisionViewTexture = nullptr;
	
	delete backgroundTexture;
	backgroundTexture = nullptr;
	
	for (int i = 0; i < sceneObjects->size(); i++)
	{
		for (int j = 0; j < sceneObjects->at(i).size(); j++)
			delete sceneObjects->at(i).at(j);

		sceneObjects->at(i).erase(sceneObjects->at(i).begin());
	}

	sceneObjects->erase(sceneObjects->begin());

	for (int i = 0; i < enemies->size(); i++)
		delete enemies->at(i);

	enemies->erase(enemies->begin(), enemies->end());

	delete mario;
	mario = nullptr;

	delete finishPoint;
	finishPoint = nullptr;

}

void Map::Draw()
{
	if (backgroundTexture != nullptr)
		backgroundTexture->DrawToWorld(Rect2D(0, 0, mapLength, sceneObjects->size() * TILE_SIZE), Rect2D(0, 0, mapLength, sceneObjects->size() * TILE_SIZE));

	int xDrawPos = ((ScreenManager::GetInst()->GetCameraPos().x * TILE_SIZE) / TILE_SIZE) / TILE_SIZE;
	int xMaxDrawPos = ((xDrawPos + 1) + (SCREEN_WIDTH / TILE_SIZE)) > (mapLength / TILE_SIZE) ? (mapLength / TILE_SIZE) : (xDrawPos + 1) + (SCREEN_WIDTH / TILE_SIZE);
	
	for (int i = 0; i < sceneObjects->size(); i++) // optimize to draw only ones visible in camera view
	{
		for (int j = xDrawPos; j < xMaxDrawPos; j++)
		{
			SceneObject* obj = sceneObjects->at(i).at(j);
			
			if (obj != nullptr)
			{
				sceneObjects->at(i).at(j)->Draw();

				if (isEditing && obj->GetCollisionType() != CollisionType::NONE)
					collisionViewTexture->DrawToWorld(Rect2D(obj->GetCollisionType() == CollisionType::PLATFORM ? 0.f : 8.f, 0, 8, 10), Rect2D(obj->GetPosition().x, obj->GetPosition().y, 8, 10));
			}
		}
	}

	for (int i = 0; i < enemies->size(); i++)
	{
		Character* enemy = enemies->at(i);

		if (enemy != nullptr)
		{
			float xPos = enemy->GetPosition().x;

			if (xPos + enemy->GetSrcRect().width > xDrawPos * TILE_SIZE && xPos < xMaxDrawPos * TILE_SIZE)
				enemy->Draw();
		}
	}

	if (!isEditing)
	{
		finishPoint->Draw();
		mario->Draw();
	}

}

void Map::Update(float deltaTime)
{
	if (isEditing)
		return;
	
	int xDrawPos = ((ScreenManager::GetInst()->GetCameraPos().x * TILE_SIZE) / TILE_SIZE) / TILE_SIZE;
	int xMaxDrawPos = ((xDrawPos + 1) + (SCREEN_WIDTH / TILE_SIZE)) > (mapLength / TILE_SIZE) ? (mapLength / TILE_SIZE) : (xDrawPos + 1) + (SCREEN_WIDTH / TILE_SIZE);

	for (int i = 0; i < sceneObjects->size(); i++) // optimize to draw only ones visible in camera view
	{
		for (int j = xDrawPos; j < xMaxDrawPos; j++)
		{
			SceneObject* obj = sceneObjects->at(i).at(j);

			if (obj != nullptr)
				obj->Update(deltaTime);
		}
	}

	if (mario->IsAlive())
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			Character* enemy = enemies->at(i);

			if (enemy != nullptr)
			{
				float xPos = enemy->GetPosition().x;

				if (xPos + enemy->GetSrcRect().width > xDrawPos * TILE_SIZE && xPos < xMaxDrawPos * TILE_SIZE)
					enemy->Update(deltaTime);
			}
		}
	}
	
	if (!isEditing)
	{
		finishPoint->Update(deltaTime);

		if (ScreenManager::GetInst()->GetCurrentLevel() != nullptr)
			mario->Update(deltaTime);
	}
}

void Map::ChangeLength(int newLength)
{
	if (newLength < mapLength && newLength > SCREEN_WIDTH)
	{
		int numOfTiles = newLength / TILE_SIZE;
		
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = numOfTiles; j < sceneObjects->at(i).size(); j++)
			{
				if (sceneObjects->at(i).at(j) != nullptr)
				{
					delete sceneObjects->at(i).at(j);
					sceneObjects->at(i).at(j) = nullptr;
				}
			}
			sceneObjects->at(i).erase(sceneObjects->at(i).begin() + numOfTiles, sceneObjects->at(i).end());
		}
		std::cout << "SIZE CHANGED TO: " << MAP_HEIGHT << " " << sceneObjects->at(0).size() << std::endl;
	}
	else if (newLength > mapLength) // seems highly inefficient.
	{
		int	numOfColsToAdd = (newLength / TILE_SIZE) - (mapLength / TILE_SIZE);

		std::vector<std::vector<SceneObject*>>* objectsToAdd = new std::vector<std::vector<SceneObject*>>(sceneObjects->size(), std::vector<SceneObject*>(numOfColsToAdd));
		
		for (int i = 0; i < MAP_HEIGHT; i++)
			sceneObjects->at(i).insert(sceneObjects->at(i).end(), objectsToAdd->at(i).begin(), objectsToAdd->at(i).end());

		objectsToAdd->erase(objectsToAdd->begin());
	}
	
	std::cout << "SIZE CHANGED TO: " << MAP_HEIGHT << " " << sceneObjects->at(0).size() << std::endl;
	mapLength = newLength;
}

void Map::ChangeTileAt(int x, int y, SceneObject* newObj)
{
	if (y < sceneObjects->size() && y >= 0)
		if (x < sceneObjects->at(y).size() && x >= 0)
			sceneObjects->at(y).at(x) = newObj;
}

SceneObject* Map::GetTileAt(int x, int y)
{
	if (y < sceneObjects->size() && y >= 0)
		if (x < sceneObjects->at(y).size() && x >= 0)
			return sceneObjects->at(y).at(x);
	
	return nullptr;
}

void Map::SaveMap(std::string mapName)
{
	std::ofstream myFile;
	myFile.open("Data/Maps/" + mapName);
	std::cout << "SAVED TO: " << "Data/Maps/" << mapName << std::endl;

	myFile << mapLength << std::endl;
	myFile << backgroundName << std::endl;

	myFile << TILE_START_POS << " " << startPos.x << " " << startPos.y << std::endl;
	myFile << TILE_END_POS << " " << endPos.x << " " << endPos.y << std::endl;
	
	for (int i = 0; i < sceneObjects->size(); i++)
	{
		for (int j = 0; j < sceneObjects->at(i).size(); j++)
		{
			if (sceneObjects->at(i).at(j) == nullptr)
			{
				myFile << -1 << " | ";
				continue;
			}
			
			Rect2D objSrcRect = sceneObjects->at(i).at(j)->GetSrcRect();

			if (objSrcRect.x / TILE_SIZE == 30 && objSrcRect.y / TILE_SIZE == 2)
				myFile << objSrcRect.x / TILE_SIZE << " " << objSrcRect.y / TILE_SIZE << " " << ((PowerUpDropTile*)sceneObjects->at(i).at(j))->GetPowerType() << " | ";
			else
				myFile << objSrcRect.x / TILE_SIZE << " " << objSrcRect.y / TILE_SIZE <<  " " << sceneObjects->at(i).at(j)->GetCollisionType() << " | ";
		}

		myFile << std::endl;
	}

	myFile << std::endl;
	myFile << enemies->size();
	myFile << std::endl;
	
	for (int i = 0; i < enemies->size(); i++)
	{
		Character* enemy = enemies->at(i);

		CustomPlacementTileType tileType = enemy->GetTag() == "E Koopa" ? TILE_KOOPA : TILE_GOOMBA;
		myFile << enemy->GetPosition().x / TILE_SIZE << " " << enemy->GetPosition().y / TILE_SIZE << " " << (int)tileType << " | ";
	}

	myFile.close();	
}

void Map::LoadMap(std::string mapName) // this looks discusting
{
	int customTileType;
	Vector2D customTilePos;
	
	std::fstream inFile;
	inFile.open("Data/Maps/" + mapName);

	if (!inFile.is_open())
	{
		std::cout << "Failed to load map: Data/Maps" << mapName << std::endl;
		LoadMap(""); // load empty map
		return;
	}
	
	inFile >> mapLength;
	inFile >> backgroundName;

	inFile >> customTileType >> customTilePos.x >> customTilePos.y;
	LoadCustomTile((CustomPlacementTileType)customTileType, customTilePos);

	inFile >> customTileType >> customTilePos.x >> customTilePos.y;
	LoadCustomTile((CustomPlacementTileType)customTileType, customTilePos);
	
	backgroundTexture = new Texture2D();
	backgroundTexture->LoadTextureFromFile("Images/" + backgroundName);
	
	sceneObjects = new std::vector<std::vector<SceneObject*>>(MAP_HEIGHT, std::vector<SceneObject*>(mapLength / TILE_SIZE));

	int count = 0;
	
	for (int i = 0; i < sceneObjects->size(); i++)
	{
		for (int j = 0; j < sceneObjects->at(i).size(); j++)
		{
			count++;
			
			Rect2D* srcRect = nullptr;
			int colIndex = 0;
			std::string str;
			
			while (true)
			{
				inFile >> str;
				
				if (str == "|")
					break;

				if (str == "-1")
					continue;
				
				if (srcRect == nullptr)
					srcRect = new Rect2D(-TILE_SIZE, -TILE_SIZE, TILE_SIZE, TILE_SIZE);
				
				srcRect->x = std::stoi(str);
				inFile >> srcRect->y;
				inFile >> colIndex;

				if (srcRect->x == 30 && srcRect->y == 2)
				{
					LoadCustomTile(TILE_POWER_UP_DROPPER, Vector2D(j, i), Rect2D(srcRect->x * TILE_SIZE, srcRect->y * TILE_SIZE, TILE_SIZE, TILE_SIZE), colIndex);
					srcRect = nullptr;
					continue;
				}
				
				srcRect->x *= TILE_SIZE;
				srcRect->y *= TILE_SIZE;
			}

			if (srcRect != nullptr)
			{
				ChangeTileAt(j, i, new SceneObject(Vector2D(j * TILE_SIZE, i * TILE_SIZE), *srcRect, ScreenManager::GetInst()->GetTileMap(), (CollisionType)colIndex));
				srcRect = nullptr;
			}
		}
	}

	int numOfEnemies;
	inFile >> numOfEnemies;
	
	enemies = new std::vector<Character*>(numOfEnemies);
	
	for (int i = 0; i < numOfEnemies; i++)
	{
		Vector2D position;
		CustomPlacementTileType customTile;
		std::string str;
		
		while (true)
		{
			inFile >> str;
			
			if (str == "|")
				break;
	
			int tileType;
			position.x = std::stof(str);
			inFile >> position.y;
			inFile >> tileType;
	
			customTile = (CustomPlacementTileType)tileType;
		}
	
		LoadCustomTile(customTile, position, Rect2D(), 0, i);
	}
	
	inFile.close();
	
	std::cout << "LOADED: " << "Data/Maps/" << mapName << std::endl;
}

void Map::LoadCustomTile(CustomPlacementTileType tileType, Vector2D pos, Rect2D srcRect, int colIndex, int index)
{
	switch (tileType)
	{
	case TILE_START_POS:
		startPos = pos;
		mario = new CharacterMario(startPos, this);
		break;
	case TILE_END_POS:
		endPos = pos;
		finishPoint = new FinishPoint(endPos, mario);
		break;
	case TILE_POWER_UP_DROPPER:
		ChangeTileAt(pos.x, pos.y, new PowerUpDropTile(Vector2D(pos.x * TILE_SIZE, pos.y * TILE_SIZE), srcRect, ScreenManager::GetInst()->GetTileMap(), (PowerUpType)colIndex));
		break;
	case TILE_GOOMBA:
		enemies->at(index) = new CharacterGoomba(Vector2D(pos.x * TILE_SIZE, pos.y * TILE_SIZE), this, mario);
		break;
	case TILE_KOOPA:
		enemies->at(index) = new CharacterKoopa(Vector2D(pos.x * TILE_SIZE, pos.y * TILE_SIZE), this, mario);
		break;
	}
}

void Map::AddEnemy(Character* enemy)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if (enemies->at(i) != nullptr)
		{
			if (enemies->at(i)->GetPosition().x == enemy->GetPosition().x && enemies->at(i)->GetPosition().y == enemy->GetPosition().y)
			{
				delete enemies->at(i);

				enemies->at(i) = enemy;
				return;
			}
		}
	}
	
	enemies->push_back(enemy);
}