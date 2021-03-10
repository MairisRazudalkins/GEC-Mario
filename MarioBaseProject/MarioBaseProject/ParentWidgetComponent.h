#pragma once
#include <vector>
#include "WidgetComponent.h"

class ParentWidgetComponent : public WidgetComponent, private std::vector<WidgetComponent*>
{
	Vector2D* position;
	
public:
	ParentWidgetComponent(Rect2D rect);
	~ParentWidgetComponent();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	
	void AddChild(WidgetComponent* widget);
	void RemoveChildAt(int index);
	int GetNumOfChildren();
	WidgetComponent* GetChildAt(int index);
};

