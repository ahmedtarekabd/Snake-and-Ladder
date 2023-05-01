#include "CardTwo.h"

#include "Ladder.h"

#include <fstream>

CardTwo::CardTwo(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
    increaseNumOfCards();
}

CardTwo::CardTwo(const CardTwo* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}

CardTwo::CardTwo()
{
	cardNumber = 2;
    //increaseNumOfCards();  //modified
}

CardTwo* CardTwo::hasCardTwo(Card* card) const
{

	return dynamic_cast<CardTwo*> (card);

}

CardTwo::~CardTwo()
{
	numOfCards--;
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Ladder* ladder = pGrid->GetNextLadder(position);

	// cellNumber of startCell of Ladder - player's cellNumber
	int numberOfCellsToMove = ladder->GetPosition().GetCellNum() - pPlayer->GetCell()->GetCellPosition().GetCellNum(); // 55 - 6

	if (ladder != NULL)
	{

		pPlayer->Move(pGrid, numberOfCellsToMove);

	}

}

void CardTwo::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}

void CardTwo::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;


	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}
