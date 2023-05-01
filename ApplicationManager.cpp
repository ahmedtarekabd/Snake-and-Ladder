#include "ApplicationManager.h"

#include "Grid.h"

// Design Mode Actions
#include "AddLadderAction.h"
#include "AddCardAction.h"
#include "AddSnakeAction.h"
#include "CopyCardAction.h"
#include "CutCardAction.h"
#include "PasteCardAction.h"
#include "SaveGridAction.h"
#include "OpenGridAction.h"
#include "DeleteGameObjectAction.h"
#include "SwitchToDesignModeAction.h"

// Play Mode
#include "RollDiceAction.h"
#include "InputDiceValueAction.h"
#include "NewGameAction.h"
#include "SwitchToPlayModeAction.h"

///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case EXIT:
		break;

	case TO_PLAY_MODE:
		pAct = new SwitchToPlayModeAction (this);  // temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this); // temporary till you made its action class (CHANGE THIS LATTER)
		break;

		

		///TODO: Add a case for EACH Action type in the Design mode or Play mode

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case COPY_CARD:
		// create an object of AddCardAction here
		pAct = new CopyCardAction(this); // CopyCardAction class need to be implemented
		break;

	case CUT_CARD:
		// create an object of AddCardAction here
		pAct = new CutCardAction(this); // CutCardAction class need to be implemented
		break;

	case PASTE_CARD:
		// create an object of AddCardAction here
		pAct = new PasteCardAction(this); // PasteCardAction class need to be implemented
		break;

	case DELETE_GAME_OBJECT:
		// create an object of AddCardAction here
		pAct = new DeleteGameObjectAction(this); // DeleteGameObjectAction class need to be implemented
		break;

	case OPEN_GRID:
		// create an object of AddCardAction here
		pAct = new OpenGridAction(this); // OpenGridAction class need to be implemented
		break;

	case SAVE_GRID:
		// create an object of AddCardAction here
		pAct = new SaveGridAction(this); // SaveGridAction class need to be implemented
		break;

	case INPUT_DICE_VALUE:
		// create an object of AddCardAction here
		pAct = new InputDiceValueAction(this); // InputDiceValueAction class need to be implemented
		break;

	case NEW_GAME:
		// create an object of AddCardAction here
		pAct = new NewGameAction(this);	// NewGameAction class need to be implemented
		break;




	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
