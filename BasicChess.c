#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

#define BOARD_SIZE 8


char board[BOARD_SIZE][BOARD_SIZE] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};


void printBoard() {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int isValidMove(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}


void movePiece(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = '.';
}


int parseMove(char *move, int *x1, int *y1, int *x2, int *y2) {
    char col1, col2;
    int row1, row2;
    if (sscanf(move, "%c%d %c%d", &col1, &row1, &col2, &row2) != 4) {
        return 0; 
    }

    
    *x1 = 8 - row1;  
    *y1 = col1 - 'a'; 
    *x2 = 8 - row2;   
    *y2 = col2 - 'a'; 

    
    return isValidMove(*x1, *y1) && isValidMove(*x2, *y2);
}


void aiMove() {
    int x1, y1, x2, y2;
    while (1) {
        x1 = rand() % BOARD_SIZE;
        y1 = rand() % BOARD_SIZE;
        x2 = rand() % BOARD_SIZE;
        y2 = rand() % BOARD_SIZE;

        if (board[x1][y1] != '.' && isValidMove(x2, y2)) {
            printf("AI moves %c%d %c%d\n", 'a' + y1, 8 - x1, 'a' + y2, 8 - x2);
            movePiece(x1, y1, x2, y2);
            break;
        }
    }
}


int main() {
    srand(time(NULL));  

    
    printBoard();

    while (1) {
        char move[10];
        int x1, y1, x2, y2;

        
        printf("Enter your move (e.g., e2 e4): ");
        fgets(move, sizeof(move), stdin);
        move[strcspn(move, "\n")] = '\0'; 

        if (parseMove(move, &x1, &y1, &x2, &y2)) {
           
            if (board[x1][y1] == '.' || (board[x1][y1] >= 'a' && board[x1][y1] <= 'z')) {
                printf("Invalid move! Try again.\n");
                continue;
            }

            movePiece(x1, y1, x2, y2);
            printBoard();

            
            aiMove();
            printBoard();
        } else {
            printf("Invalid input. Try again.\n");
        }
    }

    return 0;
}

