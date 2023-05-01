#pragma once
#include "Card.h"
class CardTwelve :public Card
{



public:

	CardTwelve(const CellPosition& pos);

	CardTwelve(const CardTwelve* otherCard, const CellPosition& pos);
	
	CardTwelve();

	CardTwelve* hasCardTwelve(Card* card) const;

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int type);

	virtual void Load(ifstream& InFile);
	virtual ~CardTwelve();
};



