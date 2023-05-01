#include "CardSeven.h"

#include <fstream>

CardSeven::CardSeven(const CellPosition& pos) :Card(pos)
{
	cardNumber = 7;
	increaseNumOfCards();
}

CardSeven::CardSeven(const CardSeven* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardSeven::CardSeven()
{
	cardNumber = 7;
	//increaseNumOfCards();  //modified
}

CardSeven* CardSeven::hasCardSeven(Card* card) const
{

	return dynamic_cast<CardSeven*> (card);

}

void CardSeven::ReadCardParameters(Grid* pGrid)
{
}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Player* nextPlayer = pGrid->GetNextPlayer(position);

	

	if (nextPlayer)
	{

		pGrid->PrintErrorMessage("Bad Luck Player " + to_string(nextPlayer->getPlayerNumber()));
		nextPlayer->goToCell(pGrid, pGrid->getCellFromNumber(1));

	}

	// Clear messages
	pGrid->GetOutput()->ClearStatusBar();
		
}

void CardSeven::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}
CardSeven::~CardSeven()
{
	numOfCards--;
}

void CardSeven::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}
