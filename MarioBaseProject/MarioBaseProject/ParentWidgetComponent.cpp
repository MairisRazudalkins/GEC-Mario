#include "ParentWidgetComponent.h"

ParentWidgetComponent::ParentWidgetComponent(Rect2D rect) : WidgetComponent(rect)
{
	
}

ParentWidgetComponent::~ParentWidgetComponent()
{
	for (int i = 0; i < vector::size(); i++)
	{
		delete vector::at(i);
	}
}

void ParentWidgetComponent::Update(float deltaTime)
{
	for (int i = 0; i < GetNumOfChildren(); i++)
	{
		GetChildAt(i)->Draw();
	}
}

void ParentWidgetComponent::Draw()
{
	for (int i = 0; i < GetNumOfChildren(); i++)
	{
		GetChildAt(i)->Draw();
	}
}

void ParentWidgetComponent::AddChild(WidgetComponent* widget)
{
	push_back(widget);
}

void ParentWidgetComponent::RemoveChildAt(int index)
{
	vector::erase(vector::begin() + index - 1);
}

int ParentWidgetComponent::GetNumOfChildren()
{
	return vector::size();
}

WidgetComponent* ParentWidgetComponent::GetChildAt(int index)
{
	return index > -1 && index < vector::size() ? vector::at(index) : nullptr; // make sure index is within the size of vector;
}
