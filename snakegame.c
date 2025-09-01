#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

int width = 20, height = 20, gameOver;
int x, y, fruitX, fruitY, score, flag;
int tailX[100], tailY[100];
int countTail = 0;

void setup() {
    gameOver = 0;
    x = width / 2;
    y = height / 2;

    srand(time(NULL)); // Initialize random seed

    // Generate fruit position (avoid borders)
    label1:
    fruitX = rand() % (height - 2) + 1;
    if(fruitX <= 0 || fruitX >= height - 1) goto label1;

    label2:
    fruitY = rand() % (width - 2) + 1;
    if(fruitY <= 0 || fruitY >= width - 1) goto label2;

    score = 0;
    flag = 0; // Initialize direction flag
}

void draw() {
    int i, j, k;
    system("cls");

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if(i == 0 || i == height-1 || j == 0 || j == width-1) {
                printf("#");
            }
            else if(i == x && j == y) {
                printf("O"); // Snake head
            }
            else if(i == fruitX && j == fruitY) {
                printf("F"); // Fruit
            }
            else {
                int ch = 0;
                for(k = 0; k < countTail; k++) {
                    if(i == tailX[k] && j == tailY[k]) {
                        printf("o"); // Snake tail
                        ch = 1;
                        break;
                    }
                }
                if(ch == 0)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("SCORE: %d\n", score);
    printf("Use WASD to move, X to exit\n");
}

void input() {
    if(kbhit()) {
        switch(getch()) {
            case 'a':
            case 'A':
                flag = 1; // Left
                break;
            case 'd':
            case 'D':
                flag = 2; // Right
                break;
            case 'w':
            case 'W':
                flag = 3; // Up
                break;
            case 's':
            case 'S':
                flag = 4; // Down
                break;
            case 'x':
            case 'X':
                gameOver = 1;
                break;
        }
    }
}

void makeLogic() {
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for(i = 1; i < countTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(flag) {
        case 1:
            y--; // Left
            break;
        case 2:
            y++; // Right
            break;
        case 3:
            x--; // Up
            break;
        case 4:
            x++; // Down
            break;
        default:
            break;
    }

    // Check wall collision
    if(x <= 0 || x >= height-1 || y <= 0 || y >= width-1)
        gameOver = 1;

    // Check self collision
    for(i = 0; i < countTail; i++) {
        if(x == tailX[i] && y == tailY[i])
            gameOver = 1;
    }

    // Check if fruit is eaten
    if(x == fruitX && y == fruitY) {
        label3:
        fruitX = rand() % (height - 2) + 1;
        if(fruitX <= 0 || fruitX >= height - 1) goto label3;

        label4:
        fruitY = rand() % (width - 2) + 1;
        if(fruitY <= 0 || fruitY >= width - 1) goto label4;

        score += 10;
        countTail++;
    }
}

int main() {
    int m, n;
    char c;

    printf("Welcome to Snake Game!\n");
    printf("Use WASD to move, X to exit\n");
    printf("Press any key to start...\n");
    getch();

    label5:
    setup();

    while(!gameOver) {
        draw();
        input();
        makeLogic();

        // Simple delay for game speed
        for(m = 0; m < 100000; m++) {
            for(n = 0; n < 1000; n++) {
                // Empty loop for delay
            }
        }
    }

    printf("\nGame Over!\n");
    printf("Final Score: %d\n", score);
    printf("Press Y to play again: ");
    scanf(" %c", &c);
    if(c == 'y' || c == 'Y')
        goto label5;

    printf("Thanks for playing!\n");
    return 0;
}
