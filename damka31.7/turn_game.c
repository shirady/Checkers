#include "turn_game.h"

static void MoveOnBoard(MultipleSourceMovesListCell* list, Board board, Player player);
static void MoveOnBoardAuxCapture(MultipleSourceMovesListCell* list, Board board, Player player);
static PrintTurn(Player player);

//The function gets a board and a player
//The function execute the best move from the possible moves in a specified board for this player (if the move is a capture the captured pieces will be removed from the board)
void Turn(Board board, Player player)
{
	MultipleSourceMovesList *listOfLists = NULL;
	listOfLists = FindAllPossiblePlayerMoves(board, player);
	AtLeastOneMove(listOfLists);
	MultipleSourceMovesListCell* list = ChooseTheListWithMaxCaptures(listOfLists);
	MoveOnBoard(list, board, player);
	FreeMultipleMovesList(listOfLists);
}

//The function gets the multiple list
//The function checks if the multiple list is not empty, which means that the player has at least one move
//If a player does not have a move the game is over
//Assumption: there's no case of allocated list with head=NULL: list is NULL or has two cells in it at least
void AtLeastOneMove(MultipleSourceMovesList *listOfLists)
{
	if (listOfLists == NULL)
		exit(NO_MOVE);
}

//The function gets a multiple list
//The function returns the optimal moves (the single list)
//Assumption: if all pieces have no captures then the returned list will the head of the list of lists (multiple list)
MultipleSourceMovesListCell* ChooseTheListWithMaxCaptures(MultipleSourceMovesList *listOfLists)
{
	MultipleSourceMovesListCell* currListOfListsCell = listOfLists->head;
	SingleSourceMovesListCell* currListCellTail = currListOfListsCell->single_source_moves_list->tail;
	MultipleSourceMovesListCell* TheChosenList = NULL;
	unsigned short MaxCaptures = currListCellTail->captures;

	while (currListOfListsCell)
	{
		if (MaxCaptures < currListCellTail->captures)
		{
			MaxCaptures = currListCellTail->captures;
			TheChosenList = currListOfListsCell;
		}
		currListOfListsCell = currListOfListsCell->next;
		if(currListOfListsCell)
			if (currListOfListsCell->single_source_moves_list)
				currListCellTail = currListOfListsCell->single_source_moves_list->tail;
	}
	if (!TheChosenList)
		TheChosenList = listOfLists->head;

	return TheChosenList;
}

//The function gets a single list, a board and a player
//The function move the piece with maximum captures, if there's no captures it does a movement
static void MoveOnBoard(MultipleSourceMovesListCell* list, Board board, Player player)
{
	SingleSourceMovesListCell* currListCell = list->single_source_moves_list->head;
	CheckersPos* currPos = currListCell->position, *nextPos;

	if (list->single_source_moves_list->tail->captures > 0)
		MoveOnBoardAuxCapture(list, board, player);

	else //assumption - in the list there's at least two cells (source and destination)
	{
		nextPos = currListCell->next->position;
		MovePieceByTurn(board, currPos, nextPos, player);
		printf("%c%c->%c%c \n", currPos->row, currPos->col, nextPos->row, nextPos->col);
	}
}

//The function gets a single list, a board and a player
//The function move the piece with maximum captures
static void MoveOnBoardAuxCapture(MultipleSourceMovesListCell* list, Board board, Player player)
{
	SingleSourceMovesListCell* currListCell = list->single_source_moves_list->head, *nextListCell;
	CheckersPos* currPos = currListCell->position, *nextPos;

	printf("%c%c", currPos->row, currPos->col);
	while (currListCell)
	{
		nextListCell = currListCell->next;
		if (nextListCell)
		{
			currPos = currListCell->position;
			nextPos = currListCell->next->position;
			MovePieceByTurnAndCapture(board, currPos, nextPos, player);
			printf("->%c%c", nextPos->row, nextPos->col);
		}
		currListCell = nextListCell;
	}
	printf("\n");
}

//The function gets a board and player which its turn to play (the starting_player it the first player)
//The function plays a game in which the computer decides on the moves of both players (the computer plays against itself)
//The function will print the board that was received as an input to the function
//In each turn the function will print the player which its turn and the executed move
void PlayGame(Board board, Player starting_player)
{
	BOOL victory = FALSE;
	Player opponent;

	PrintBoard(board);
	PrintTurn(starting_player);

	while (!victory)
	{
		Turn(board, starting_player);
		victory = IsThereVictory(board, starting_player);
		opponent = ShiftPlayer(starting_player);
		PrintTurn(opponent);
		starting_player = opponent;
	}
}

//The function gets a player
//The function prints the message before th turn starts
static PrintTurn(Player player)
{
	if (player == TOP_PLAYER)
		printf("player TOP_DOWN'S turn\n");
	else //player == BOTTOM_PLAYER
		printf("player BOTTOM_UP'S turn\n");
}


//The function gets a board and a player
//The function returns if there's a victory
BOOL IsThereVictory(Board board, Player player)
{
	BOOL VictoryFromLastRow;
	BOOL VictoryFormCaptures;
	Player opponent = ShiftPlayer(player);


	VictoryFromLastRow = IsThereAPieceOnTheLastRow(board);
	if (VictoryFromLastRow)
		return TRUE;

	VictoryFormCaptures = AnyOpponentPieceLeft(board, opponent);
	if (VictoryFormCaptures)
		return TRUE;
	else
		return FALSE;
}

//The function gets a board and a player
//The function returns if there's a victory, if the player moved to the opponent first row (if BOTTOM_PLAYER came to row 'A' or TOP_PLAYER came to row 'H')
BOOL IsThereAPieceOnTheLastRow(Board board)
{
	int colNum;

	for (colNum = 0; colNum < BOARD_SIZE; colNum++) 
	{
		if ((board[ROW_A][colNum] == BOTTOM_PLAYER) || (board[ROW_H][colNum] == TOP_PLAYER))
			return TRUE;
	}
	return FALSE;
}

//The function gets a board and a player
//The function returns if there's a victory,  if the opponent has no pieces then the game is over
BOOL AnyOpponentPieceLeft(Board board, Player player)
{
	int rowNum, colNum;

	for (rowNum = 0; rowNum < BOARD_SIZE; rowNum++)
	{
		for (colNum = 0; colNum < BOARD_SIZE; colNum++)
		{
			if (board[rowNum][colNum] == player)
				return FALSE;
		}
	}
	return TRUE;
}