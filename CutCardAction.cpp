#include "CutCardAction.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"

CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{

	// Initializes the pManager pointer of Action with the passed pointer
	cancelExecution = false;
	cutOnce = true;

}

CutCardAction::~CutCardAction()
{



}

void CutCardAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Click the card you want to copy");
	CellPosition cellPosition = pIn->GetCellClicked();

	if (!(pGrid->HasCard(cellPosition)))
	{

		pGrid->PrintErrorMessage("Error: No Card in this cell! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	cardPosition = cellPosition;

	// Clear messages
	pOut->ClearStatusBar();

}

void CutCardAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	ReadActionParameters();

	if (cancelExecution)
		return;

	if (pGrid->HasCard(cardPosition))
		card = pGrid->HasCard(cardPosition);

	pGrid->SetClipboard(card);

	pGrid->PrintErrorMessage("Cut");


	bool deleteGameObject = false;

	// Remove the card from grid (cut)
	pGrid->RemoveObjectFromCell(cardPosition, deleteGameObject);
	card->decreaseNumOfCards();

	// Clear messages
	pOut->ClearStatusBar();

}

