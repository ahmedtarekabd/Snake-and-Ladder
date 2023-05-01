#include "Snake.h"

#include <fstream>

int Snake::numOfSnakes = 0;

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{

	///TODO: Do the needed validation

	// vCell of startCell must be bigger than endCell and both are on the same column
	if (startCellPos.VCell() < endCellPos.VCell() || startCellPos.HCell() == endCellPos.HCell())
	{

		this->endCellPos = endCellPos;
		increaseNumOfSnakes();

	}
	else
		this->endCellPos.SetVCell(startCellPos.VCell() - 1);

}

Snake::Snake()
{



}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click

	//pGrid->GetOutput()->PrintMessage("You have reached a Snake. Click to continue ...");
	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");

	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

bool Snake::isOverlapping(GameObject* onGridObject) const
{

	Snake* onGridSnake = dynamic_cast<Snake*>(onGridObject);

	// "this" is the new Snake
	int newSnakeStartPos = this->GetPosition().VCell();
	int newSnakeEndPos = this->GetEndPosition().VCell();

	if (onGridSnake != NULL)
	{

		// Snake that is already in the grid
		int onGridSnakeStartPos = onGridSnake->GetPosition().VCell();
		int onGridSnakeEndPos = onGridSnake->GetEndPosition().VCell();

		// If the current Snake (from Start to end) below the otherSnake's Start
		// OR the current Snake (from Start to end) above the otherSnake's End
		// So NOT OVERLAPPING
		if (newSnakeEndPos < onGridSnakeStartPos || newSnakeStartPos > onGridSnakeEndPos)
			return false;
		else // OVERLAPPING
			return true;

	}

	// return false if the otherObject is not a Snake
	return false;

}

void Snake::increaseNumOfSnakes()
{

	numOfSnakes++;

}

int Snake::getNumOfSnakes()
{

	return numOfSnakes;

}

void Snake::setNumOfSnakes(int number)
{

	numOfSnakes= number;

}

void Snake::Save(ofstream& OutFile, int type)
{
	if (type == SNAKE)
		OutFile << GetPosition().GetCellNum() << " " << GetEndPosition().GetCellNum() << endl;

}

void Snake::Load(ifstream& InFile)
{

	int startPosNum, endPosNum;

	InFile >> startPosNum >> endPosNum;

	CellPosition startPos(startPosNum);
	this->position = startPos;

	CellPosition endPos(endPosNum);
	this->endCellPos = endPos;

}

Snake::~Snake()
{

	numOfSnakes--;

}
