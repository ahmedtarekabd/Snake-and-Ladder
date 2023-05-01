#include "CardEleven.h"
#include <fstream>


CardEleven::CardEleven(const CellPosition& pos) : Card9_11(pos) // set the cell position of the card
{

	cardNumber = 11; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	increaseNumOfCards();

}

CardEleven::CardEleven(const CardEleven* otherCard, const CellPosition& pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardEleven::CardEleven()
{

	cardNumber = 11; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	//increaseNumOfCards();  //modified

}

CardEleven* CardEleven::hasCardEleven(Card* card) const
{

	return dynamic_cast<CardEleven*> (card);

}

CardEleven::~CardEleven()
{

	numOfCards--;

}

void CardEleven::setNoOwners(Grid* pGrid, Player* pPlayer)
{

	if (pGrid->anyPlayerOwnThisCard(cardNumber))
		noOwners = false;
	else
		noOwners = true;

}

void CardEleven::ReadCardParameters(Grid* pGrid)
{

	Card9_11::ReadCardParameters(pGrid);

}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{

	Card9_11::Apply(pGrid, pPlayer);

}

void CardEleven::setOwner(Player* player)
{
	owner = player;
}

int CardEleven::getCardPrice()
{

	return CardPrice;

}

void CardEleven::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << " " << CardPrice << " " << Fees << endl;

}
void CardEleven::Load(ifstream& InFile)
{

	int cellNum, cardPrice, fees;

	InFile >> cellNum>> cardPrice >> fees;


	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	CardPrice = cardPrice;
	Fees = fees;
}