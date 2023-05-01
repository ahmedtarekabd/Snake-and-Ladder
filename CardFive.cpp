#include "CardFive.h"
#include "Snake.h"
#include "Ladder.h"
#include <fstream>

CardFive::CardFive(const CellPosition& pos) :Card(pos)
{
	cardNumber = 5;
	increaseNumOfCards();
}

CardFive::CardFive(const CardFive* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardFive::CardFive()
{
	cardNumber = 5;
	// increaseNumOfCards();   //modified
}


CardFive* CardFive::hasCardFive(Card* card) const
{

	return dynamic_cast<CardFive*> (card);

}

void CardFive::ReadCardParameters(Grid* pGrid)
{
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	int stepstomoveback = pPlayer->getJustRolledDice();

	bool countTurn = false;
	pPlayer->Move(pGrid, -stepstomoveback, countTurn);

}
void CardFive::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}
CardFive::~CardFive()
{
	numOfCards--;
}

void CardFive::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}
