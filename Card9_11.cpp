#include "Card9_11.h"
#include <fstream>

#include <string>

Card9_11::Card9_11(const CellPosition& pos) : Card(pos) // set the cell position of the card
{

	CardPrice = 0;
	Fees = 0;
	owner = NULL;
	noOwners = false;

}

Card9_11::Card9_11() // set the cell position of the card
{

	CardPrice = 0;
	Fees = 0;
	owner = NULL;
	noOwners = false;

}

Card9_11* Card9_11::hasCard9_11(Card* card) const
{

	return dynamic_cast<Card9_11*> (card);

}

Card9_11::~Card9_11()
{



}

void Card9_11::setOwner(Player* player)
{



}

bool Card9_11::hasOwner()
{

	if (owner)
		return true;

	return false;

}

void Card9_11::setNoOwners(Grid* pGrid, Player* pPlayer)
{

	// No Owners
	if (pGrid->anyPlayerOwnThisCard(cardNumber))
		noOwners = false;
	else
		noOwners = true;

}

void Card9_11::ReadCardParameters(Grid* pGrid)
{

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."

	pOut->PrintMessage("New Card" + to_string(cardNumber) + ": Enter its price...");
	int price = pIn->GetInteger(pOut);

	// Invalid number (zero or negative)
	if (price <= 0)
	{

		pGrid->PrintErrorMessage("Error: Price must be positive integer! Click to continue...");
		return;

	}
	CardPrice = price;

	pOut->PrintMessage("Enter its fees...");
	int fees = pIn->GetInteger(pOut);

	// Invalid number (zero or negative)
	if (fees <= 0)
	{

		pGrid->PrintErrorMessage("Error: Fees must be positive integer! Click to continue...");
		return;

	}
	Fees = fees;

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}

void Card9_11::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	string approval;
	bool askAgain = false;

	setNoOwners(pGrid, pPlayer);

	// No Player own this card
	if (noOwners)
	{

		do
		{

			pOut->PrintMessage("Do you want to buy Card" + to_string(cardNumber) + "?(yes/no)");
			approval = pIn->GetSrting(pOut);

			// Not Case-Sensetive
			for (int i = 0; i < approval.length(); i++)
				approval[i] = (char)tolower(approval[i]);

			if (approval.compare("yes") != 0 && approval.compare("no") != 0)
				askAgain = true;

		} while (askAgain);


		// Want to buy
		if (approval.compare("yes") == 0)
		{

			pPlayer->SetWallet(pPlayer->GetWallet() - CardPrice);
			pPlayer->setCardOwnership(cardNumber, true);
			pPlayer->addCardOwnership(this);

		}

	}

	// currentPlayer is owner
	else if (pPlayer->ownCard(cardNumber))
		return;

	// currentPlayer is not the owner and other player owns it
	else
	{

		pPlayer->SetWallet(pPlayer->GetWallet() - Fees);

	}

}

int Card9_11::getCardPrice()
{

	return CardPrice;

}

void Card9_11::Save(ofstream& OutFile, int type)
{

	

}

void Card9_11::Load(ifstream& InFile)
{

	

}
