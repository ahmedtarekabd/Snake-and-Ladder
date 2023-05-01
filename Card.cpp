#include "Card.h"
#include <fstream>

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"


int Card::numOfCards = 0;

Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{

	cardNumber = 0;

}

Card::Card()
{

	cardNumber = 0;
	

}

void Card::SetCardNumber(int cnum)
{

	if (cnum >= 1 && cnum <= 12)
		cardNumber = cnum; // needs validation

}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);

}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
	
}

bool Card::isOverlapping(GameObject* otherObject) const
{

	return false;

}

void Card::increaseNumOfCards()
{

	numOfCards++;

}

void Card::decreaseNumOfCards()
{

	numOfCards--;

}

int Card::getNumOfCards()
{

	return numOfCards;

}

void Card::setNumOfCards(int number)
{

	numOfCards = number;

}

void Card::Save(ofstream& OutFile, int type)
{



}

void Card::Load(ifstream& InFile)
{

	int cardNum;

	InFile >> cardNum;

	cardNumber = cardNum;

	// cellPosition of card (cardPosition)
	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
	{
		pCard = new CardOne();
		pCard->Load(InFile);
		break;
	}
	// Add the remaining cases

	case 2:
	{

		pCard = new CardTwo();
		pCard->Load(InFile);
		break;
	}
	case 3:
	{
		pCard = new CardThree();
		pCard->Load(InFile);
		break;
	}
	case 4:
	{
		pCard = new CardFour();
		pCard->Load(InFile);
		break;
	}
	case 5:
	{

		pCard = new CardFive();
		pCard->Load(InFile);
		break;
	}
	case 6:
	{
		pCard = new CardSix();
		pCard->Load(InFile);
		break;
	}
	case 7:
	{
		pCard = new CardSeven();
		pCard->Load(InFile);
		break;
	}
	case 8:
	{
		pCard = new CardEight();
		pCard->Load(InFile);
		break;
	}
	case 9:
	{
		pCard = new CardNine();
		pCard->Load(InFile);
		break;
	}
	case 10:
	{
		pCard = new CardTen();
		pCard->Load(InFile);
		break;
	}
	case 11:
	{
		pCard = new CardEleven();
		pCard->Load(InFile);
		break;
	}
	//case 12:
	// {
	//	pCard = new CardTwelve();
	//	pCard->Load(InFile);
	//	break;
	// }

	}

	*this = *pCard;

}

Card::~Card()
{
}