#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int N;
    scanf("%d", &N);
    
    int cnt = 0;
    int *num = (int *) malloc(N * sizeof(int));
    int *even = (int *) malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
    /// scanf("%d", num + i);
        
        if (num[i] % 2 == 0)
            even[cnt++] = num[i];
    }
    
    for (int i = 0; i < cnt - 1; i++)
        for (int j = i + 1; j < cnt; j++)
            if (even[i] > even[j])
                swap(&even[i], &even[j]);
            /// swap(even + i, even + j);
    
    cnt = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (num[i] % 2 == 0)
            printf("%d ", even[cnt++]);
        else
            printf("%d ", num[i]);
    }
    
    printf("\n");
    
    return 0;
}
