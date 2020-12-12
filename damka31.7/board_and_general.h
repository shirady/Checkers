#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <crtdbg.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define BOARD_SIZE 8

#define LEFT 1
#define RIGHT 0

#define NEXT_MOVE_LEFT 0
#define NEXT_MOVE_RIGHT 1 

#define TOP_PLAYER 'T'
#define BOTTOM_PLAYER 'B'
#define NO_PLAYER ' '

#define ONE_MOVE 1
#define CAPTURE_MOVE 2

#define NO_CAPTURES 0
#define ONE_CAPTURE 1

#define MALLOC_ERROR_CODE -1

typedef struct _CheckersPos
{
	char row; //'A' to 'H'
	char col; //'1' to '8'
} CheckersPos;

typedef struct _BoardCell
{
	int rowNum; //0 to 7
	int colNum; //0 to 7
} BoardCell;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

void CheckAllocation(void* ptr);
BoardCell CalculateCellMoveForPlayer(BoardCell current, Player player, int steps, BOOL moveLeft);
Player GetPlayer(Board board, BoardCell currentCell);
BOOL IsInBound(BoardCell cell);
BOOL CheckASquare(Board board, BoardCell cell, Player* player);
BoardCell CurrentBoardCell(CheckersPos* src);
void RowColNumToChar(BoardCell cell, CheckersPos *posDirection);
CheckersPos* BuildPosition(BoardCell cell);
void MovePiece(Board board, BoardCell sourceCell, BoardCell destCell, Player player);
void PieceAfterCapture(Board board, BoardCell sourceCell, BoardCell captureCell, BoardCell destCell, Player player);
BOOL IsCapture(BoardCell sourceCell, BoardCell targetCell);
BOOL IsLeft(BoardCell sourceCell, BoardCell targetCell);
void PrintBoard(Board board);
Player ShiftPlayer(Player player);
int GetNextMove(BOOL moveLeft);
void MovePieceByTurn(Board board, CheckersPos* currPos, CheckersPos* NextPos, Player player);
void MovePieceByTurnAndCapture(Board board, CheckersPos* currPos, CheckersPos* NextPos, Player player);

