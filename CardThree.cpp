#include "CardThree.h"

#include <fstream>

CardThree::CardThree(const CellPosition& pos):Card(pos)
{
	cardNumber = 3;
	increaseNumOfCards();
}

// use for PasteCardAction
CardThree::CardThree(const CardThree* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}

// OpenGridAction
CardThree::CardThree()
{

	cardNumber = 3;
	//increaseNumOfCards();   //modified

}

// use for PasteCardAction
CardThree* CardThree::hasCardThree(Card* card) const
{

	return dynamic_cast<CardThree*> (card);

}

CardThree::~CardThree()
{

	numOfCards--;

}

void CardThree::ReadCardParameters(Grid* pGrid)
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	
	pGrid->giveExtraRollDice();

}

void CardThree::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}

void CardThree::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}