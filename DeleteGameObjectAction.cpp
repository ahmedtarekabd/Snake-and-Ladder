#include "DeleteGameObjectAction.h"

#include"Grid.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}

void DeleteGameObjectAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Select the cell to reset...");
	CellPosition cellPosition = pIn->GetCellClicked();

	if (!(pGrid->HasCard(cellPosition) || pGrid->HasSnake(cellPosition) || pGrid->HasLadder(cellPosition)))
	{
		pGrid->PrintErrorMessage("Error: There is no Object in this cell! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	objectPosition = cellPosition;

	// Clear messages
	pOut->ClearStatusBar();

}

void DeleteGameObjectAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	
	ReadActionParameters();

	pGrid->RemoveObjectFromCell(objectPosition);

}

DeleteGameObjectAction::~DeleteGameObjectAction()
{
}