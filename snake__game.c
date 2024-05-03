#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void Play_LEvel(int sx,int sy,int tlx,int tly)
{
    char ch;
    while (1)
    {
        ch = getch();
        switch (ch)
        {
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
        printf("%d %d\n",sx,sy);
        if (sx == tlx && sy == tly)
        {
            printf("\nGAME OVER\n");
            sx=tlx;
            sy=tly;
            break;
        }
    }

}

int main()
{
    char ch;
    clock_t start, end;
    double cpu_time_used=0.0;
    int level=0;

    int sx=0,sy=0;
    int tx, ty;

    while(1)
    {
        srand(time(NULL));


        tx = rand() % 20 - 10;
        ty = rand() % 20 - 10;
        printf("\n target is %d %d \n", tx, ty);
        printf("-----------GO-------\n");
        start = clock();
        Play_LEvel(sx,sy,tx,ty);
        end = clock();
        level++;
        cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("if you want to continue ? press y for continue and n for discontinue:\n");
        ch=getche();
        if(ch=='n'||ch=='N')
        {
            break;
        }
    }
    printf("\n Time taken: %.3f seconds and Level=%d\n", cpu_time_used,level);
    getch();
    getch();
    return 0;
}
