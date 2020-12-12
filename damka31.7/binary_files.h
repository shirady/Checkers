#pragma once

#include "board_and_general.h"

#define TWO_BITS 2
#define OPEN_FILE_ERROR_CODE -1

#define MASK_T 0x4000;         //0100 0000 0000 0000
#define MASK_B 0x8000;         //1000 0000 0000 0000
#define MASK_COL 0xC000;       //1100 0000 0000 0000
#define EMPTY_ROW_BITS 0x0000; //0000 0000 0000 0000

void StoreBoard(Board board, char* filename);
void LoadBoard(char* filename, Board borad);
void OpenFileCheck(void* ptr, char* filename);
unsigned int GetFileSize(FILE* file);
