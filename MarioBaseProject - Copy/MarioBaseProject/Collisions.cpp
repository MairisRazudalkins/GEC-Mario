#include <iostream>
#include "Collisions.h"
#include "Character.h"
#include "Commons.h"

Collisions* Collisions::instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
    delete instance;
}

Collisions* Collisions::GetInst()
{
    return instance != nullptr ? instance : instance = new Collisions();
}

bool Collisions::Circle(Vector2D pos1, Vector2D pos2, float radius1, float radius2)
{
    Vector2D vec = Vector2D(pos1.x - pos2.x, pos1.y - pos2.y);
    double vecLength = sqrt((vec.x * vec.x) + (vec.y * vec.y));
    double combinedLength = radius1 + radius2;

    return vecLength < combinedLength;
}

//bool Collisions::Circle(Character* character1, Character* character2)
//{
//    Vector2D vec = Vector2D(character1->GetPosition().x - character2->GetPosition().x, character1->GetPosition().y - character2->GetPosition().y);
//    double vecLength = sqrt((vec.x * vec.x) + (vec.y * vec.y));
//    double combinedLength = character1->GetCollisionRadius() + character2->GetCollisionRadius();
//
//    return vecLength < combinedLength;
//}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
    if (rect1.x <= rect2.x + rect2.width && rect1.x + rect1.width >= rect2.x && rect1.y <= rect2.y + rect2.height && rect1.y + rect1.height >= rect2.y)
    {
        return true;
    }

    return false;
}
