#include <SDL.h>
#include "LevelMap.h"

#include <iostream>

#include "Texture2D.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH], SDL_Renderer* renderer)
{
	this->map = new int* [MAP_HEIGHT];

	for (unsigned int i = 0; i < MAP_HEIGHT; i ++)
	{
		this->map[i] = new int[MAP_WIDTH];
	}

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			this->map[i][j] = map[i][j];

			if (this->map[i][j] == 1)
			{			
				Texture2D* texture = new Texture2D(renderer);
				texture->LoadTextureFromFile("Images/TestTile.png");
				
				tiles[i * MAP_WIDTH + j] = texture;
			}
		}
	}
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] map[i];
	}
	
	delete[] map;
}

int LevelMap::GetTileAt(unsigned h, unsigned w)
{
	
	return map[h][w];
}

void LevelMap::ChangeTileAt(unsigned h, unsigned w, int newTileType)
{
	map[h][w] = newTileType;
}

void LevelMap::Render()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			Texture2D* texture = tiles[i * MAP_WIDTH + j];
			
			if (texture != nullptr)
			{
				texture->Render(Vector2D(j * texture->GetWidth(), i * texture->GetHeight()));
			}
		}
	}
}

Vector2D LevelMap::ScreenPosToGridPos(Vector2D pos)
{
	return Vector2D((int)(pos.x / TILE_WIDTH), (int)(pos.y / TILE_WIDTH));
}
