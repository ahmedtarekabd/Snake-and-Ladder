#pragma once

#include "Card9_11.h"

class CardNine : public Card9_11
{

	

public:
	CardNine(const CellPosition& pos); // A Constructor takes card position

	CardNine(const CardNine* otherCard, const CellPosition& pos);
	
	CardNine();
	
	CardNine* hasCardNine(Card* card) const;

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member

	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);

	virtual int getCardPrice();

	void setOwner(Player* player);

	void setNoOwners(Grid* pGrid, Player* pPlayer);

	virtual ~CardNine(); // A Virtual Destructor
};
