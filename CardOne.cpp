#include "CardOne.h"

#include <fstream>

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
//used in add card
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	walletAmount = 0;
	increaseNumOfCards();

}

CardOne::CardOne(const CardOne* otherCard, const CellPosition& pos)
{
//used in paste card
	// Same Data Members
	*this = *otherCard;
	// New Position
	position = pos;
	increaseNumOfCards();

}

CardOne::CardOne()
{
//used in loading card
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	walletAmount = 0;
	//increaseNumOfCards(); // modified

}

CardOne* CardOne::hasCardOne(Card* card) const
{

	return dynamic_cast<CardOne*> (card);

}

CardOne::~CardOne()
{

	numOfCards--;

}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	
	pOut->PrintMessage("New CardOne: Enter its wallet amount ...");
	int walletValue = pIn->GetInteger(pOut);

	// Invalid number (zero or negative)
	if (walletValue <= 0)
	{

		pGrid->PrintErrorMessage("Error: Value must be positive integer! Click to continue...");
		return;

	}
	
	walletAmount = walletValue;

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer->SetWallet(pPlayer->GetWallet() - walletAmount);

}

void CardOne::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << " " << walletAmount << endl;

}

void CardOne::Load(ifstream& InFile)
{

	int cellNum, amount;

	InFile >> cellNum >> amount;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	walletAmount = amount;

}
