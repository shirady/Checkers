#include "list_of_lists.h"

static SingleSourceMovesList* ActionsBeforeAddingToList(Board board, Player player, BoardCell cell);
static MultipleSourceMovesList* BuildListOfLists();

//The function gets a board and a player
//The function returns the list of the optimal moves from each square of the board which contains a piece of the player which is not blocked (the piece has a movement)
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
	BoardCell cell;
	SingleSourceMovesList* list =NULL;
	MultipleSourceMovesList* listOfLists =NULL;
	BOOL isTheresList = FALSE;

	for (cell.rowNum = 0; cell.rowNum < BOARD_SIZE; cell.rowNum++)
	{
		for (cell.colNum = 0; cell.colNum < BOARD_SIZE; cell.colNum++)
		{
			if (board[cell.rowNum][cell.colNum] == player)
			{
				if (!isTheresList) //the build of list of lists happens only for the first time, afterward it just to add the cells in this list
				{
					listOfLists = BuildListOfLists();
					isTheresList = TRUE;
				}
				list = ActionsBeforeAddingToList(board, player, cell);
				if (list) //if the list is not empty
					InsertDataToBeginningOfListOfLists(listOfLists, list);
			}
		}
	}
	return listOfLists;
}

//The function gets a board, a player and a cell on board
//The function returns the single list: it creates the binary tree of the moves and a list of the optimal moves and frees the tree
static SingleSourceMovesList* ActionsBeforeAddingToList(Board board, Player player, BoardCell cell)
{
	CheckersPos* pos = BuildPosition(cell);
	SingleSourceMovesTree* moves_tree = FindSingleSourceMoves(board, pos);
	SingleSourceMovesList* list = FindSingleSourceOptimalMove(moves_tree);
	FreeTree(moves_tree);
	return list;
}

//The function creates for the first time the multiple list (list of lists) and returns it
static MultipleSourceMovesList* BuildListOfLists()
{
	MultipleSourceMovesList* listOfLists = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	CheckAllocation(listOfLists);
	MakeEmptyMultipleSourceMovesListOfLists(listOfLists);
	return listOfLists;
}

//The function gets the multiple list (list of lists)
//The function initializes the head and the tail of the list to NULL
void MakeEmptyMultipleSourceMovesListOfLists(MultipleSourceMovesList* listOfLists)
{
	listOfLists->head = listOfLists->tail = NULL;
}

//The function gets the multiple list (list of lists) and a single list
//The function create a new cell in the list and put it at the beginning of the list (the head of the list)
void InsertDataToBeginningOfListOfLists(MultipleSourceMovesList* listOfLists, SingleSourceMovesList* list)
{
	MultipleSourceMovesListCell* newHead = CreateNewMultipleSourceMovesListCell(list, NULL);
	InsertNodeToBeginningOfListOfLists(listOfLists, newHead);
}

//The function gets a multiple list and a new cell to add to the list
//The function puts the mentioned cell at the beginning of the multiple list (the head of the list)
void InsertNodeToBeginningOfListOfLists(MultipleSourceMovesList* listOfLists, MultipleSourceMovesListCell* newHead)
{
	if (IsEmptyMultipleSourceMovesListOfLists(*listOfLists))
		listOfLists->head = listOfLists->tail = newHead;
	else
	{
		newHead->next = listOfLists->head;
		listOfLists->head = newHead;
	}
}

//The function gets a multiple list and a pointer to the next cell of the list
//The function returns a new cell in a multiple list
MultipleSourceMovesListCell* CreateNewMultipleSourceMovesListCell(SingleSourceMovesList* list, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* newNode = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	CheckAllocation(newNode);

	newNode->single_source_moves_list = list;
	newNode->next = next;
	return newNode;
}

//The function gets a multiple list
//The function returns if the list is empty or not
BOOL IsEmptyMultipleSourceMovesListOfLists(MultipleSourceMovesList listOfLists)
{
	return (listOfLists.head == NULL);
}

//The function gets a list of all possible player moves
//The function frees the multiple list
//Assumption: in the list of lists all the cells (which are lists) are not NULL
void FreeMultipleMovesList(MultipleSourceMovesList* listOfLists)
{
	MultipleSourceMovesListCell* currCellListOfLists = listOfLists->head, *nextCellListOfLists;
	SingleSourceMovesList* currCellList =  currCellListOfLists->single_source_moves_list;

	while (currCellListOfLists)
	{
		nextCellListOfLists = currCellListOfLists->next;
		FreeSingleSourceMovesList(currCellListOfLists->single_source_moves_list);
		free(currCellListOfLists);
		currCellListOfLists = nextCellListOfLists;
	}
	free(listOfLists);
}