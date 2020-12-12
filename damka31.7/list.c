#include "list.h"

static SingleSourceMovesList* FindSingleSourceOptimalMoveRec(SingleSourceMovesTreeNode* root);
static SingleSourceMovesList* ChooseList(SingleSourceMovesList* leftSubTreeList, SingleSourceMovesList* rightSubTreeList);
static SingleSourceMovesList* RandomList(SingleSourceMovesList* leftSubTreeList, SingleSourceMovesList* rightSubTreeList);
static SingleSourceMovesList* BuildList(SingleSourceMovesTreeNode* root);

//The function gets a binary tree of a specific piece
//The function returns the optimal move with the maximum captures of the optional movements in the tree
//If there's more than one move with the same number of captures it returns one of them
//Assumption: if the piece exists, but blocked the binary tree that will be received is a source with NULL tree node in the left and in the right - in that case there's no moves, that's why the list that will be returned is NULL
//Assumption: a returned list contains at least two cells
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* movesList;

	if (moves_tree->source) //if the tree is not NULL
	{
		if (moves_tree->source->next_move[NEXT_MOVE_LEFT] || moves_tree->source->next_move[NEXT_MOVE_RIGHT]) //is the tree has at least one move
		{
			movesList = FindSingleSourceOptimalMoveRec(moves_tree->source);
			return movesList;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

//The function gets a tree node of the binary tree
//The function returns the list of the optimal move
static SingleSourceMovesList* FindSingleSourceOptimalMoveRec(SingleSourceMovesTreeNode* treeNode)
{
	SingleSourceMovesList *leftSubTreeList, *rightSubTreeList, *resList;

	if (!treeNode->next_move[NEXT_MOVE_LEFT] && !treeNode->next_move[NEXT_MOVE_RIGHT]) //leaf of the binary tree
		return BuildList(treeNode); //in each leaf we build a list
	else
	{
		if (treeNode->next_move[NEXT_MOVE_LEFT])
			leftSubTreeList = FindSingleSourceOptimalMoveRec(treeNode->next_move[NEXT_MOVE_LEFT]);
		else
			leftSubTreeList = NULL;

		if (treeNode->next_move[NEXT_MOVE_RIGHT])
			rightSubTreeList = FindSingleSourceOptimalMoveRec(treeNode->next_move[NEXT_MOVE_RIGHT]);
		else
			rightSubTreeList = NULL;

		resList = ChooseList(leftSubTreeList, rightSubTreeList);
		InsertDataToBeginningOfList(resList, treeNode->pos, treeNode->total_captures_so_far);
		return resList;
	}
}

//The function gets a node of the binary tree
//The function returns a new list of the optimal move
static SingleSourceMovesList* BuildList(SingleSourceMovesTreeNode* node)
{
	SingleSourceMovesList* list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	CheckAllocation(list);
	MakeEmptySingleSourceMovesList(list);
	InsertDataToBeginningOfList(list, node->pos, node->total_captures_so_far);
	return list;
}

//The function gets two lists which describe the optimal move of each side (left and right)
//The function returns the list with more captures
static SingleSourceMovesList* ChooseList(SingleSourceMovesList* leftSubTreeList, SingleSourceMovesList* rightSubTreeList)
{
	if (leftSubTreeList && rightSubTreeList) //if both lists are not empty
	{
		if (leftSubTreeList->tail->captures > rightSubTreeList->tail->captures)
		{
			FreeSingleSourceMovesList(rightSubTreeList);
			return leftSubTreeList;
		}
		else if (leftSubTreeList->tail->captures == rightSubTreeList->tail->captures)
		{
			return (RandomList(leftSubTreeList, rightSubTreeList));
		}
		else //leftSubTreeList->tail->captures < rightSubTreeList->tail->captures
		{
			FreeSingleSourceMovesList(leftSubTreeList);
			return rightSubTreeList;
		}
	}
	else if (leftSubTreeList) //right list is empty
		return leftSubTreeList;
	else //left list is empty
		return rightSubTreeList;
}

//The function gets two lists with the same amount of captures
//The function returns one of lists randomly
static SingleSourceMovesList* RandomList(SingleSourceMovesList* leftSubTreeList, SingleSourceMovesList* rightSubTreeList)
{
	srand((unsigned int)(time(NULL)));
	unsigned int randomNumber = rand() % 2; //only two numbers are relevant: 0 and 1

	if (randomNumber == (unsigned int)(NEXT_MOVE_LEFT)) //randomNumber == 0
	{
		FreeSingleSourceMovesList(rightSubTreeList);
		return leftSubTreeList;
	}
	else //randomNumber == 1
	{
		FreeSingleSourceMovesList(leftSubTreeList);
		return rightSubTreeList;
	}
}

//The function gets a list
//The function initializes the head and the tail of the list to NULL
void MakeEmptySingleSourceMovesList(SingleSourceMovesList* list)
{
	list->head = list->tail = NULL;
}

//The function gets a list, a position on the board (row 'A' to 'H' a column '1' to '8') and the number of captures of the piece
//The function create a new cell in the list and puts it at the beginning of the list (the head of the list)
void InsertDataToBeginningOfList(SingleSourceMovesList* list, CheckersPos* pos, unsigned short captures)
{
	SingleSourceMovesListCell* newHead = CreateNewSingleSourceMovesListCell(pos, captures, NULL);
	InsertNodeToBeginningOfList(list, newHead);
}

//The function gets a list and a new cell to add at beginning of the list
//The function puts the mentioned cell at the beginning of the single list (the head of the list)
void InsertNodeToBeginningOfList(SingleSourceMovesList* list, SingleSourceMovesListCell* newHead)
{
	if (IsEmptySingleSourceMovesList(*list))
		list->head = list->tail = newHead;
	else
	{
		newHead->next = list->head;
		list->head = newHead;
	}
}

//The function gets the position (row 'A' to 'H' a column '1' to '8'), the number of captures of the piece and a pointer to the next cell of the list
//The function returns a new cell in a single list
SingleSourceMovesListCell* CreateNewSingleSourceMovesListCell(CheckersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* newNode;

	newNode = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	CheckAllocation(newNode);

	newNode->position = (CheckersPos*)malloc(sizeof(CheckersPos));
	CheckAllocation(newNode->position);

	newNode->position->col = position->col;
	newNode->position->row = position->row;
	newNode->captures = captures;
	newNode->next = next;

	return newNode;
}

//The function gets a single list
//The function returns if the list is empty or not
BOOL IsEmptySingleSourceMovesList(SingleSourceMovesList list)
{
	return (list.head == NULL);
}

//The function gets a list of optimal move
//The function frees the list
void FreeSingleSourceMovesList(SingleSourceMovesList* list)
{
	SingleSourceMovesListCell* curr = list->head;
	SingleSourceMovesListCell* next;

	while (curr)
	{
		next = curr->next;
		free(curr->position);
		free(curr);
		curr = next;
	}
	free(list);
}