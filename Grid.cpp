#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"

#include <fstream>

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{

	if (pNewObject != NULL)
	{

		// Get the cell position of pNewObject
		CellPosition pos = pNewObject->GetPosition();
		if (pos.IsValidCell()) // Check if valid position
		{
			// Get the previous GameObject of the Cell
			GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
			if (pPrevObject)  // the cell already contains a game object
				return false; // do NOT add and return false

			// Set the game object of the Cell with the new game object
			CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
			return true; // indicating that addition is done
		}

	}

	// If invalid cell or no gameObject
	return false;

}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition& pos, bool deleteGameObject)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		if (deleteGameObject)
			delete CellList[pos.VCell()][pos.HCell()]->GetGameObject(); // Just to reduce the amount of memory leaks
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Checking GameObjects inside Cells =========


Ladder* Grid::HasLadder(const CellPosition& cellPosition) const
{

	return CellList[cellPosition.VCell()][cellPosition.HCell()]->HasLadder();

}

Snake* Grid::HasSnake(const CellPosition& cellPosition) const
{

	return CellList[cellPosition.VCell()][cellPosition.HCell()]->HasSnake();

}

Card* Grid::HasCard(const CellPosition& cellPosition) const
{

	return CellList[cellPosition.VCell()][cellPosition.HCell()]->HasCard();

}

bool Grid::startOverlapsEnd(const CellPosition& startPos) const
{

	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{

		// Check first if ladder or snake exist before getting it's endPosition
		if (CellList[i][startPos.HCell()]->HasLadder())
		{
			if (CellList[i][startPos.HCell()]->HasLadder()->GetEndPosition().GetCellNum() == startPos.GetCellNum())
				return true;
		}
		else if (CellList[i][startPos.HCell()]->HasSnake())
		{
			if (CellList[i][startPos.HCell()]->HasSnake()->GetEndPosition().GetCellNum() == startPos.GetCellNum())
				return true;
		}

	}
	return false;

}

bool Grid::isOverlapping(GameObject* newObject) const
{

	bool overlap = false;
	CellPosition otherPos = newObject->GetPosition();

	for (int i = 0; i < NumVerticalCells; i++)
	{

		///TODO: Check if CellList[i][j] has a ladder, if yes return it
		overlap = newObject->isOverlapping(CellList[i][otherPos.HCell()]->GetGameObject());

		if (overlap)
			return true;

	}


	return false;

}

bool Grid::anyPlayerOwnThisCard(int cardNumber)
{

	bool playerOwnThisCard = false;

	for (int i = 0; i < MaxPlayerCount; i++)
		if (PlayerList[i]->ownCard(cardNumber))
			playerOwnThisCard = true;

	//for (int i = 0; i < MaxPlayerCount; i++)
	//	if (PlayerList[i]->ownCard(cardNumber))
	//		playerOwnThisCard = true;

	return playerOwnThisCard;

}

void Grid::giveExtraRollDice()
{

	currPlayerNumber--;

}

void Grid::ResetPlayerPosition(const CellPosition& cellPosition)
{
	for (int i = 0; i < MaxPlayerCount; i++)
		UpdatePlayerCell(PlayerList[i], cellPosition);

}

Player* Grid::GetPlayerLeastAmount()
{
	Player* leastcoinsplayer = PlayerList[0];
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		leastcoinsplayer = leastcoinsplayer->GetPlayerLeastAmount(PlayerList[i]);
	}
	return leastcoinsplayer;
}

void Grid::ResetOwnerships()
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		for (int j = 0; j < MaxOwnedCards; j++)
		{
			PlayerList[i]->setCardOwnership(j, false);
		}
	}
}


// ========= Save and Load the Grid =========

void Grid::SaveAll(ofstream& OutFile, int type) const
{

	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{

		for (int j = 0; j < NumHorizontalCells; j++)
		{

			switch (type)
			{

			case LADDER:
				if (CellList[i][j]->HasLadder())
					CellList[i][j]->GetGameObject()->Save(OutFile, LADDER);
				break;

			case SNAKE:
				if (CellList[i][j]->HasSnake())
					CellList[i][j]->GetGameObject()->Save(OutFile, SNAKE);
				break;

			case CARD:
				if (CellList[i][j]->HasCard())
					CellList[i][j]->GetGameObject()->Save(OutFile, CARD);
				break;

			}

		}

	}

}

void Grid::clearAll()
{

	CellPosition pos(1);
	ResetPlayerPosition(pos);
	ResetOwnerships();

	Ladder::setNumOfLadders(0);
	Snake::setNumOfSnakes(0);
	Card::setNumOfCards(0);

	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{

		for (int j = 0; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasLadder() || CellList[i][j]->HasSnake() || CellList[i][j]->HasCard())
			{

				RemoveObjectFromCell(CellList[i][j]->GetCellPosition(), false);

			}

		}

	}

}

// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::GetNextPlayer(const CellPosition& position)
{

	int nearest = 100;

	// Get the nearest player
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		int playerCellNumber = PlayerList[i]->GetCell()->GetCellPosition().GetCellNum();

		if (playerCellNumber > position.GetCellNum())
			if (nearest > playerCellNumber)
				nearest = playerCellNumber;

	}

	for (int i = 0; i < MaxPlayerCount; i++)
	{

		if (PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() == nearest)
			return PlayerList[i];

	}
	return NULL;

}

Cell* Grid::getCellFromNumber(int cellNumber)
{

	CellPosition newPosition(cellNumber);
	return CellList[newPosition.VCell()][newPosition.HCell()];

}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}