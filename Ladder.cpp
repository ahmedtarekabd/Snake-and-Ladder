#include "Ladder.h"

#include <fstream>

int Ladder::numOfLadders = 0;

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	///TODO: Do the needed validation

	// vCell of startCell must be bigger than endCell and both are on the same column
	if (startCellPos.VCell() > endCellPos.VCell() || startCellPos.HCell() == endCellPos.HCell())
	{

		this->endCellPos = endCellPos;
		increaseNumOfLadders();

	}
	else
		this->endCellPos.SetVCell(startCellPos.VCell() + 1);


}

Ladder::Ladder()
{



}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	//pGrid->GetOutput()->PrintMessage("You have reached a ladder. Click to continue ...");
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}



bool Ladder::isOverlapping(GameObject* onGridObject) const
{

	Ladder* onGridLadder = dynamic_cast<Ladder*>(onGridObject);

	// "this" is the new ladder
	int newLadderStartPos = this->GetPosition().VCell(); //
	int newLadderEndPos = this->GetEndPosition().VCell();

	if (onGridLadder != NULL)
	{

		// Ladder that is already in the grid
		int onGridLadderStartPos = onGridLadder->GetPosition().VCell();
		int onGridLadderEndPos = onGridLadder->GetEndPosition().VCell();

		// If the current ladder (from Start to end) below the otherLadder's Start
		// OR the current ladder (from Start to end) above the otherLadder's End
		// So NOT OVERLAPPING
		if (newLadderEndPos > onGridLadderStartPos || newLadderStartPos < onGridLadderEndPos)
			return false;
		else // OVERLAPPING
			return true;

	}
	
	// return false if the otherObject is not a ladder
	return false;

}

void Ladder::increaseNumOfLadders()
{

	numOfLadders++;

}

int Ladder::getNumOfLadders()
{

	return numOfLadders;

}

void Ladder::setNumOfLadders(int number)
{

	numOfLadders = number;

}

void Ladder::Save(ofstream& OutFile, int type)
{

	if (type == LADDER)
		OutFile << GetPosition().GetCellNum() << " " << GetEndPosition().GetCellNum() << endl;

}

void Ladder::Load(ifstream& InFile)
{

	int startPosNum, endPosNum;

	InFile >> startPosNum >> endPosNum;

	CellPosition startPos(startPosNum);
	this->position = startPos;

	CellPosition endPos(endPosNum);
	this->endCellPos = endPos;

}

Ladder::~Ladder()
{

	numOfLadders--;

}
