#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Draw colorful score bar
void drawScoreBar(int score) {

    int barLength = score % 20; // bar loops every 20 points

    printf("\n ");

    if (score < 10) color(10);      // green
    else if (score < 20) color(14); // yellow
    else color(12);                 // red

    printf("[");
    for (int i = 0; i < barLength; i++)
        printf("#");
    for (int i = barLength; i < 20; i++)
        printf(" ");
    printf("]");

    color(7);
}

int playGame() {
    srand(time(0));

    int x = 1;
    int step = 0;
    int obstaclePos = rand() % 3;
    int score = 0;

    char car = '@';
    char rock = 'O';

    while (1) {

        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0) x--;
            if (ch == 77 && x < 2) x++;
        }

        system("cls");

        // ONLY CURRENT SCORE (NO HIGH SCORE)
        color(11);
        printf(" SCORE: ");
        color(10);
        printf("%d\n", score);
        color(7);

        drawScoreBar(score);
        printf("\n");

        printf("\n|--- --- ---|\n");

        // OBSTACLE DRAW
        for (int i = 0; i < 10; i++) {
            if (i == step) {
                if (obstaclePos == 0) printf("| %c        |\n", rock);
                else if (obstaclePos == 1) printf("|     %c    |\n", rock);
                else printf("|        %c |\n", rock);
            }
            else printf("|           |\n");
        }

        // PLAYER
        if (x == 0) printf("| %c        |\n", car);
        else if (x == 1) printf("|     %c    |\n", car);
        else printf("|        %c |\n", car);

        // COLLISION
        if (step == 10 && x == obstaclePos) {

            color(12);
            printf("\n  GAME OVER!\n");
            color(14);
            printf("  Final Score: %d\n\n", score);

            color(11);
            printf("+------------------+    +------------------+\n");
            printf("|     ");
            color(10); printf("RESTART"); 
            color(11); printf("      |    |      ");
            color(12); printf("QUIT");
            color(11); printf("        |\n");
            printf("+------------------+    +------------------+\n");

            color(10);
            printf("   Press R"); 
            color(7);
            printf("                       ");

            color(12);
            printf("Press Q\n");
            color(7);

            // Input loop
            while (1) {
                char ch = getch();
                if (ch == 'r' || ch == 'R') return 1;
                if (ch == 'q' || ch == 'Q') return 0;
            }
        }

        Sleep(90);

        step++;

        if (step > 10) {
            step = 0;
            score++;
            obstaclePos = rand() % 3;
        }
    }
}

int main() {
    while (1) {
        int restart = playGame();
        if (!restart) break;
    }

    return 0;
}
