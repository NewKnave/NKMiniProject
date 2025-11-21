#include <stdio.h>

// "f" Function
// "iv" Integer Variable
// "cv" Char Variable

int fWinnerState(void);
int fCurrentPlayer(int ivIn);
void fPrintWinner(int ivIn);
void fPrintDraw(void);
void fPrintBoard(void);
void fPrintFinalBoard(void);
void fMarkBoard(int In);

char cvMark[2] = {'O', 'X'};
int ivMarkNumber = 0;

char cvBoard[9] = {
	'1', '2', '3',
	'4', '5', '6',
	'7', '8', '9'
	};

char cvFinalBoard[9] = {
	' ', ' ', ' ',
	' ', ' ', ' ',
	' ', ' ', ' '
	};

int main(void) {
	int ivFunction = 0;
	int ivTurnCounter = 0;
	int ivTurnLimit = 9;
	int ivIsValidMove = 0;

	printf("Tic Tac Toe\n");
	for(ivTurnCounter = 0; ivTurnCounter < ivTurnLimit; ivTurnCounter++)
		{
			ivFunction = (ivTurnCounter % 2);
			if(fWinnerState() > 0)
				{
					fPrintWinner(ivFunction);
					fPrintBoard();
					fPrintFinalBoard();
					return 0;
				}
			printf("\nTurn %i\n", (ivTurnCounter + 1));
			fPrintBoard();
			ivIsValidMove = fCurrentPlayer(ivFunction);
			if(ivIsValidMove == 1)
				{
					ivTurnCounter--;
				}
		}
	fPrintDraw();
	fPrintFinalBoard();
	return 0;
	} // End of Main

int fWinnerState(void) {
	int ivCheck = 0;
		// Player1 Horizontal
		if(cvBoard[0] == 'O' && cvBoard[1] == 'O' && cvBoard[2] == 'O') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[1] = '+';
			cvFinalBoard[2] = '+';
			ivCheck = 1;
			}
		else if(cvBoard[3] == 'O' && cvBoard[4] == 'O' && cvBoard[5] == 'O') {
			cvFinalBoard[3] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[5] = '+';
			ivCheck =  1;
			}
		else if(cvBoard[6] == 'O' && cvBoard[7] == 'O' && cvBoard[8] == 'O') {
			cvFinalBoard[6] = '+';
			cvFinalBoard[7] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  1;
			}

		// Player1 Vertical
		else if(cvBoard[0] == 'O' && cvBoard[3] == 'O' && cvBoard[6] == 'O') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[3] = '+';
			cvFinalBoard[6] = '+';
			ivCheck =  1;
			}
		else if(cvBoard[1] == 'O' && cvBoard[4] == 'O' && cvBoard[7] == 'O') {
			cvFinalBoard[1] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[7] = '+';
			ivCheck =  1;
			}
		else if(cvBoard[2] == 'O' && cvBoard[5] == 'O' && cvBoard[8] == 'O') {
			cvFinalBoard[2] = '+';
			cvFinalBoard[5] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  1;
			}

		//Player1 Diagonal
		else if(cvBoard[0] == 'O' && cvBoard[4] == 'O' && cvBoard[8] == 'O') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  1;
			}
		else if(cvBoard[2] == 'O' && cvBoard[4] == 'O' && cvBoard[6] == 'O') {
			cvFinalBoard[2] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[6] = '+';
			ivCheck =  1;
			}

		// Player2 Horizontal
		else if(cvBoard[0] == 'X' && cvBoard[1] == 'X' && cvBoard[2] == 'X') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[1] = '+';
			cvFinalBoard[2] = '+';
			ivCheck =  2;
			}
		else if(cvBoard[3] == 'X' && cvBoard[4] == 'X' && cvBoard[5] == 'X') {
			cvFinalBoard[3] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[5] = '+';
			ivCheck =  2;
			}
		else if(cvBoard[6] == 'X' && cvBoard[7] == 'X' && cvBoard[8] == 'X') {
			cvFinalBoard[6] = '+';
			cvFinalBoard[7] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  2;
			}

		// Player2 Vertical
		else if(cvBoard[0] == 'X' && cvBoard[3] == 'X' && cvBoard[6] == 'X') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[3] = '+';
			cvFinalBoard[6] = '+';
			ivCheck =  2;
			}
		else if(cvBoard[1] == 'X' && cvBoard[4] == 'X' && cvBoard[7] == 'X') {
			cvFinalBoard[1] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[7] = '+';
			ivCheck =  2;
			}
		else if(cvBoard[2] == 'X' && cvBoard[5] == 'X' && cvBoard[8] == 'X') {
			cvFinalBoard[2] = '+';
			cvFinalBoard[5] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  2;
			}

		// Player2 Diagonal
		else if(cvBoard[0] == 'X' && cvBoard[4] == 'X' && cvBoard[8] == 'X') {
			cvFinalBoard[0] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[8] = '+';
			ivCheck =  2;
			}
		else if(cvBoard[2] == 'X' && cvBoard[4] == 'X' && cvBoard[6] == 'X') {
			cvFinalBoard[2] = '+';
			cvFinalBoard[4] = '+';
			cvFinalBoard[6] = '+';
			ivCheck =  2;
			}
	if(ivCheck > 0) {
		return ivCheck;
		}
	return 0;
	} // End of CheckForWinner

int fCurrentPlayer(int ivIn) {
	int ivPlayerInput = 0;
	int ivMark;

	fflush(stdin);
	printf("\nPlayer%i: ", (ivIn + 1));
	scanf("%i", &ivPlayerInput);
	ivMark = (ivPlayerInput - 1);
	if(ivPlayerInput >= 1 && ivPlayerInput <= 9 )
		{
			if(cvBoard[ivMark] == 'X' || cvBoard[ivMark] == 'O')
				{
					fflush(stdin);
					printf("\nInvalid Move\n");
					return 1;
			} else {
					ivMarkNumber = ivIn;
					fMarkBoard(ivMark);
					return 0;	 
				}
	} else {
			fflush(stdin);
			printf("\nInvalid Input\n");
			return 1;
		}
	} // End of CurrentPlayer

void fPrintWinner(int ivIn) {
	if(ivIn == 0) {
		printf("\nPlayer2 Won!\n");
		}
	else if(ivIn == 1) {
		printf("\nPlayer1 Won!\n");
		}
	} // End of PrintWinner

void fPrintDraw(void) {
	printf("\nIts a draw!\n");
	fPrintBoard();
	} // End of PrintDraw

void fPrintBoard(void) {
	printf("\n");
	printf("  %c | %c | %c\n", cvBoard[0], cvBoard[1], cvBoard[2]);
	printf(" --- --- ---\n");
	printf("  %c | %c | %c\n", cvBoard[3], cvBoard[4], cvBoard[5]);
	printf(" --- --- ---\n");
	printf("  %c | %c | %c\n", cvBoard[6], cvBoard[7], cvBoard[8]);
	} // End of PrintBoard

void fPrintFinalBoard(void) {
	printf("\n");
	printf("  %c | %c | %c\n", cvFinalBoard[0], cvFinalBoard[1], cvFinalBoard[2]);
	printf(" --- --- ---\n");
	printf("  %c | %c | %c\n", cvFinalBoard[3], cvFinalBoard[4], cvFinalBoard[5]);
	printf(" --- --- ---\n");
	printf("  %c | %c | %c\n", cvFinalBoard[6], cvFinalBoard[7], cvFinalBoard[8]);
	} // End of PrintFinalBoard

void fMarkBoard(int In) {
	cvBoard[In] = cvMark[ivMarkNumber];
	} // End of MarkBoard