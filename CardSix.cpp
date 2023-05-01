#include "CardSix.h"
#include "Ladder.h"
#include "Snake.h"
#include <fstream>

CardSix::CardSix(const CellPosition& pos) :Card(pos)
{
	cardNumber = 6;
	increaseNumOfCards();
}

CardSix::CardSix(const CardSix* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardSix::CardSix()
{
	cardNumber = 6;
	//increaseNumOfCards();  //modified
}

CardSix* CardSix::hasCardSix(Card* card) const
{

	return dynamic_cast<CardSix*> (card);

}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	pO->PrintMessage("Cell to move to");
	int cellNumber = pIn->GetInteger(pO);//waits for user to enter the cell to move to

	//CellPosition specificcellposition = pIn->GetCellClicked();//waits for user to click the cell to move to

	if (cellNumber > 99 || cellNumber < 1)
		return;

	specificCell = cellNumber;
	//cell number of the cell the player chose

}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	//int playerCell = pPlayer->GetCell()->GetCellPosition().GetCellNum(); // modified

	pPlayer->goToCell(pGrid, pGrid->getCellFromNumber(specificCell));
	
	// Clear messages
	pGrid->GetOutput()->ClearStatusBar();

}

void CardSix::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}
CardSix::~CardSix()
{
	numOfCards--;
}

void CardSix::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	specificCell = 0;

}