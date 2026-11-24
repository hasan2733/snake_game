#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define BOARD_MIN (-11)
#define BOARD_MAX 11
#define TARGET_MIN (-10)
#define TARGET_RANGE 20
#define MAX_TRAIL 100

static void draw_game(int player_x,
                      int player_y,
                      int target_x,
                      int target_y,
                      const int trail_x[],
                      const int trail_y[],
                      int trail_count)
{
    system("cls");

    for (int y = BOARD_MAX; y >= BOARD_MIN; --y) {
        for (int x = BOARD_MIN; x <= BOARD_MAX; ++x) {
            const int is_border =
                y == BOARD_MAX || y == BOARD_MIN || x == BOARD_MIN || x == BOARD_MAX;
            const int is_player = x == player_x && y == player_y;
            const int is_target = x == target_x && y == target_y;
            int is_trail = 0;

            for (int i = 0; i < trail_count; ++i) {
                if (x == trail_x[i] && y == trail_y[i]) {
                    is_trail = 1;
                    break;
                }
            }

            if (is_border) {
                putchar('#');
            } else if (is_player) {
                putchar('*');
            } else if (is_target) {
                putchar('$');
            } else if (is_trail) {
                putchar('.');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

static void hide_cursor(int hidden)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;

    if (GetConsoleCursorInfo(console, &cursor_info)) {
        cursor_info.bVisible = !hidden;
        SetConsoleCursorInfo(console, &cursor_info);
    }
}

static void add_to_trail(int x, int y, int trail_x[], int trail_y[], int *trail_count)
{
    if (*trail_count < MAX_TRAIL) {
        trail_x[*trail_count] = x;
        trail_y[*trail_count] = y;
        ++(*trail_count);
        return;
    }

    for (int i = 1; i < MAX_TRAIL; ++i) {
        trail_x[i - 1] = trail_x[i];
        trail_y[i - 1] = trail_y[i];
    }
    trail_x[MAX_TRAIL - 1] = x;
    trail_y[MAX_TRAIL - 1] = y;
}

static void play_level(int *player_x, int *player_y, int target_x, int target_y)
{
    int trail_x[MAX_TRAIL];
    int trail_y[MAX_TRAIL];
    int trail_count = 0;

    hide_cursor(1);

    while (1) {
        const char key = getch();

        add_to_trail(*player_x, *player_y, trail_x, trail_y, &trail_count);

        switch (key) {
        case 'w':
        case 'W':
            ++(*player_y);
            break;
        case 's':
        case 'S':
            --(*player_y);
            break;
        case 'a':
        case 'A':
            --(*player_x);
            break;
        case 'd':
        case 'D':
            ++(*player_x);
            break;
        default:
            break;
        }

        draw_game(*player_x,
                  *player_y,
                  target_x,
                  target_y,
                  trail_x,
                  trail_y,
                  trail_count);

        if (*player_x == target_x && *player_y == target_y) {
            printf("\nTarget reached!\n");
            break;
        }
    }

    hide_cursor(0);
}

static int random_target_coordinate(void)
{
    return rand() % TARGET_RANGE + TARGET_MIN;
}

int main(void)
{
    char answer;
    clock_t start;
    clock_t end;
    double total_time = 0.0;
    int level = 0;
    int player_x = 0;
    int player_y = 0;

    srand((unsigned int)time(NULL));

    do {
        int target_x;
        int target_y;

        do {
            target_x = random_target_coordinate();
            target_y = random_target_coordinate();
        } while (target_x == player_x && target_y == player_y);

        printf("\n-----------------------\n");
        printf("  Level %d\n", level + 1);
        printf("-----------------------\n");
        printf("Find the target ($) to win.\n");
        printf("Move with W, A, S, and D.\n");

        start = clock();
        play_level(&player_x, &player_y, target_x, target_y);
        end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;
        ++level;

        printf("Play another level? (y/n): ");
        answer = getche();
        putchar('\n');
    } while (answer != 'n' && answer != 'N');

    printf("\nTotal time: %.3f seconds\n", total_time);
    printf("Levels completed: %d\n", level);
    printf("Press any key to exit...");
    getch();
    return 0;
}
