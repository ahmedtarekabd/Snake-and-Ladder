#pragma once
#include "Action.h"
class DeleteGameObjectAction : public Action
{

	CellPosition objectPosition;

public:

	DeleteGameObjectAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DeleteGameObjectAction();
};