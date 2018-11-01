#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct object
{
    int ID;
    int user;
    int day;
    int month;
    int year;
} *object;

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int members, books, each, maxDays, price, N, takenLen = 0, *remaining;
object booksTaken = NULL;

int max(int a, int b)
{
    return a >= b ? a : b;
}

int main()
{
    scanf("%d %d %d %d %d %d", &members, &books, &each, &maxDays, &price, &N);
    
    remaining = (int*) malloc((books + 1) * sizeof(int));
    
    for (int i = 0; i <= books; i++)
        remaining[i] = each;
    
    /// memset(remaining, each, (books + 1) * sizeof(int));
    
    /**
    for (int i = 1; i <= books; i++)
        printf("%d\n", remaining[i]);
    **/
    
    for (int i = 0; i < N; i++)
    {
        char type;
        scanf (" %c", &type);
        
        if (type == '+')
        {
            int ID, which;
            char date[20];
            
            scanf("%s %d %d", date, &ID, &which);
            
            if (remaining[which] <= 0)
            {
                printf("N\n");
                continue;
            }
            
            /// printf("%s %d %d\n", date, ID, which);
            
            bool hasTaken = false;
            
            for (int j = 0; j < takenLen && !hasTaken; j++)
                hasTaken |= (booksTaken[j].user == ID && booksTaken[j].ID == which);
            
            if (hasTaken)
            {
                printf("N\n");
                continue;
            }
            
            booksTaken = realloc(booksTaken, (takenLen + 1) * sizeof(struct object));
            
            remaining[which]--;
            booksTaken[takenLen].user = ID;
            booksTaken[takenLen].ID = which;
            booksTaken[takenLen].day = 10 * (date[0] - '0') + (date[1] - '0');
            booksTaken[takenLen].month = 10 * (date[3] - '0') + (date[4] - '0');
            booksTaken[takenLen].year = 1000 * (date[6] - '0') + 100 * (date[7] - '0') + 10 * (date[8] - '0') + (date[9] - '0');
            takenLen++;
            
            printf("D\n");
            
            /**
            for (int j = 0; j < takenLen; j++)
                printf("USERID: %d; BOOKID: %d; DAY: %d; MONTH: %d; YEAR %d\n", booksTaken[j].user, booksTaken[j].ID, booksTaken[j].day, booksTaken[j].month, booksTaken[j].year);
            **/
        }
        else if (type == '-')
        {
            int ID, which;
            char date[20];
            
            scanf(" %s %d %d", date, &ID, &which);
            
            int idx = -1;
            
            for (int j = 0; j < takenLen && idx == -1; j++)
                if (booksTaken[j].user == ID && booksTaken[j].ID == which)
                    idx = j;
            
            if (idx == -1)
            {
                printf("N\n");
                continue;
            }
            
            int dif = 0;
            int day = 10 * (date[0] - '0') + (date[1] - '0');
            int month = 10 * (date[3] - '0') + (date[4] - '0');
            int year = 1000 * (date[6] - '0') + 100 * (date[7] - '0') + 10 * (date[8] - '0') + (date[9] - '0');
            
            /**
            printf("TAKE:\nDAY: %d; MONTH: %d; YEAR: %d;\nRETURN:\nDAY: %d; MONTH: %d; YEAR: %d\n",
                   booksTaken[idx].day, booksTaken[idx].month, booksTaken[idx].year,
                   day, month, year);
            **/
            
            while (day != booksTaken[idx].day || month != booksTaken[idx].month || year != booksTaken[idx].year)
            {
                dif++;  day--;

                if (day <= 0)
                {
                    month--;
                    
                    if (month <= 0)
                    {
                        month = 12;
                        year--;
                    }
                    
                    day = days[month];
                    
                    if (year % 4 == 0 && month == 2)
                        day++;
                }
            }
            
            /// printf("OVDE E DIF: %d\n", dif);
            
            printf("%d\n", max(0, (dif - maxDays) * price));
            
            remaining[booksTaken[idx].ID]++;
            
            booksTaken[idx].ID = booksTaken[idx].user = -1;
        }
        else if (type == 'A')
        {
            int ID;
            scanf("%d", &ID);
            
            int res = 0;
            
            for (int j = 0; j < takenLen; j++)
                res += booksTaken[j].user == ID;
            
            printf("%d\n", res);
        }
        else if (type == 'B')
        {
            int ID;
            scanf("%d", &ID);
            printf("%d\n", each - remaining[ID]);
        }
        else if (type == 'C')
        {
            int ID;
            scanf("%d", &ID);
            
            printf("/");
            
            bool visited[10000];
            memset(visited, false, sizeof(visited));
            
            while (true)
            {
                int idx = -1, minID = (1 << 30);
                
                for (int j = 0; j < takenLen; j++)
                {
                    if (booksTaken[j].user == ID && !visited[j] && booksTaken[j].ID < minID)
                    {
                        idx = j;
                        minID = booksTaken[j].ID;
                    }
                }
                
                if (idx == -1)
                    break;
                    
                visited[idx] = true;
                
                int cnt = maxDays, day = booksTaken[idx].day, month = booksTaken[idx].month, year = booksTaken[idx].year;
                
                while (cnt > 0)
                {
                    cnt--;  day++;
                    
                    if (day > days[month] + (year % 4 == 0 && month == 2))
                    {
                        day = 1;
                        
                        month++;
                        
                        if (month > 12)
                        {
                            month = 1;
                            year++;
                        }
                    }
                }
                
                printf("%d:", minID);
                
                if (day < 10)
                    printf("0");
                printf("%d.", day);
                
                if (month < 10)
                    printf("0");
                printf("%d.", month);
                
                printf("%d/", year);
                
                /// printf("%d:%d.%d.%d/", minID, day, month, year);
            }
            
            printf("\n");
        }
        else if (type == 'D')
        {
            int ID;
            scanf("%d", &ID);
            
            printf("/");
            
            bool visited[10000];
            memset(visited, false, sizeof(visited));
            
            while (true)
            {
                int idx = -1, minID = (1 << 30);
                
                for (int j = 0; j < takenLen; j++)
                {
                    if (booksTaken[j].ID == ID && !visited[j] && booksTaken[j].user < minID)
                    {
                        idx = j;
                        minID = booksTaken[j].user;
                    }
                }
                
                if (idx == -1)
                    break;
                
                visited[idx] = true;
                
                int cnt = maxDays, day = booksTaken[idx].day, month = booksTaken[idx].month, year = booksTaken[idx].year;
                
                while (cnt > 0)
                {
                    cnt--;  day++;
                    
                    if (day > days[month] + (year % 4 == 0 && month == 2))
                    {
                        day = 1;
                        
                        month++;
                        
                        if (month > 12)
                        {
                            month = 1;
                            year++;
                        }
                    }
                }
                
                printf("%d:", minID);
                
                if (day < 10)
                    printf("0");
                printf("%d.", day);
                
                if (month < 10)
                    printf("0");
                printf("%d.", month);
                
                printf("%d/", year);
                
                /// printf("%d:%d.%d.%d/", minID, day, month, year);
            }
            
            printf("\n");
        }
    }
    
    return 0;
}
