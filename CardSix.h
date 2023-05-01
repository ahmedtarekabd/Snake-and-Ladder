#pragma once
#include "Card.h"
class CardSix :public Card
{

	int specificCell;

public:

	CardSix(const CellPosition& pos);

	CardSix(const CardSix* otherCard, const CellPosition& pos);
	
	CardSix();
	
	CardSix* hasCardSix(Card* card) const;
	
	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void ReadCardParameters(Grid* pGrid);
	
	virtual void Load(ifstream& InFile);

	virtual void Save(ofstream& OutFile, int type);
	
	virtual ~CardSix();
};

