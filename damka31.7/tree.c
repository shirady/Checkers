#include "tree.h"

static void CreateNode(SingleSourceMovesTree* moves_tree, Board board, BoardCell currentCell, Player player, BOOL moveLeft);
static SingleSourceMovesTreeNode* CreateDirectionNode(Board board, Player player, BoardCell sourceCell, BoardCell targetCell, int captureCount);
static SingleSourceMovesTreeNode* CreateCaptureNodeRec(Board board, Player player, BoardCell source, BoardCell captureCell, int captureCount);
static SingleSourceMovesTreeNode* AllocateTreeNode(Board board, CheckersPos *pos, unsigned short captureCount);
static void freeTreeRec(SingleSourceMovesTreeNode *root);
static BOOL AuxRightAndLeftInRec(Board board, SingleSourceMovesTreeNode* node, BoardCell CellAfterCapture, BoardCell CellAfterCaptureDirection, Player player, BOOL moveLeft);

//The function gets a board with given situation and a square on the board (row 'A' to 'H' and column '1' to '8')
//If there's a piece on the specified square the function returns a binary tree of its possible movements, otherwise it returns NULL
//Assumption: if the piece exists and blocked: the binary tree that will be returned is a source of the binary tree with NULL tree node at its left and  at its right
SingleSourceMovesTree* FindSingleSourceMoves(Board board, CheckersPos* src)
{
	SingleSourceMovesTree* moves_tree;
	BoardCell currentCell = CurrentBoardCell(src);
	Player player = GetPlayer(board, currentCell);

	if (player == NO_PLAYER)
		return NULL;

	moves_tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	CheckAllocation(moves_tree);
	moves_tree->source = AllocateTreeNode(board, src, NO_CAPTURES);

	CreateNode(moves_tree, board, currentCell, player, LEFT);
	CreateNode(moves_tree, board, currentCell, player, RIGHT);

	return moves_tree;
}

//The function gets a binary tree, a board, the current cell on the board, a player and a direction (left and right)
//The function maps the situation if its a movement or a capture (or none of them) and create the suitable tree node
static void CreateNode(SingleSourceMovesTree* moves_tree, Board board, BoardCell currentCell, Player player, BOOL moveLeft)
{
	Player playerTarget;
	BoardCell targetCell = CalculateCellMoveForPlayer(currentCell, player, ONE_MOVE, moveLeft);
	BOOL isInBoundTarget = CheckASquare(board, targetCell, &playerTarget);
	int nextMove = GetNextMove(moveLeft);

	if (isInBoundTarget)
	{
		if (playerTarget == NO_PLAYER) //a movement
			moves_tree->source->next_move[nextMove] = CreateDirectionNode(board, player, currentCell, targetCell, NO_CAPTURES);
		else if (playerTarget != player) //potential capture
		{
			BoardCell CellAfterCapture = CalculateCellMoveForPlayer(currentCell, player, CAPTURE_MOVE, moveLeft);
			if (GetPlayer(board, CellAfterCapture) == NO_PLAYER) //The cell after capture is empty
				moves_tree->source->next_move[nextMove] = CreateCaptureNodeRec(board, player, currentCell, CellAfterCapture, ONE_CAPTURE);
		}
	}
}

//The function gets a board, a player, a cell on the board, a cell that will be the cell after the piece capture an opponent's piece and a number of captures
//The function returns the nodes of the binary tree (the sub-tree) of the steps which are captures (using recursion)
static SingleSourceMovesTreeNode* CreateCaptureNodeRec(Board board, Player player, BoardCell source, BoardCell CellAfterCapture, int captureCount)
{
	SingleSourceMovesTreeNode* node;
	Player playerInCaptureCell = GetPlayer(board, CellAfterCapture);

	if (!IsInBound(CellAfterCapture)) //if the cell after capture is out of bound
		return NULL;
	if (playerInCaptureCell =! NO_PLAYER) //if the close cell is empty it's not a capture
		return NULL;
	else
	{
		node = CreateDirectionNode(board, player, source, CellAfterCapture, captureCount);
		BoardCell CellAfterCaptureLeft = CalculateCellMoveForPlayer(CellAfterCapture, player, CAPTURE_MOVE, LEFT);
		BoardCell CellAfterCaptureRight = CalculateCellMoveForPlayer(CellAfterCapture, player, CAPTURE_MOVE, RIGHT);

		if (AuxRightAndLeftInRec(board, node, CellAfterCapture, CellAfterCaptureLeft, player, LEFT))
			node->next_move[NEXT_MOVE_LEFT] = CreateCaptureNodeRec(node->board, player, CellAfterCapture, CellAfterCaptureLeft, captureCount + 1);

		if (AuxRightAndLeftInRec(board, node, CellAfterCapture, CellAfterCaptureRight, player, RIGHT))
			node->next_move[NEXT_MOVE_RIGHT] = CreateCaptureNodeRec(node->board, player, CellAfterCapture, CellAfterCaptureRight, captureCount + 1);

		return node;
	}
}

//The function gets a board, current node of the binary tree, the cell after capture on the board and the next cell after capture in a specific direction (left or right), a player and a direction as mentioned before
//The function returns if there's another capture from the specified situation (a sequence of captures) 
static BOOL AuxRightAndLeftInRec(Board board, SingleSourceMovesTreeNode* node, BoardCell CellAfterCapture, BoardCell CellAfterCaptureDirection, Player player, BOOL moveLeft)
{
	Player playerOnDirection;
	Player playerCellAfterCaptureDirection = GetPlayer(node->board, CellAfterCaptureDirection);
	BoardCell captureCellCloseDirection = CalculateCellMoveForPlayer(CellAfterCapture, player, ONE_MOVE, moveLeft);
	BOOL isDirectionInBound = CheckASquare(board, captureCellCloseDirection, &playerOnDirection);

	if (isDirectionInBound && playerOnDirection != player && playerOnDirection != NO_PLAYER && playerCellAfterCaptureDirection == NO_PLAYER)
		return TRUE;
	else
		return FALSE;
}

//The function gets a board, a player, a cell on the board, a cell on the board after movement and the number of captures of the piece
//The function returns a tree node of the movement
static SingleSourceMovesTreeNode* CreateDirectionNode(Board board, Player player, BoardCell sourceCell, BoardCell targetCell, int captureCount)
{
	SingleSourceMovesTreeNode* NewNode;
	CheckersPos *posDirection;

	Board targetBoard;
	memcpy(targetBoard, board, BOARD_SIZE * BOARD_SIZE * sizeof(unsigned char));

	if (IsCapture(sourceCell, targetCell))
	{
		BOOL moveLeft = IsLeft(sourceCell, targetCell);
		BoardCell captureCell = CalculateCellMoveForPlayer(sourceCell, player, ONE_MOVE, moveLeft);
		PieceAfterCapture(targetBoard, sourceCell, captureCell, targetCell, player);
	}
	else
		MovePiece(targetBoard, sourceCell, targetCell, player);

	posDirection = BuildPosition(targetCell);
	NewNode = AllocateTreeNode(targetBoard, posDirection, captureCount);
	return NewNode;
}

//The function gets a board, a position (row 'A' to 'H' and column '1' to '8') and the number of captures of the piece
//The function returns the node of the binary tree
SingleSourceMovesTreeNode* AllocateTreeNode(Board board, CheckersPos *pos, unsigned short captureCount)
{
	SingleSourceMovesTreeNode* node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	CheckAllocation(node);

	memcpy(node->board, board, BOARD_SIZE * BOARD_SIZE * sizeof(unsigned char));
	node->pos = pos;
	node->total_captures_so_far = captureCount;
	node->next_move[NEXT_MOVE_LEFT] = NULL;
	node->next_move[NEXT_MOVE_RIGHT] = NULL;
	return node;
}

//The function gets the binary tree
//The function frees the allocated memory of the binary tree
void FreeTree(SingleSourceMovesTree* moves_tree)
{
	freeTreeRec(moves_tree->source);
	free(moves_tree);
}

//The function gets the root of the binary tree
//The function frees the allocated memory of the mentioned node
static void freeTreeRec(SingleSourceMovesTreeNode *root)
{
	if (root)
	{
		if (root->next_move[NEXT_MOVE_LEFT])
			freeTreeRec(root->next_move[NEXT_MOVE_LEFT]);
		if (root->next_move[NEXT_MOVE_RIGHT])
			freeTreeRec(root->next_move[NEXT_MOVE_RIGHT]);

		free(root->pos);
		free(root);
	}
}