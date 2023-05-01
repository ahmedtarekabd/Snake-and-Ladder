#include "Player.h"
#include"Card9_11.h"
#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	prisoned = 0;
	justRolledDiceNum = 0;
	currentNumOfCardsOwned = 0;
	preventedNextTurn = false;

	for (int i = 0; i < MaxOwnedCards; i++)
		CardsOwned[i] = false;

	for (int i = 0; i < MaxOwnedCards; i++)
		cardsOwned[i] = NULL;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::getJustRolledDice() const
{
	return justRolledDiceNum;
}

void Player::decrementTurnCount()
{

	if (turnCount > 0)
		turnCount--;

}

bool Player::ownCard(int cardNumber)
{


	//return currentNumOfCardsOwned == 0;
	// Change from (9->11) to (0->2)
	return CardsOwned[cardNumber - 9];

}

void Player::setCardOwnership(int cardNumber, bool ownership)
{

	// Change from (9->11) to (0->2)
	CardsOwned[cardNumber - 9] = ownership;


}

void Player::addCardOwnership(Card* card)
{

	cardsOwned[currentNumOfCardsOwned++] = card;

}

void Player::removeCardOwnership(Card* card)
{

	for (int i = 0; i < currentNumOfCardsOwned; i++) // card10 card11
		if (cardsOwned[i] == card)
		{

			cardsOwned[i] = cardsOwned[currentNumOfCardsOwned];
			cardsOwned[currentNumOfCardsOwned] = NULL;

		}
	
	currentNumOfCardsOwned--;

}

Card* Player::getMostExpensiveCardOwned()
{

	if (currentNumOfCardsOwned == 0)
		return NULL;

	Card* mostexpensive = cardsOwned[0];

	for (int i = 1; i < currentNumOfCardsOwned; i++)
	{

		Card9_11* firstCard = NULL;
		firstCard = firstCard->hasCard9_11(mostexpensive);

		Card9_11* secondCard = NULL;
		secondCard = secondCard->hasCard9_11(cardsOwned[i]);

		// If the second greater than the first
		if (firstCard->getCardPrice() < secondCard->getCardPrice())
			mostexpensive = cardsOwned[i];

	}

	return mostexpensive;
}

void Player::setPreventedNextTurn(bool preventNextTurn, int numberOfTimes)
{

	if (preventNextTurn)
		preventedNextTurn = true;

	preventNumOfTimes = numberOfTimes;

}

void Player::goToCell(Grid* pGrid, Cell* cell)
{

	pGrid->UpdatePlayerCell(this, cell->GetCellPosition());

}

int Player::getPlayerNumber()
{

	return playerNum;

}

Player* Player::GetPlayerLeastAmount(Player* anotherplayer)
{

	if (GetWallet() < anotherplayer->GetWallet())
	{
		return this;
	}
	
	return anotherplayer;

}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber, bool countTurn)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once

	turnCount++;

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	// If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	if (countTurn)
	{

		if (turnCount == 3)
		{

			if (diceNumber < 0)
				diceNumber *= -1;

			wallet += 10 * diceNumber;
			turnCount = 0;
			return;

		}

	}

	// Card 9-11
	if (prisoned > 0)
	{

		prisoned--;
		return;

	}

	// Card Four & Eight
	if (preventedNextTurn)
	{

		if (preventNumOfTimes == 0)
			preventedNextTurn = false;
		// else							modified
		preventNumOfTimes--;

		return;
	}

	// 3- Set the justRolledDiceNum with the passed diceNumber

	justRolledDiceNum = diceNumber;

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	CellPosition pos(GetCell()->GetCellPosition().GetCellNum() + diceNumber);


	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	pGrid->UpdatePlayerCell(this, pos);

	// 6- Apply() the game object of the reached cell (if any)

	GameObject* gameObject = pCell->GetGameObject();

	if (gameObject != NULL)
		gameObject->Apply(pGrid, this);

	gameObject = pCell->GetGameObject();

	// Check if position has changed (by ladder or snake)
	if (pCell->GetCellPosition().GetCellNum() != pos.GetCellNum())
		gameObject->Apply(pGrid, this);

	// modified
	//// Checks for a card after 
	//if (gameObject != NULL)
	//	if ((pGrid->HasCard(pCell->GetCellPosition())))
	//		gameObject->Apply(pGrid, this);

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

	if (GetCell()->GetCellPosition().GetCellNum() == 99)
	{

		pGrid->SetEndGame(true);
		pGrid->PrintErrorMessage("Congratualtion P" + to_string(playerNum) + ". You have reached the end! You are Winner ;)");
		pGrid->PrintErrorMessage("Open a grid by it's name or start from scrach by pressing enter after clicking 'Open Grid'");

	}

}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}