#pragma once

#include "board_and_general.h"
#include "list_of_lists.h"

#define NO_MOVE -1
#define ROW_A 0
#define ROW_H 7

void Turn(Board board, Player player);
void PlayGame(Board board, Player starting_player);
void AtLeastOneMove(MultipleSourceMovesList *listOfLists);
MultipleSourceMovesListCell* ChooseTheListWithMaxCaptures(MultipleSourceMovesList *listOfLists);
BOOL IsThereVictory(Board board, Player player);
BOOL IsThereAPieceOnTheLastRow(Board board);
BOOL AnyOpponentPieceLeft(Board board, Player player);
