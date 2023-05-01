#include "SwitchToDesignModeAction.h"

#include "Grid.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{
	// no parameters to read from user
}

void SwitchToDesignModeAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->CreateDesignModeToolBar();

}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}

