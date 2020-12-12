#pragma once

#include "board_and_general.h"
#include "list.h"

typedef struct _MultipleSourceMovesListCell
{
	SingleSourceMovesList *single_source_moves_list;
	struct _MultipleSourceMovesListCell *next;
} MultipleSourceMovesListCell;

typedef struct _MultipleSourceMovesList
{
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
} MultipleSourceMovesList;

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);
void MakeEmptyMultipleSourceMovesListOfLists(MultipleSourceMovesList* listOfLists);
void InsertDataToBeginningOfListOfLists(MultipleSourceMovesList* listOfLists, SingleSourceMovesList* list);
void InsertNodeToBeginningOfListOfLists(MultipleSourceMovesList* listOfLists, MultipleSourceMovesListCell* newHead);
MultipleSourceMovesListCell* CreateNewMultipleSourceMovesListCell(SingleSourceMovesList* list, MultipleSourceMovesListCell* next);
BOOL IsEmptyMultipleSourceMovesListOfLists(MultipleSourceMovesList listOfLists);
void FreeMultipleMovesList(MultipleSourceMovesList* listOfLists);