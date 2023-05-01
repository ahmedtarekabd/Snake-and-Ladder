#pragma once

#include "Card.h"

class CardFour : public Card
{



public:

	CardFour(const CellPosition& pos);

	CardFour::CardFour(const CardFour* otherCard, const CellPosition& pos);
	
	CardFour* hasCardFour(Card* card) const;

	CardFour();

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Load(ifstream& InFile);

	virtual void Save(ofstream& OutFile, int type);
		
	virtual ~CardFour();
};


