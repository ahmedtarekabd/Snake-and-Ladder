#include "CardFour.h"

#include <fstream>

CardFour::CardFour(const CellPosition& pos) :Card(pos)
{
	cardNumber = 4;
	increaseNumOfCards();
}

CardFour::CardFour(const CardFour* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardFour::CardFour()
{
	cardNumber = 4;
	//increaseNumOfCards();   //modified
}

CardFour* CardFour::hasCardFour(Card* card) const
{

	return dynamic_cast<CardFour*> (card);

}

void CardFour::ReadCardParameters(Grid* pGrid)
{

}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{

	pPlayer->setPreventedNextTurn(true);

}

void CardFour::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}

CardFour::~CardFour()
{
	numOfCards--;
}

void CardFour::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}