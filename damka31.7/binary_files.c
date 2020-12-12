#pragma once
#include "binary_files.h"

static unsigned short UpdateRow(unsigned short rowBits, int colNum, Player player);
static Player LoadPiece(unsigned short rowBits, int colNum);

//The function gets a board and a name of binary file
//The function stores the board in the binary file
//Each square will be saves in two bits by using the values: 00 empty square, 01 a piece of TOP_DOWN player, 10 a piece of BOTTOM_UP player
//Each row will be saved from left to right
void StoreBoard(Board board, char* filename)
{
	unsigned short rowBits; //since a row contains 8 squares and each square is saved in 2 bits the total bits of a row is 16 bits, which is 2 bytes
	unsigned int rowNum, colNum;
	Player player;
	FILE* fileOutput;

	fileOutput = fopen(filename, "wb");
	OpenFileCheck(fileOutput, filename);

	for (rowNum = 0; rowNum < BOARD_SIZE; rowNum++)
	{
		rowBits = EMPTY_ROW_BITS; //initialize the row to an empty row (0 in all bits) 
		for (colNum = 0; colNum < BOARD_SIZE; colNum++)
		{
			player = board[rowNum][colNum];
			if (player == TOP_PLAYER || player == BOTTOM_PLAYER)
				rowBits = UpdateRow(rowBits, colNum, player); //updates the row for each column (a specific square) if there's a player in it
		}
		fwrite(&rowBits, sizeof(unsigned short), 1, fileOutput);
	}
	fclose(fileOutput);
}

//The function gets a row (each two bits are a square on the board), the number of the column and a player
//The function updates two bits by in mentioned square
static unsigned short UpdateRow(unsigned short rowBits, int colNum, Player player)
{
	unsigned short maskT = MASK_T;
	unsigned short maskB = MASK_B;
	unsigned short movement = colNum * TWO_BITS; //the shifts in the mask

	if (player == TOP_PLAYER)
		rowBits = rowBits | (maskT >> movement);
	else // (player == BOTTOM_PLAYER)
		rowBits = rowBits | (maskB >> movement);

	return rowBits;
}

//The function gets a pointer and a file name
//The function checks if the opening of the file succeeded, otherwise it prints error message (using the name of the file) and exits the program
void OpenFileCheck(void* ptr, char* filename)
{
	if (!ptr)
	{
		fprintf(stderr, "error opening input file %s!\n", filename);
		exit(OPEN_FILE_ERROR_CODE);
	}
}

//The function gets a name of a binary file (which was created in StoreBoard function) and a board
//The function load the board from the binary file to the board variable
void LoadBoard(char* filename, Board board)
{
	unsigned short rowBits;
	unsigned int rowNum = 0, colNum;
	Player player;
	FILE* fileInput;
	long int fileSize;

	fileInput = fopen(filename, "rb");
	OpenFileCheck(fileInput, filename);
	fileSize = GetFileSize(fileInput);

	while (ftell(fileInput) < fileSize)
	{
		fread(&rowBits, sizeof(unsigned short), 1, fileInput);

		for (colNum = 0; colNum < BOARD_SIZE; colNum++)
		{
			player = LoadPiece(rowBits, colNum);
			board[rowNum][colNum] = player;
		}
		rowNum++;
	}
	fclose(fileInput);
}

//The function gets a binary file
//The function returns the size of the binary file (in bytes)
unsigned int GetFileSize(FILE* file)
{
	unsigned int fileSize;

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	return fileSize;
}

//The function gets a row (each two bits represent a square in it) and a column number
//The function returns the player which the piece is his
static Player LoadPiece(unsigned short rowBits, int colNum)
{
	Player player;
	unsigned short colMask = MASK_COL;
	unsigned short movement = colNum * TWO_BITS;  //the shifts in the mask
	unsigned short backToLSB = (BOARD_SIZE - colNum - 1)*TWO_BITS; //puts the two bits in the LSB
	unsigned short playerBits = rowBits & (colMask >> movement);

	playerBits = playerBits >> backToLSB; //put the two bits in the LSB so we can calculate easily the number
	switch (playerBits)
	{
	case 1: //0000 0000 0000 0001
		player = TOP_PLAYER;
		break;
	case 2: //0000 0000 0000 0010
		player = BOTTOM_PLAYER;
		break;
	default:
		player = NO_PLAYER;
		break;
	}
	return player;
}
