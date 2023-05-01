#pragma once

#include "Action.h"

class InputDiceValueAction : public Action
{

	int diceNumber;

	// Note: These parameters should be read in ReadActionParameters()

public:
	InputDiceValueAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads InputDiceValueAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~InputDiceValueAction(); // A Virtual Destructor
};