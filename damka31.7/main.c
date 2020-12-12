#include "board_and_general.h"
#include "list.h"
#include "tree.h"
#include "binary_files.h"
#include "list_of_lists.h"
#include "turn_game.h"

void main()
{

}


//start board
/*

	Board board = {
{ 'W', 'T', 'W', 'T', 'W', 'T', 'W', 'T' }, //row1
{ 'T', 'W', 'T', 'W', 'T', 'W', 'T', 'W' }, //row2
{ 'W', 'T', 'W', 'T', 'W', 'T', 'W', 'T' }, //row3
{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' }, //row6
{ 'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B' }, //row7
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' }, //row8
	};

*/

// check question number 1
/*
	
void main()
{
	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[1][0] = 'T';
	board[2][1] = 'B';
	board[4][3] = 'B';
	board[5][4] = 'B';

	SingleSourceMovesTree* tr = NULL;
	CheckersPos* src;

	src = (CheckersPos*)malloc(sizeof(CheckersPos));
	CheckAllocation(src);

	src->row = 'B';
	src->col = '1';
	tr = FindSingleSourceMoves(board, src);
	printf("\n");
}

*/

// some more checks for question number 1

/*
	///////////////////////////
	board[1][0] = 'T';
	board[2][1] = 'B';
	board[4][3] = 'B';
	board[6][5] = 'B';

	src->row = 'B';
	src->col = '1';

	///////////////////////////
	board[0][3] = 'T';
	board[1][2] = 'B';
	board[1][4] = 'B';
	board[3][6] = 'B';
	board[3][4] = 'B';
	board[5][4] = 'B';

	src->col = '4';
	src->row = 'A';

	///////////////////////////
	board[6][1] = 'B';
	board[5][2] = 'T';
	board[3][4] = 'T';
	board[2][5] = 'B';

	src->col = '2';
	src->row = 'G';

	///////////////////////////
	board[6][3] = 'B';
	board[5][4] = 'B';
	board[5][2] = 'T';
	board[3][0] = 'T';

	src->col = '4';
	src->row = 'G';

	///////////////////////////
	board[1][0] = 'T';
	board[2][1] = 'B';
	board[4][3] = 'B';
	board[5][4] = 'B';

	src->col = '1';
	src->row = 'B';

	///////////////////////////
	board[5][2] = 'T';
	board[6][1] = 'B';
	board[6][3] = 'T';
	board[7][0] = 'B';
		
	src->col = '3';
	src->row = 'F';

	///////////////////////////
	board[6][1] = 'B';
	board[5][2] = 'T';
	board[3][4] = 'T';
	board[2][5] = 'B';

	src->col = '2';
	src->row = 'F';

	///////////////////////////
	board[0][3] = 'T';
	board[1][2] = 'B';
	board[2][1] = 'T';
	board[1][4] = 'B';
	board[2][5] = 'B';

	src->col = '4';
	src->row = 'A';

	///////////////////////////
	board[1][4] = 'T';
	board[2][3] = 'T';
	board[2][5] = 'B';
	board[4][5] = 'B';
	board[6][3] = 'B';

	src->col = '5';
	src->row = 'B';
*/

//check question number 2
/*
void main()
{
	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[2][3] = 'T';
	board[3][2] = 'T';
	board[3][4] = 'B';
	board[5][4] = 'B';

	SingleSourceMovesTree* moves_tree = NULL;
	CheckersPos* src;
	SingleSourceMovesList* list;

	src = (CheckersPos*)malloc(sizeof(CheckersPos));
	CheckAllocation(src);

	src->col = '4';
	src->row = 'C';
	moves_tree = FindSingleSourceMoves(board, src);
	printf("\n");
	list = FindSingleSourceOptimalMove(moves_tree);
	printf("\n");
}
*/

// some more checks for question number 2

/*
	///////////////////////////
	board[0][3] = 'T';
	board[1][2] = 'B';
	board[1][4] = 'B';
	board[3][6] = 'B';
	board[3][4] = 'B';

	src->col = '4';
	src->row = 'A';

	///////////////////////////
	board[0][3] = 'T';
	board[1][2] = 'B';
	board[2][1] = 'T';
	board[1][4] = 'B';
	board[2][5] = 'B';

	src->col = '4';
	src->row = 'A';

	///////////////////////////
	board[6][3] = 'B';
	board[5][4] = 'B';

	src->col = '4';
	src->row = 'G';

	///////////////////////////
	board[1][0] = 'T';
	board[2][1] = 'T';

	src->col = '1';
	src->row = 'B';

	///////////////////////////
	board[3][4] = 'T';
	board[4][3] = 'B';
	board[4][5] = 'B';

	src->col = '5';
	src->row = 'D';

	*/

// check question number 3
/*
void main()
{
	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[2][3] = 'T';
	board[3][2] = 'T';
	board[3][4] = 'B';
	board[5][4] = 'B';

	Player player = TOP_PLAYER;
	MultipleSourceMovesList* listOfLists;
	listOfLists =  FindAllPossiblePlayerMoves(board, player);
	printf("\n");
}
*/


// some more checks for question number 3

/*

	board[0][1] = 'T';
	board[1][2] = 'B';
	board[1][6] = 'T';
	board[3][2] = 'T';
	board[3][4] = 'T';
	board[4][3] = 'B';

	Player player = BOTTOM_PLAYER;

	///////////////////////////
	board[0][3] = 'T';
	board[1][4] = 'B';
	board[3][4] = 'B';
	board[4][1] = 'T';
	board[5][4] = 'B';
	board[5][6] = 'T';
	board[7][4] = 'B';

	Player player = TOP_PLAYER;
*/

//check questions number 4
/*

	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[0][3] = 'T';
	board[1][4] = 'B';
	board[3][4] = 'B';
	board[4][1] = 'T';
	board[5][4] = 'B';
	board[5][6] = 'T';
	board[7][4] = 'B';

	PrintBoard(board);
	Player player = TOP_PLAYER;
	Turn(board, player);
	printf("\n");
	PrintBoard(board);
	printf("\n");
*/

//check questions number 5-6
/*
void main()
{
	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	Board targetBoard;

	board[0][1] = TOP_PLAYER;
	board[0][3] = BOTTOM_PLAYER;
	board[0][5] = TOP_PLAYER;
	board[0][7] = BOTTOM_PLAYER;
	board[4][1] = BOTTOM_PLAYER;
	board[4][5] = BOTTOM_PLAYER;
	board[6][3] = TOP_PLAYER;
	board[6][7] = TOP_PLAYER;

	char filename[6] = "a.bin";
	StoreBoard(board, filename);
	LoadBoard(filename, targetBoard);
	printMat(targetBoard);
}
*/

//check question number 7

/*
	Board board = {
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
	{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
	{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[0][1] = 'T';
	board[0][3] = 'T';
	board[0][5] = 'T';
	board[0][7] = 'T';

	board[1][0] = 'T';
	board[1][2] = 'T';
	board[1][4] = 'T';
	board[1][6] = 'T';

	board[2][1] = 'T';
	board[2][3] = 'T';
	board[2][5] = 'T';
	board[2][7] = 'T';

	board[5][0] = 'B';
	board[5][2] = 'B';
	board[5][4] = 'B';
	board[5][6] = 'B';

	board[6][1] = 'B';
	board[6][3] = 'B';
	board[6][5] = 'B';
	board[6][7] = 'B';

	board[7][0] = 'B';
	board[7][2] = 'B';
	board[7][4] = 'B';
	board[7][6] = 'B';

	Player starting_player = TOP_PLAYER;
	PlayGame(board, starting_player);
*/

// some more checks for question number 7

/*
	Board board = {
{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row1
{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row2
{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row3
{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row4
{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row5
{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row6
{ 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ' }, //row7
{ ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' }, //row8
	};

	board[0][1] = 'T';
	board[0][3] = 'T';
	board[0][5] = 'T';
	board[0][7] = 'T';

	board[1][0] = 'T';
	board[1][2] = 'T';
	board[1][4] = 'T';
	board[1][6] = 'T';

	board[2][1] = 'T';
	board[2][3] = 'T';
	board[2][5] = 'T';
	board[2][7] = 'T';

	board[5][0] = 'B';
	board[5][2] = 'B';
	board[5][4] = 'B';
	board[5][6] = 'B';

	board[6][1] = 'B';
	board[6][3] = 'B';
	board[6][5] = 'B';
	board[6][7] = 'B';

	board[7][0] = 'B';
	board[7][2] = 'B';
	board[7][4] = 'B';
	board[7][6] = 'B';

	Player starting_player = BOTTOM_PLAYER;
	PlayGame(board, starting_player);
*/

//printf("%d\n", _CrtDumpMemoryLeaks()); //prints 0 when there's no memory leaks, otherwise 1

