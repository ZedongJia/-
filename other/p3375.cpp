#include <cstring>
#include <iostream>
#define L 2000001
char input[L];
char pattern[L];
int il, pl;

int next[L];
void setNext()
{
    next[0] = -1;
    int j = 0, k = -1;
    while (j < pl)
    {
        if (k == -1 || pattern[j] == pattern[k])
        {
            j++, k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
}

void kmp()
{
    int i = 0, j = 0;
    while (i < il)
    {
        if (j == -1 || input[i] == pattern[j])
        {
            i++, j++;
        }
        else
        {
            j = next[j];
        }
        if (j == pl)
        {
            printf("%d\n", i - j + 1);
            j = next[j];
        }
    }
}

int main()
{
    scanf("%s", input);
    scanf("%s", pattern);
    il = strlen(input);
    pl = strlen(pattern);
    setNext();
    kmp();
    for (int j = 1; j < pl; j++)
    {
        printf("%d ", next[j]);
    }
    printf("%d", next[pl]);
}