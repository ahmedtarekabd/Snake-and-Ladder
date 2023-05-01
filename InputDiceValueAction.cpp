#include "InputDiceValueAction.h"

#include "Grid.h"
#include "Player.h"


InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	int selectedNumber;

	do
	{
		pO->PrintMessage("please enter a dice value between 1 - 6");
		selectedNumber = pIn->GetInteger(pO);
	} while (selectedNumber <= 0 || selectedNumber > 6);
	
	diceNumber = selectedNumber;

}

void InputDiceValueAction::Execute()
{


	Grid* pGrid = pManager->GetGrid();

	ReadActionParameters();

	if (pGrid->GetEndGame())
		return;

	Player* currentPlayer = pGrid->GetCurrentPlayer();

	if (currentPlayer->GetCell()->GetCellPosition().GetCellNum() + diceNumber <= 99)
		currentPlayer->Move(pGrid, diceNumber);

	pGrid->AdvanceCurrentPlayer();

	// Clear messages
	pGrid->GetOutput()->ClearStatusBar();

}

InputDiceValueAction::~InputDiceValueAction()
{
}