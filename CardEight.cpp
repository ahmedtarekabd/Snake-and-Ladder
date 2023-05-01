#include "CardEight.h"

#include<fstream>

CardEight::CardEight(const CellPosition& pos) :Card(pos)
{
	cardNumber = 8;
	increaseNumOfCards();
}

CardEight::CardEight(const CardEight* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}

CardEight* CardEight::hasCardEight(Card* card) const
{

	return dynamic_cast<CardEight*> (card);

}


CardEight::CardEight()
{
	cardNumber = 8;
	// increaseNumOfCards();   //modified
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	pO->PrintMessage("Enter the amount of Fees to leave prison...");

	int number = pIn->GetInteger(pO);

	/*if (number <= 0)
	{

		pGrid->PrintErrorMessage("Error: Fees must be a");
		return;
	}*/

	AmountToLeavePrison = number;

}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)

{
	Card::Apply(pGrid, pPlayer);

	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	pO->PrintMessage("Enter '1' to pay specific amount of coins to go out of the prison or Enter '2' or stay in prison and not play for 3 turns");
	
	ChoiceClicked = pIn->GetInteger(pO);
	
	if (ChoiceClicked == 1)
	{

		pPlayer->SetWallet(pPlayer->GetWallet() - AmountToLeavePrison);

	}
	else if (ChoiceClicked == 2)
	{
		pO->PrintMessage("stay in prison and not play for 3 turns");
		pPlayer->setPreventedNextTurn(true, 3);
	}

}
void CardEight::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << AmountToLeavePrison <<  " " <<ChoiceClicked << endl;

}

CardEight::~CardEight()
{
	numOfCards--;
}

void CardEight::Load(ifstream& InFile)
{

	int cellNum, AmountToLeavePrison ,ChoiceClicked;

	InFile >> cellNum >> AmountToLeavePrison >> ChoiceClicked;

	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

	this->AmountToLeavePrison = AmountToLeavePrison;
	this->ChoiceClicked=ChoiceClicked;
	
}