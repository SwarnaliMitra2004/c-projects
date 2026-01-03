#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 60

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir;

int score;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100], tail_y[100];
int gameOver;

void setup();
void draw();
void input();
void logic();
void clear_screen();

int main() {
    srand(time(NULL));
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);   // speed control
    }

    clear_screen();
    printf("\n💀 GAME OVER\nFinal Score: %d\n", score);
    return 0;
}

void setup() {
    gameOver = 0;
    dir = STOP;
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    score = 0;
    tail_length = 0;
}

void draw() {
    clear_screen();
    printf("\t\t🐍 Snake Game 🐍\n");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");

    for (int i = 0; i < HEIGHT; i++) {
        printf("\n#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x)
                printf("O");
            else if (i == fruit_y && j == fruit_x)
                printf("F");
            else {
                int printTail = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        printf("o");
                        printTail = 1;
                        break;
                    }
                }
                if (!printTail) printf(" ");
            }
        }
        printf("#");
    }

    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void logic() {
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev2_x, prev2_y;
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    for (int i = 1; i < tail_length; i++) {
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev2_x;
        prev_y = prev2_y;
    }

    switch (dir) {
        case UP:    head_y--; break;
        case DOWN:  head_y++; break;
        case LEFT:  head_x--; break;
        case RIGHT: head_x++; break;
        default: break;
    }

    // Wall collision
    if (head_x < 0 || head_x >= WIDTH || head_y < 0 || head_y >= HEIGHT) {
        gameOver = 1;
    }

    // Self collision
    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            gameOver = 1;
        }
    }

    // Eat fruit
    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
        tail_length++;
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}