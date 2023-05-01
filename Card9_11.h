#pragma once

#include "Card.h"

class Player;

class Card9_11 : public Card
{

protected:

	int CardPrice;
	int Fees;

	Player* owner;

	bool noOwners;

public:
	Card9_11(const CellPosition& pos); // A Constructor takes card position

	Card9_11();

	Card9_11* hasCard9_11(Card* card) const;

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member


	virtual void setOwner(Player* player);
	virtual bool hasOwner();

	virtual int getCardPrice() = 0;

	void setNoOwners(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int type) = 0;
	virtual void Load(ifstream& InFile) = 0;

	virtual ~Card9_11(); // A Virtual Destructor
};
