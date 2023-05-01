#pragma once

#include "Card9_11.h"

class CardEleven :	public Card9_11
{
    


public:
	CardEleven(const CellPosition & pos); // A Constructor takes card position

	CardEleven(const CardEleven* otherCard, const CellPosition& pos);
	
	CardEleven();

	CardEleven* hasCardEleven(Card* card) const;

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	
	virtual int getCardPrice();

	void setOwner(Player* player);

	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);

	void setNoOwners(Grid* pGrid, Player* pPlayer);

	virtual ~CardEleven(); // A Virtual Destructor
};
