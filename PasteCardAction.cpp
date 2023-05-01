#include "PasteCardAction.h"

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


PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{

	// Initializes the pManager pointer of Action with the passed pointer
	cancelExecution = false;
	

}

PasteCardAction::~PasteCardAction()
{



}

void PasteCardAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Select the cell to paste...");
	CellPosition cellPosition = pIn->GetCellClicked();

	if (pGrid->HasCard(cellPosition))
	{


		pGrid->PrintErrorMessage("Error: There is Card in this cell! Click to continue ...");
		pOut->ClearStatusBar();	// Clear messages

		cancelExecution = true; // Don't Execute
		return;

	}

	cardPosition = cellPosition;

	// Clear messages
	pOut->ClearStatusBar();

}

void PasteCardAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	ReadActionParameters();

	if (cancelExecution)
		return;

	// cardNumber 
	card = pGrid->GetClipboard();

	// Empty Clipboard
	if (card == NULL)
		return;


	cardNumber = card->GetCardNumber();

	// cellPosition of card (cardPosition)
	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
	{
		CardOne* cardOne = NULL;
		cardOne = cardOne->hasCardOne(card);
		if (cardOne)
			pCard = new CardOne(cardOne, cardPosition);
		break;
	}
	// Add the remaining cases

	case 2:
	{
		CardTwo* cardTwo = NULL;
		cardTwo = cardTwo->hasCardTwo(card);
		if (cardTwo)
			pCard = new CardTwo(cardTwo, cardPosition);
		break;
	}
	case 3:
	{
		CardThree* cardThree = NULL;
		cardThree = cardThree->hasCardThree(card);
		if (cardThree)
			pCard = new CardThree(cardThree, cardPosition);
		break;
	}
	case 4:
	{
		CardFour* cardFour = NULL;
		cardFour = cardFour->hasCardFour(card);
		if (cardFour)
			pCard = new CardFour(cardFour, cardPosition);
		break;
	}
	case 5:
	{
		CardFive* cardFive = NULL;
		cardFive = cardFive->hasCardFive(card);
		if (cardFive)
			pCard = new CardFive(cardFive, cardPosition);
		break;
	}
	case 6:
	{
		CardSix* cardSix = NULL;
		cardSix= cardSix->hasCardSix(card);
		if (cardSix)
			pCard = new CardSix(cardSix, cardPosition);
		break;
	}
	case 7:
	{
		CardSeven* cardSeven = NULL;
		cardSeven = cardSeven->hasCardSeven(card);
		if (cardSeven)
			pCard = new CardSeven(cardSeven, cardPosition);
		break;
	}
	case 8:
	{
		CardEight* cardEight = NULL;
		cardEight = cardEight->hasCardEight(card);
		if (cardEight)
			pCard = new CardEight(cardEight, cardPosition);
		break;
	}
	case 9:
	{
		CardNine* cardNine = NULL;
		cardNine = cardNine->hasCardNine(card);
		if (cardNine)
			pCard = new CardNine(cardNine, cardPosition);
		break;
	}
	case 10:
	{
		CardTen* cardTen = NULL;
		cardTen = cardTen->hasCardTen(card);
		if (cardTen)
			pCard = new CardTen(cardTen, cardPosition);
		break;
	}
	case 11:
	{
		CardEleven* cardEleven = NULL;
		cardEleven = cardEleven->hasCardEleven(card);
		if (cardEleven)
			pCard = new CardEleven(cardEleven, cardPosition);
		break;
	}
	//case 12:
	// {
	// CardTwelve* cardTwelve;
	//	cardTwelve = cardTwelve->hasCardTwelve(card);
	//	if (cardTwelve)
	//	pCard = new CardTwelve(cardTwelve,cardPosition);
	//	break;
	// }

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);

		// if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!added)
		{

			pGrid->PrintErrorMessage("Error: Couldn't add! Click to continue ...");
			return;

		}

		// Cut Card
		// object is till in the old position but isn't deleted
		// we have old position & new position

		// card was Cut ONCE
		// if clipboard has card in the old position -> set the clipboard to the card in the new position to use it's data to paste
		if (cutOnce)
			if (pGrid->HasCard(card->GetPosition()))
			{

				pGrid->SetClipboard(pCard);
				cutOnce = false;

			}
		
		// card was Copied -> Do nothing


	}


}

