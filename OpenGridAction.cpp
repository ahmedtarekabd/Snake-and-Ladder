#include "OpenGridAction.h"

#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

#include <fstream>
#include <direct.h>

//const char* folderNameToCreate = "Grids";

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{

	

}

void OpenGridAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Enter the name of the grid: ");
	fileName = pIn->GetSrting(pOut);

}

void OpenGridAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	pGrid->clearAll();
	pGrid->UpdateInterface();

	//int numOfLadders = Ladder::getNumOfLadders();
	//int numOfSnakes = Snake::getNumOfSnakes();
	//int numOfCards = Card::getNumOfCards();

	ReadActionParameters();

	ifstream InFile;

	
	InFile.open(fileName + ".txt"); // Search in the current directory

	// Couldn't find the file in the current directory
	if (!InFile.is_open())
	{

		pGrid->PrintErrorMessage("Error: Couldn't find the file! Click to continue...");
		return;

	}



	int numberOfGameObjects;
	

	// Add Ladders
	InFile >> numberOfGameObjects;
	Ladder::setNumOfLadders(numberOfGameObjects);

	GameObject* pObjectLadder = NULL;

	for (int i = 0; i < numberOfGameObjects; i++)
	{

		pObjectLadder = new Ladder;
		pObjectLadder->Load(InFile);
		pGrid->AddObjectToCell(pObjectLadder);

	}


	// Add Snakes
	InFile >> numberOfGameObjects;
	Snake::setNumOfSnakes(numberOfGameObjects);

	GameObject* pObjectSnake = NULL;

	for (int i = 0; i < numberOfGameObjects; i++)
	{

		pObjectSnake = new Snake;
		pObjectSnake->Load(InFile);
		pGrid->AddObjectToCell(pObjectSnake);

	}


	// Add Cards
	InFile >> numberOfGameObjects;
	Card::setNumOfCards(numberOfGameObjects);

	GameObject* pObjectCard = NULL;

	for (int i = 0; i < numberOfGameObjects; i++)
	{

		pObjectCard = new Card;
		pObjectCard->Load(InFile);
		pGrid->AddObjectToCell(pObjectCard);

	}

	InFile.close();

	// Clear messages
	pOut->ClearStatusBar();

}

OpenGridAction::~OpenGridAction()
{
}
