#pragma once

class Texture2D;

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;
	
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

