#pragma once

#ifndef LEVELMAP;
#define LEVELMAP

#include "Constants.h"

class Texture2D;
class SDL_Renderer;
class Vector2D;

class LevelMap
{
	int** map;
	
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH], SDL_Renderer* renderer);
	~LevelMap();

	Texture2D *tiles[MAP_HEIGHT * MAP_WIDTH];
	
	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int h, unsigned int w, int newTileType);
	void Render();

	static Vector2D ScreenPosToGridPos(Vector2D pos);
};

#endif