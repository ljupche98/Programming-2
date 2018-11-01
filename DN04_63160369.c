#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define mlen ((int) strlen(match))
#define wlen ((int) strlen(word))

int N, res = 0;
int cache[101][101];
char match[101], word[101];

bool solve(int idxm, int idxw)
{
    if (idxm >= mlen)
        return false;
    
    if (cache[idxm][idxw] != -1)
        return cache[idxm][idxw];
    
    if (idxm == mlen - 1 && match[idxm] == '*')
        return cache[idxm][idxw] = true;
    
    if (idxm == mlen - 1 && idxw == wlen - 1 && (match[idxm] == '?' || match[idxm] == word[idxw]))
        return cache[idxm][idxw] = true;
    
    if (idxw >= wlen)
        return false;
    
    bool res = false;
    
    if (match[idxm] == '?')
        return cache[idxm][idxw] = res |= solve(idxm + 1, idxw + 1);
    
    if (match[idxm] == '*')
        for (int i = idxw; i < wlen; i++)
            res |= solve(idxm + 1, i);
    
    if (match[idxm] == word[idxw])
        return cache[idxm][idxw] = res |= solve(idxm + 1, idxw + 1);
    
    if (match[idxm] != word[idxw])
        return cache[idxm][idxw] = res |= false;
    
    return cache[idxm][idxw] = res;
}

int main()
{
    scanf("%s", match);
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
    {
        scanf("%s", word);
        
        memset(cache, -1, sizeof(cache));
        
        if (solve(0, 0))
            res++;
    }
    
    printf("%d\n", res);
    
    return 0;
}
