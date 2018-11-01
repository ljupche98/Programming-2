#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct edge
{
    int in;
    int out;
    int days;
    int prev;
    int next;
}
edge;

int loc, N;
int endID;
int startID;
edge **edges;
char **locations;

int find(char *text)
{
    for (int i = 0; i < loc; i++)
        if (!strcmp(text, locations[i]))
            return i;
    return -1;
}

void addLocation(char *text)
{
    if (find(text) != -1)
        return;
    
    locations = (char**) realloc(locations, (loc + 1) * sizeof(char*));
    locations[loc] = (char*) malloc(((int) strlen(text) + 1) * sizeof(char));
    strcpy(locations[loc++], text);
}

void addEgde(int prev, int next, int in, int out, int days)
{
    edges = (edge**) realloc(edges, (N + 1) * sizeof(edge*));
    edges[N] = (edge*) malloc(sizeof(edge));
    edges[N]->in = in;
    edges[N]->out = out;
    edges[N]->days = days;
    edges[N]->prev = prev;
    edges[N++]->next = next;
}

void findStart()
{
    bool *visit = (bool*) malloc(loc * sizeof(bool));
    
    for (int i = 0; i < N; i++)
        visit[edges[i]->prev] ^= true;
    
    for (int i = 0; i < N; i++)
        visit[edges[i]->next] ^= true;
    
    for (int i = 0; i < loc; i++)
        if (visit[i])
            for (int j = 0; j < N; j++)
                if (edges[j]->prev == i)
                    startID = edges[j]->prev;
}

void findEnd()
{
    bool *visit = (bool*) malloc(loc * sizeof(bool));
    
    for (int i = 0; i < N; i++)
        visit[edges[i]->prev] ^= true;
    
    for (int i = 0; i < N; i++)
        visit[edges[i]->next] ^= true;
    
    for (int i = 0; i < loc; i++)
        if (visit[i])
            for (int j = 0; j < N; j++)
                if (edges[j]->next == i)
                    endID = edges[j]->next;
}

edge *findEdge(int ID)
{
    for (int i = 0; i < N; i++)
        if (edges[i]->prev == ID)
            return edges[i];
    return NULL;
}

int findOut(int ID)
{
    for (int i = 0; i < N; i++)
        if (edges[i]->next == ID)
            return edges[i]->out;
    return 0;
}

void solve(int days)
{
    int i, cnt, res; edge *it;
    
    for (i = cnt = res = 0, it = findEdge(startID); i < N && it != NULL && days > 0; res += it->in - findOut(it->prev), days -= it->days, i++, it = findEdge(it->next));
    
    for (it = findEdge(startID); i > 1; i--, it = findEdge(it->next));
    
    if (days > 0)
        printf("NAPAKA\n");
    else
        printf("%s %s %d\n", locations[it->prev], locations[it->next], res);
}

int main()
{
    for (;;)
    {
        char L1[101], L2[101];
        int days, in, out;
        scanf("%s", L1);
        
        if (L1[0] == '?')
            break;
        
        scanf("%s %d %d %d", L2, &days, &in, &out);
        
        addLocation(L1); addLocation(L2);
        
        addEgde(find(L1), find(L2), in, out, days);
    }
    
    findStart(); findEnd();
    
    int query;
    
    for (;scanf("%d", &query) != EOF /** scanf("%d", &query) == 1 **/;)
        solve(query);
    
    return 0;
}
