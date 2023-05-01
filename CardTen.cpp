#include "CardTen.h"
#include <fstream>

//bool CardTen::noOwners = false;

CardTen::CardTen(const CellPosition& pos) : Card9_11(pos) // set the cell position of the card
{

	cardNumber = 10; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	increaseNumOfCards();

}

CardTen::CardTen(const CardTen* otherCard, const CellPosition& pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardTen::CardTen()
{

	cardNumber = 10; // set the inherited cardNumber data member with the card number (1 here)
	noOwners = false;
	//increaseNumOfCards();   //modified

}

CardTen* CardTen::hasCardTen(Card* card) const
{

	return dynamic_cast<CardTen*> (card);

}

CardTen::~CardTen()
{

	numOfCards--;

}

void CardTen::setNoOwners(Grid* pGrid, Player* pPlayer)
{

	if (pGrid->anyPlayerOwnThisCard(cardNumber))
		noOwners = false;
	else
		noOwners = true;

}

void CardTen::ReadCardParameters(Grid* pGrid)
{

	Card9_11::ReadCardParameters(pGrid);

}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{
    
	Card9_11::Apply(pGrid, pPlayer);

}

void CardTen::setOwner(Player* player)
{
owner=player;
}

int CardTen::getCardPrice()
{
return CardPrice;
}

void CardTen::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << " " << CardPrice << " " << Fees << endl;

}
void CardTen::Load(ifstream& InFile)
{

	int cellNum, cardPice, fees;

	InFile >> cellNum>> cardPice >> fees;


	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	CardPrice= cardPice;
	Fees= fees;
}