#pragma once
#include "Card.h"
class CardTwo :public Card
{


public:

	CardTwo(const CellPosition& pos);

	CardTwo(const CardTwo* otherCard, const CellPosition& pos);
	
	CardTwo();

	CardTwo* hasCardTwo(Card* card) const;

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void ReadCardParameters(Grid* pGrid);
	
	virtual void Load(ifstream& InFile);

	virtual void Save(ofstream& OutFile, int type);
	
	virtual ~CardTwo();

};



