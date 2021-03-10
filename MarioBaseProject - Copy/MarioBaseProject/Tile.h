#pragma once
#include <string>

#include "GameObject.h"
class Tile : public GameObject
{
	Texture2D* texture;
	
public:
	Tile();
	~Tile();

	void Draw() override;

	static GameObject* LoadTile(const std::string tilePath);
};

