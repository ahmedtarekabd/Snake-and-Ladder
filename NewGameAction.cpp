#include "NewGameAction.h"

#include"Grid.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) :Action(pApp)
{
	
}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	CellPosition pos(1);
	pGrid->ResetPlayerPosition(pos);

	pGrid->ResetOwnerships();

}

NewGameAction::~NewGameAction()
{
}