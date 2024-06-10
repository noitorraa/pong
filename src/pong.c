#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 80
#define SCORE_FOR_WIN 21

void drawField(int leftRocket, int rightRocket, int ballX, int ballY);
void clear(void);
void showWinner(char winner[]);
void drawScore(int leftScore, int rightScore);

int main(void) {
    system("stty -icanon");
    int leftRacket = ROWS / 2, rightRacket = ROWS / 2;
    int ballX = ROWS / 2, ballY = COLS / 2;
    int dirY = 1, dirX = 1;
    char input = 'f';
    int leftScore = 0, rightScore = 0;
    do {
        input = getchar();
        leftRacket = (input == 'a' && leftRacket > 1) ? leftRacket - 1 : leftRacket;
        leftRacket = (input == 'z' && leftRacket < ROWS - 2) ? leftRacket + 1 : leftRacket;
        rightRacket = (input == 'k' && rightRacket > 1) ? rightRacket - 1 : rightRacket;
        rightRacket = (input == 'm' && rightRacket < ROWS - 2) ? rightRacket + 1 : rightRacket;
        if (input == 'a' || input == 'z' || input == 'k' || input == 'm' || input == ' ') {
            if ((ballX == ROWS - 1 && (dirX == 1 || dirX == -1) && dirY == 1) ||
                (ballX == 0 && (dirX == 1 || dirX == -1) && dirY == -1)) {
                dirY *= -1;
            } else if (ballY == COLS - 3 && (dirX == 1 || dirX == -1) && (dirY == 1 || dirY == -1) &&
                       (ballX == rightRacket - 1 || ballX == rightRacket || ballX == rightRacket + 1)) {
                dirX *= -1;
            } else if (ballY == 2 && (dirX == 1 || dirX == -1) && (dirY == 1 || dirY == -1) &&
                       (ballX == leftRacket - 1 || ballX == leftRacket || ballX == leftRacket + 1)) {
                dirX *= -1;
            }
            ballX += dirY;
            ballY += dirX;
            if (ballY == 1 || ballY == COLS - 2) {
                if (ballY == 1) {
                    rightScore++;
                } else if (ballY == COLS - 2) {
                    leftScore++;
                }
                leftRacket = ROWS / 2;
                rightRacket = ROWS / 2;
                ballX = ROWS / 2;
                ballY = COLS / 2;
                dirX *= -1;
                dirY *= -1;
            }
        }
        clear();
        drawField(leftRacket, rightRacket, ballX, ballY);
        drawScore(leftScore, rightScore);
        if (leftScore == SCORE_FOR_WIN) {
            showWinner("Left");
            break;
        } else if (rightScore == SCORE_FOR_WIN) {
            showWinner("Right");
            break;
        }
    } while (input != 'q');
}

void drawField(int leftRocket, int rightRocket, int ballX, int ballY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j == 1 && (i == leftRocket + 1 || i == leftRocket || i == leftRocket - 1)) {
                printf("[");
            } else if (j == COLS - 2 && (i == rightRocket + 1 || i == rightRocket || i == rightRocket - 1)) {
                printf("]");
            } else if (i == ballX && j == ballY) {
                printf("*");
            } else if (j == COLS / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void clear() {
    printf("\033[2J");
    printf("\033[0;0f");
}

void showWinner(char winner[]) { printf("%s player is winner\n", winner); }

void drawScore(int leftScore, int rightScore) {
    printf("Left player score: %d\n", leftScore);
    printf("Right player score: %d\n", rightScore);
}