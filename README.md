# Checkers
Console application of a checkers game in which the computer competes against itself, final project of Advanced Programming course (2019B).

In the board of the checkers there's 8 rows and 8 columns. 
The position is defined by two characters: a character for the row (A to H) and a character for the column (1 to 8).

## Rules of the game:
- In the game there is two players called T (for 'Top') and B (for 'Bottom').
- The game operates only on the grey checkers when T is moving from top to bottom and B is moving from bottom to the top.
- Each player has 12 pieces at the beginning of the game and advances at his own turn. 
- A pieces can be moved to one of the two checkers that are next to him on his left, or his right, whereas it's available.
- In case the checker is not available and contains a opponent's piece, but the checker afterwards is available, the player can hop over the opponent's piece and eliminate it from the board - That move called a capture!
In case another capture is available after capturing, the player can keep hoping over and in that way keep capturing more opponent's pieces.	

## The game finishes when one of the scenarios happens:
1) One of the Players has no more pieces.
2) When one of T pieces reaches line H.
3) When one of B pieces reaches line A.

