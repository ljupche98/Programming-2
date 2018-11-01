#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll res[10][10];
int T, N, M;
char openn[21], writen[21];
FILE *open, *write;

int main()
{
    scanf("%d %d %d", &T, &N, &M);
    scanf("%s", openn);
    scanf("%s", writen);
    
    open = fopen(openn, "r");
    write = fopen(writen, "w");
    
    if (T == 1)
    {
        for (int i = 0; i < (N << 3);)
        {
            char line[(M<<3)+1];
            fgets(line, (M << 3) + 1, open);
            
            if (line[0] == '\n')
                continue;
                
            for (int j = 0; j < (M << 3); j++)
                if (line[j] == '*')
                    res[i>>3][j>>3] |= (1LL << (63 - ((i % 8) << 3) - (j % 8)));
    
            i++;
        }
        
        for (int i = 0; i < N; i++, fprintf(write, "\n"))
            for (int j = 0; j < M; j++)
                fprintf(write, "%lld ", res[i][j]);
    }
    else
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                fscanf(open, "%lld", &res[i][j]);
                                
        for (int i = 0; i < (N << 3); i++, fprintf(write, "\n"))
            for (int j = 0; j < (M << 3); j++)
                fprintf(write, "%c", (res[i>>3][j>>3] & (1LL << (63 - ((i % 8) << 3) - (j % 8)))) ? '*' : ' ');
    }
    
    fclose(open); fclose(write);
    
    return 0;
}
