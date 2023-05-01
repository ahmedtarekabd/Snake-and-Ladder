#include "CardTwelve.h"

#include <fstream>

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
	increaseNumOfCards();
}

CardTwelve::CardTwelve(const CardTwelve* otherCard, const CellPosition& pos) : Card(pos)
{

	*this = *otherCard;
	position = pos;
	increaseNumOfCards();

}
CardTwelve::CardTwelve()
{
	cardNumber = 2;
	//increaseNumOfCards();  //modified
}

CardTwelve* CardTwelve::hasCardTwelve(Card* card) const
{

	return dynamic_cast<CardTwelve*> (card);

}

CardTwelve::~CardTwelve()
{
	numOfCards--;
}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{



}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Player* leastPlayer = pGrid->GetPlayerLeastAmount();

	//leastPlayer->setCardOwnership();

	//Player* leastPlayer = pGrid->GetPlayerLeastAmount();
	//
	//// Add the station to the poorest player then remove the ownership of the current player
	//leastPlayer->addCardOwnership(pPlayer->getMostExpensiveCardOwned());
	//pPlayer->removeCardOwnership(pPlayer->getMostExpensiveCardOwned());

	////pPlayer->getMostExpensiveCardOwned();

}

void CardTwelve::Save(ofstream& OutFile, int type)
{

	if (type == CARD)
		OutFile << cardNumber << " " << GetPosition().GetCellNum() << endl;

}
void CardTwelve::Load(ifstream& InFile)
{

	int cellNum;

	InFile >> cellNum;


	CellPosition cellNumber(cellNum);
	this->position = cellNumber;

}