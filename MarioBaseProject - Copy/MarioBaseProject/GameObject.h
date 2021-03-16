#pragma once

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;
	
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

