#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

int digits(ll a)
{
    int res = 0;
    
    while (a > 0)
    {
        a /= 10LL; res++;
    }
    
    return res;
}

int digitAt(ll a, int b)
{
    while (digits(a) > b)
        a /= 10LL;
    
    return a % 10LL;
}


int main()
{
    ll A, B;
    scanf("%lld %lld", &A, &B);
    
    int sum = 0;
    
    for (int i = 1; i <= digits(B); i++)
    {
        bool nonZero = false;
        
        for (int j = 0; j < digitAt(B, i); j++)
        {
            nonZero |= (digitAt(A, ++sum) != 0);
            
            if (nonZero)
                printf("%d", digitAt(A, sum));
        }
        
        if (!nonZero)
            printf("0");
        
        printf("\n");
    }
    
    return 0;
}
