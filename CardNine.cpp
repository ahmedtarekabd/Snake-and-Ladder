#include "CardNine.h"

#include <fstream>

CardNine::CardNine(const CellPosition& pos) : Card9_11(pos) // set the cell position of the card
{

	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	increaseNumOfCards();

}


CardNine::CardNine(const CardNine* otherCard, const CellPosition& pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardNine::CardNine()
{

	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	//increaseNumOfCards();   //modified

}

CardNine* CardNine::hasCardNine(Card* card) const
{

	return dynamic_cast<CardNine*> (card);

}

CardNine::~CardNine()
{

	numOfCards--;

}

void CardNine::setNoOwners(Grid* pGrid, Player* pPlayer)
{

	if (pGrid->anyPlayerOwnThisCard(cardNumber))
		noOwners = false;
	else
		noOwners = true;

}

void CardNine::ReadCardParameters(Grid* pGrid)
{

	Card9_11::ReadCardParameters(pGrid);
	//CardPrice = 

}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{

	Card9_11::Apply(pGrid, pPlayer);

}

void CardNine::setOwner(Player* player)
{
	owner = player;
}

int CardNine::getCardPrice()
{
	return CardPrice;
}

void CardNine::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << " " << CardPrice << " " << Fees << endl;

}

void CardNine::Load(ifstream& InFile)
{

	int cellNum, cardPrice  ,fees;

	InFile >> cellNum >> cardPrice >> fees;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	CardPrice= cardPrice;
	Fees= fees;
	
}