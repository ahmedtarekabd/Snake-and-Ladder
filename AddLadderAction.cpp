#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	cancelExecution = false;

}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	
	///TODO: Make the needed validations on the read parameters

	// If start above the end
	if (startPos.VCell() <= endPos.VCell())
	{

		pGrid->PrintErrorMessage("Error: The start of the Ladder must be below the end! Click to continue ...");
		cancelExecution = true;

	}

	// If not on the same column
	if (startPos.HCell() != endPos.HCell())
	{

		pGrid->PrintErrorMessage("Error: The Ladder must be in the same column! Click to continue ...");
		cancelExecution = true;

	}

	// The start cell is a special cell (a card cell), or a cell in the last row
	if (pGrid->HasCard(startPos) || startPos.VCell() == 0)
	{

		pGrid->PrintErrorMessage("Error: The start cell cannot be a special cell (a card cell), nor a cell in the last row! Click to continue ...");
		cancelExecution = true;

	}

	// The end cell of a ladder is the start cell of another ladder or snake
	if (pGrid->HasLadder(endPos) || pGrid->HasSnake(endPos))
	{

		pGrid->PrintErrorMessage("Error: The end cell of a ladder cannot be the start cell of another ladder or snake! Click to continue ...");
		cancelExecution = true;

	}

	// The start cell of a ladder is the end cell of another ladder or snake
	if (pGrid->startOverlapsEnd(startPos))
	{

		pGrid->PrintErrorMessage("Error: The start cell of a ladder cannot be the end cell of another ladder or snake! Click to continue ...");
		cancelExecution = true;

	}

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if (cancelExecution)
		return;

	// Create a Ladder object with the parameters read from the user
	Ladder* pLadder = new Ladder(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	bool overlaping = pGrid->isOverlapping(pLadder);
	if (overlaping)
	{

		pGrid->PrintErrorMessage("Error: Two ladders cannot overlap! Click to continue ...");
		delete pLadder;
		return;

	}

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
