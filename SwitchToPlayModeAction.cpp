#include "SwitchToPlayModeAction.h"

#include "Grid.h"


SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// no parameters to read from user
}

void SwitchToPlayModeAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->CreatePlayModeToolBar();

}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
