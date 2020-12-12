#pragma once

#include "board_and_general.h"

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	CheckersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2]; //next_move[0] is the left move, next_move[1]is the right move
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

SingleSourceMovesTree* FindSingleSourceMoves(Board board, CheckersPos* src);
void FreeTree(SingleSourceMovesTree* moves_tree);