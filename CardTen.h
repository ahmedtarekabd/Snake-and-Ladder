#pragma once

#include "Card9_11.h"


class CardTen : public Card9_11
{

	

public:
	CardTen(const CellPosition& pos); // A Constructor takes card position

	CardTen(const CardTen* otherCard, const CellPosition& pos);
	
	CardTen();

	CardTen* hasCardTen(Card* card) const;
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member

	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);

	virtual int getCardPrice();

	void setOwner(Player* player);

	void setNoOwners(Grid* pGrid, Player* pPlayer);

	virtual ~CardTen(); // A Virtual Destructor
};
