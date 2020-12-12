#pragma once

#include "tree.h"
#include "board_and_general.h"

typedef struct _SingleSourceMovesListCell
{
	CheckersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
void MakeEmptySingleSourceMovesList(SingleSourceMovesList* list);
void InsertDataToBeginningOfList(SingleSourceMovesList* res, CheckersPos* pos, unsigned short captures);
SingleSourceMovesListCell* CreateNewSingleSourceMovesListCell(CheckersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void InsertNodeToBeginningOfList(SingleSourceMovesList* res, SingleSourceMovesListCell* newHead);
BOOL IsEmptySingleSourceMovesList(SingleSourceMovesList list);
void FreeSingleSourceMovesList(SingleSourceMovesList* list);