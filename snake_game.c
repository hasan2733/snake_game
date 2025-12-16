#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void drawGame(int sx, int sy, int tx, int ty, int fx, int fy, int prevX[], int prevY[], int prevCount) {
    system("cls");
    for (int y = 11; y >= -11; y--) {
        for (int x = -11; x <= 11; x++) {
            int isBorder = (y == 11 || y == -11 || x == -11 || x == 11);
            int isPlayer = (x == sx && y == sy);
            int isTarget = (x == tx && y == ty);
            int isFootprint = (x == fx && y == fy);
            int isPrevious = 0;
            for (int i = 0; i < prevCount; i++) {
                if (x == prevX[i] && y == prevY[i]) {
                    isPrevious = 1;
                    break;
                }
            }
            if (isBorder) {
                printf("#");
            } else if (isPlayer) {
                printf("*");
            } else if (isTarget) {
                printf("$");
            } else if (isFootprint) {
                printf(".");
            } else if (isPrevious) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void Play_LEvel(int sx, int sy, int tlx, int tly) {
    char ch;
    int fx = sx, fy = sy;
    int prevX[100], prevY[100];
    int prevCount = 0;

    // Hide cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    while (1) {
        ch = getch();
        prevX[prevCount] = sx;
        prevY[prevCount] = sy;
        prevCount++;
        if (prevCount >= 100)
        {
            prevCount = 0;
        }

        switch (ch) {
            case 'w':
            case 'W':
                sy = sy + 1;
                break;
            case 's':
            case 'S':
                sy = sy - 1;
                break;
            case 'a':
            case 'A':
                sx = sx - 1;
                break;
            case 'd':
            case 'D':
                sx = sx + 1;
                break;
        }
        fx = sx;
        fy = sy;
        drawGame(sx, sy, tlx, tly, fx, fy, prevX, prevY, prevCount);
        if (sx == tlx && sy == tly) {
            printf("\nGAME OVER\n");
            sx = tlx;
            sy = tly;
            break;
        }
        printf("%d%d\n", sx, sy);
        if (sx == tlx && sy == tly) {
            printf("\nGAME OVER\n");
            sx = tlx;
            sy = tly;
            break;
        }
    }

    // Reset cursor visibility
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int main() {
    char ch;
    clock_t start, end;
    double cpu_time_used = 0.0;
    int level = 0;

    int sx = 0, sy = 0;
    int tx, ty;

    while (1) {
        srand(time(NULL));

        tx = rand() % 20 - 10;
        ty = rand() % 20 - 10;
        printf("[ABID]......................[720]");
        printf("\n-----------------------\n");
        printf("  Level %d\n", level + 1);
        printf("-----------------------\n");
        printf("Find the target ($) to win!\n\n");

        start = clock();
        Play_LEvel(sx, sy, tx, ty);
        end = clock();
        level++;
        cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("if you want to continue ? press y for continue and n for discontinue:\n");
        ch = getche();
        if (ch == 'n' || ch == 'N') {
            break;
        }
    }
    printf("\n Time taken: %.3f seconds and Level=%d\n", cpu_time_used, level);
    getch();
    getch();
    return 0;
}
