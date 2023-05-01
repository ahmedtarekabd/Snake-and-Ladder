#include "GameObject.h"

#include "Card.h"

GameObject::GameObject(const CellPosition& pos)
{
	position = pos; // Sets Position
}

GameObject::GameObject()
{

}

Card* GameObject::hasCard(GameObject* object)
{

	return dynamic_cast<Card*> (object);

}

CellPosition GameObject::GetPosition() const
{
	return position;
}

GameObject::~GameObject()
{
}