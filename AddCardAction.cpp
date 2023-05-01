#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{

	// Initializes the pManager pointer of Action with the passed pointer
	cardNumber = 0;
	cancelExecution = false;

}

AddCardAction::~AddCardAction()
{



}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();


	// 2- Read the "cardNumber" parameter and set its data member

	pOut->PrintMessage("Enter Card Number (1-12): ");

	int number = pIn->GetInteger(pOut);

	// Invalid Card number, cancel execution
	if (number <= 0 || number > 12)
	{

		pGrid->PrintErrorMessage("Error: Invalid card number (Cards: 1->12)! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	cardNumber = number;

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	pOut->PrintMessage("Click on the cell to add the card.");
	CellPosition cellClicked = pIn->GetCellClicked();

	// Invalid Cell, cancel execution
	if (!cellClicked.IsValidCell())
	{

		pGrid->PrintErrorMessage("Error: Invalid Cell! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	// Refuse to add card in the first and the last cell
	if (cellClicked.GetCellNum() == 1 || cellClicked.GetCellNum() == 99)
	{

		pGrid->PrintErrorMessage("Error: Cannot add a card in the first or last cell! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	cardPosition = cellClicked;

	// 4- Make the needed validations on the read parameters

	// A cell have a card, cancel execution
	if (pGrid->HasCard(cardPosition))
	{

		pGrid->PrintErrorMessage("Error: A cell can’t have more than one card! Click to continue ...");
		cancelExecution = true;

	}

	// A card is placed at the start cell of a ladder or a snake, cancel execution
	if (pGrid->HasLadder(cardPosition) || pGrid->HasSnake(cardPosition))
	{

		pGrid->PrintErrorMessage("Error: A card cannot be placed at the start cell of a ladder or a snake! Click to continue ...");
		cancelExecution = true;

	}

	

	// Clear messages
	pOut->ClearStatusBar();

}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first

	ReadActionParameters();

	// check whether the card can be added or not, if not don't execute
	if (cancelExecution)
		return;

	// 2- Switch case on cardNumber data member and create the appropriate card object type

	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;

		// A- Add the remaining cases

	case 2:
		pCard = new CardTwo(cardPosition);
		break;

	case 3:
		pCard = new CardThree(cardPosition);
		break;

	case 4:
		pCard = new CardFour(cardPosition);
		break;

	case 5:
		pCard = new CardFive(cardPosition);
		break;

	case 6:
		pCard = new CardSix(cardPosition);
		break;

	case 7:
		pCard = new CardSeven(cardPosition);
		break;

	case 8:
		pCard = new CardEight(cardPosition);
		break;

	case 9:
		pCard = new CardNine(cardPosition);
		break;

	case 10:
		pCard = new CardTen(cardPosition);
		break;

	case 11:
		pCard = new CardEleven(cardPosition);
		break;

	//case 12:
	//	pCard = new CardTwelve(cardPosition);
	//	break;

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);

		// C- Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!added)
		{

			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");

		}

	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
