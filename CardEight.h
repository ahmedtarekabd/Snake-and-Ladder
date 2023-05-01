#pragma once
#include "Card.h"
class CardEight : public Card
{

	int AmountToLeavePrison;
	int ChoiceClicked;

public:
	CardEight(const CellPosition& pos);

	CardEight(const CardEight* otherCard, const CellPosition& pos);
	
	CardEight();
	
	CardEight* hasCardEight(Card* card) const;

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);

	virtual ~CardEight();

};


