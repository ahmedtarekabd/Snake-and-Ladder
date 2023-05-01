#pragma once
#include "Card.h"
class CardSeven : public Card
{
public:
	CardSeven(const CellPosition& pos);

	CardSeven(const CardSeven* otherCard, const CellPosition& pos);
	
	CardSeven();
	
	CardSeven* hasCardSeven(Card* card) const;
	
	virtual void ReadCardParameters(Grid* pGrid);
	
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	
	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);

	virtual ~CardSeven();

};


