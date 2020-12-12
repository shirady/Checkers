#include "board_and_general.h"

//The function gets a pointer
//The function checks if the memory allocation succeeded, otherwise it prints error message and exits the program
void CheckAllocation(void* ptr)
{
	if (!ptr)
	{
		fprintf(stderr, "memory allocation error!\n");
		exit(MALLOC_ERROR_CODE);
	}
}

//The function gets the current cell on board (row and column 0 to 7), player, steps (1 as one move or 2 as capture) and the direction (left or right)
//The function returns the target cell (regular movement or a capture step)
BoardCell CalculateCellMoveForPlayer(BoardCell current, Player player, int steps, BOOL moveLeft)
{
	BoardCell cell;

	if (player == TOP_PLAYER)
		cell.rowNum = current.rowNum + steps; //T moves top down (from row 0 to row 7)
	else   // player == BOTTOM_PLAYER
		cell.rowNum = current.rowNum - steps; //B moves bottom up (from row t to row 0)

	if (moveLeft)
		cell.colNum = current.colNum - steps; // left (from column 7 to 0)
	else
		cell.colNum = current.colNum + steps; //right (from column 0 to 7)

	return cell;
}


//The function gets the board and a cell on the board (row and column 0 to 7)
//The function returns the player in which its piece is on the specified cell
Player GetPlayer(Board board, BoardCell currentCell)
{
	char val = board[currentCell.rowNum][currentCell.colNum];
	if (val == TOP_PLAYER || val == BOTTOM_PLAYER)
		return val;

	return NO_PLAYER;
}

//The function gets a cell on the board
// The function returns if the cell is in bound: row and column numbers are 0 to 7 and the color of the square is black
BOOL IsInBound(BoardCell cell)
{
	if ((cell.rowNum >= 0) && (cell.rowNum < BOARD_SIZE) && (cell.colNum >= 0) && (cell.colNum < BOARD_SIZE))
	{
		if (cell.rowNum % 2 == 0)
			return (cell.colNum % 2 == 1);
		else
			return (cell.colNum % 2 == 0);
	}
	else
		return FALSE;
}

//The function gets the board, a cell on the board
//The function returns if there's a player in the specified cell on board, and also returns its player (using output parameter) 
BOOL CheckASquare(Board board, BoardCell cell, Player* player)
{
	BOOL validLocation = IsInBound(cell);

	if (validLocation)
		*player = GetPlayer(board, cell);
	return validLocation;
}

//The function gets the checkers position in characters: row 'A' to 'H' and column '1' to '8'
//The function returns the cell on board after converting it to integers 0 to 7
BoardCell CurrentBoardCell(CheckersPos* pos)
{
	BoardCell currentCell;
	currentCell.rowNum = (int)pos->row - 'A';
	currentCell.colNum = (int)pos->col - '1';
	return currentCell;
}

//The function gets the cell on board
//The function returns the position in characters (using output parameters)
void RowColNumToChar(BoardCell cell, CheckersPos *posDirection)
{
	posDirection->row = (char)(cell.rowNum + 'A');
	posDirection->col = (char)(cell.colNum + '1');
}

//The function gets the cell on board
//the function returns a pointer to the position (after allocating memory for it)
CheckersPos* BuildPosition(BoardCell cell)
{
	CheckersPos *pos;

	pos = (CheckersPos*)malloc(sizeof(CheckersPos));
	CheckAllocation(pos);
	RowColNumToChar(cell, pos);
	return pos;
}

//The function gets a board, a current cell, a destination cell on board and a player
//The function clears the current cell on the board and puts the player's piece at the destination cell on board
void MovePiece(Board board, BoardCell sourceCell, BoardCell destCell, Player player)
{
	board[sourceCell.rowNum][sourceCell.colNum] = NO_PLAYER;
	board[destCell.rowNum][destCell.colNum] = player;
}

//The function gets a board, a current cell, a destination cell, a cell of the opponent player which was captured and a player
//The function clears current cell and captured cell from the board and puts the player's piece at the destination cell on board
void PieceAfterCapture(Board board, BoardCell sourceCell, BoardCell OccupiedCell, BoardCell destCell, Player player)
{
	MovePiece(board, sourceCell, destCell, player);
	board[OccupiedCell.rowNum][OccupiedCell.colNum] = NO_PLAYER;
}

//The function gets a current cell on board and a destination cell on board
//The function returns if the mentioned step is a capture
BOOL IsCapture(BoardCell sourceCell, BoardCell targetCell)
{
	int absStep = abs(targetCell.rowNum - sourceCell.rowNum);
	return (absStep == 2);
}

//The function gets a current cell and a destination cell on board
//The function returns if the mentioned step if left
BOOL IsLeft(BoardCell sourceCell, BoardCell targetCell)
{
	int direction = targetCell.colNum - sourceCell.colNum;
	if (direction < 0)
		return LEFT;
	else
		return RIGHT;
}

//The function gets a board
//The function prints the board
void PrintBoard(Board board)
{
	unsigned int i, j;
	char col = 'A';

	printf("+-+-+-+-+-+-+-+-+-+ \n");
	printf("+ |1|2|3|4|5|6|7|8| \n");

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("|%c|", col);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] != 'W') //In the board we used there were 4 kinds of squares: T (Top-Down), B (Bottom_Up), ' '(Empty), W (White square) - which is out of bound, but was comfortable for debugging
				printf("%c|", board[i][j]);
			else
				printf("%c|", ' '); //That's way in case we used 'W' it will be printed
		}
		printf("\n");
		printf("+-+-+-+-+-+-+-+-+-+ \n");
		col = col + (char)(1);
	}
}


//The function gets a player
//The function returns its opponents
Player ShiftPlayer(Player player)
{
	if (player == TOP_PLAYER)
		return BOTTOM_PLAYER;
	else
		return TOP_PLAYER;
}

//The function gets a direction (left or right)
//The function returns the element's index in the next_move array (see: the struct of SingleSourceMovesTreeNode) 
int GetNextMove(BOOL moveLeft)
{
	BOOL nextMove;

	if (moveLeft == LEFT)
		nextMove = NEXT_MOVE_LEFT;
	else
		nextMove = NEXT_MOVE_RIGHT;

	return nextMove;
}

//The function gets a board, a current and a next position (using characters) and a player
//The function plays a turn of a move (one step)
void MovePieceByTurn(Board board, CheckersPos* currPos, CheckersPos* NextPos, Player player)
{
	BoardCell sourceCell = CurrentBoardCell(currPos);
	BoardCell destCell = CurrentBoardCell(NextPos);
	MovePiece(board, sourceCell, destCell, player);
}

//The function gets a board, a current and a next position (using characters) and a player
//The function plays a turn of a capture (two steps)
void MovePieceByTurnAndCapture(Board board, CheckersPos* currPos, CheckersPos* NextPos, Player player) //maybe add to general module
{
	BoardCell sourceCell = CurrentBoardCell(currPos);
	BoardCell destCell = CurrentBoardCell(NextPos);
	BOOL moveLeft = IsLeft(sourceCell, destCell);
	BoardCell OccupiedCell = CalculateCellMoveForPlayer(sourceCell, player, ONE_MOVE, moveLeft);
	PieceAfterCapture(board, sourceCell, OccupiedCell, destCell, player);
}