#include <stdio.h>

int main()
{
    int T, N;
    scanf("%d %d", &T, &N);
    
    int last = -1, cnt = 1;
    
    for (int i = 0; i < N; i++)
    {
        if (T == 1)
        {
            int A;
            scanf("%d", &A);
            
            if (i == 0)
            {
                last = A;
                cnt = 1;
            }
            else if (last != A)
            {
                printf("%d %d ", cnt, last);
                cnt = 1;
                last = A;
            }
            else
            {
                cnt++;
            }
        }
        else
        {
            int A, B;
            scanf("%d %d", &A, &B);
            
            for (int j = 0; j < A; j++)
            {
                printf("%d ", B);
            }
        }
    }
    
    if (T == 1 && N != 0)
    {
        printf("%d %d", cnt, last);
    }
    
    printf("\n");
    
    /**
    if (N == 0)
    {
        printf("\n");
        return 0;
    }
    
    if (T == 1)
    {
        int last, cnt = 1;
        scanf("%d", &last);
        
        for (int i = 1; i < N; i++)
        {
            int A;
            scanf("%d", &A);
            
            if (last != A)
            {
                printf("%d %d ", cnt, last);
                last = A;
                cnt = 1;
            }
            else
            {
                cnt++;
            }
        }
        
        printf("%d %d", cnt, last);
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            int A, B;
            scanf("%d %d", &A, &B);
            
            for (int j = 0; j < A; j++)
                printf("%d ", B);
        }
    }
    **/
    
    return 0;
}
