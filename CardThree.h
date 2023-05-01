#pragma once
#include "Card.h"
class CardThree :public Card
{

public:

	CardThree(const CellPosition& pos);

	CardThree(const CardThree* otherCard, const CellPosition& pos);
	
	CardThree();
	
	CardThree* hasCardThree(Card* card) const;

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void ReadCardParameters(Grid* pGrid);
	
	virtual void Load(ifstream& InFile);

	virtual void Save(ofstream& OutFile, int type);
	
	virtual ~CardThree();

};


