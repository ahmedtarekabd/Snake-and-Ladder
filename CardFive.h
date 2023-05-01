#pragma once
#include "Card.h"
class CardFive :public Card
{
public:

	CardFive(const CellPosition& pos);

	CardFive(const CardFive* otherCard, const CellPosition& pos);
	
	CardFive();
	
	CardFive* hasCardFive(Card* card) const;

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void ReadCardParameters(Grid* pGrid);
	
	virtual void Load(ifstream& InFile);
	
	virtual void Save(ofstream& OutFile, int type);

	virtual ~CardFive();

};

