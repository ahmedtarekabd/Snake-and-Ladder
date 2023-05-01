#include "CopyCardAction.h"

#include "Input.h"
#include "Output.h"
#include "Card.h"

CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{

	// Initializes the pManager pointer of Action with the passed pointer
	card = NULL;
	cancelExecution = false;
	cutOnce = false;

}

CopyCardAction::~CopyCardAction()
{

	

}

void CopyCardAction::ReadActionParameters()
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

void CopyCardAction::Execute()
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
	
	pGrid->PrintErrorMessage("Copied");
	// Clear messages
	pOut->ClearStatusBar();

}

