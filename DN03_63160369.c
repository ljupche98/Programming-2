#include <stdio.h>

struct object
{
    int x;
    int y;
    int type;
    int length;
} snake[1001], objects[1000];

int N, K;
int dir = 0;
int comx[] = {0, -1, 0, 1};
int comy[] = {1, 0, -1, 0};

int main()
{
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
        scanf("%d %d %d", &objects[i].x, &objects[i].y, &objects[i].type);
    
    scanf("%d", &K);
    
    snake[0].x = snake[0].y = 0; snake[0].length = 1;
    
    for (int i = 1; i <= K; i++)
    {
        snake[i] = snake[i-1];
        
        for (int j = 0; j < N; j++)
        {
            if (objects[j].x == snake[i-1].x && objects[j].y == snake[i-1].y && i != 1)
            {
                if (objects[j].type == 1)
                    snake[i].length++;
                else if (objects[j].type == 2)
                    dir = ((dir + 1) + 4) % 4;
                else if (objects[j].type == 3)
                    dir = ((dir - 1) + 4) % 4;
            }
        }
        
        snake[i].x = snake[i-1].x + comx[dir];
        snake[i].y = snake[i-1].y + comy[dir];
        
        for (int j = 0; j < i; j++)
        {
            if (snake[i].x == snake[j].x && snake[i].y == snake[j].y && i - j < snake[i].length)
            {
                printf("0 %d %d\n", snake[i].x, snake[i].y);
                return 0;
            }
        }
    }
    
    printf("%d %d %d\n", snake[K].length, snake[K].x, snake[K].y);
    
    return 0;
}
