#include <stdio.h>

#define f first
#define s second

#define MAX (1 << 30)

struct object
{
    int first;
    int second;
} objects[50];

int N;

int min(int a, int b)
{
    return a <= b ? a : b;
}

int max(int a, int b)
{
    return a >= b ? a : b;
}

int solve(int last, long long visited)
{
    int res = 0;
    for (int i = 0; i < N; i++)
        if ((visited & (1 << i)) == 0)
            if (last == -1 || (max(objects[last].f, objects[last].s) > max(objects[i].f, objects[i].s) && min(objects[last].f, objects[last].s) > min(objects[i].f, objects[i].s)))
                res = max(res, 1 + solve(i, visited | (1 << i)));
    return res;
}



int main()
{
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
        scanf("%d %d", &objects[i].f, &objects[i].s);
    
    printf("%d\n", solve(-1, 0LL));
    
    return 0;
}
