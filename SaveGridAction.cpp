#include "SaveGridAction.h"

#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

#include <fstream>
#include <direct.h>

//const char* folderNameToCreate = "Grids";

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{

	

}

void SaveGridAction::ReadActionParameters()
{
	
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Enter the name of the grid: ");
	fileName = pIn->GetSrting(pOut);

}

void SaveGridAction::Execute()
{
	
	int numOfLadders = Ladder::getNumOfLadders();
	int numOfSnakes = Snake::getNumOfSnakes();
	int numOfCards = Card::getNumOfCards();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	ReadActionParameters();


	ofstream OutFile;
	
	OutFile.open(fileName + ".txt");

	// If file couldn't open, don't execute
	if (!OutFile.is_open())
		return;

	OutFile << numOfLadders << endl;
	pGrid->SaveAll(OutFile, LADDER);
	
	OutFile << numOfSnakes << endl;
	pGrid->SaveAll(OutFile, SNAKE);
	
	OutFile << numOfCards << endl;
	pGrid->SaveAll(OutFile, CARD);

	OutFile.close();

	// Clear messages
	pOut->ClearStatusBar();

}

SaveGridAction::~SaveGridAction()
{
}
