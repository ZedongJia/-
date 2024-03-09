#include <stdio.h>

void show(char *cnd, int len, int type)
{
    int s1 = 0;
    int s2 = 0;
    for (int i = 0; i < len; i++)
    {
        if (cnd[i] == 'W')
        {
            s1++;
        }
        if (cnd[i] == 'L')
        {
            s2++;
        }
        if ((s1 >= s2 + 2) && s1 >= type)
        {
            printf("%d:%d\n", s1, s2);
            s1 = 0;
            s2 = 0;
        }
        else if ((s2 >= s1 + 2) && s2 >= type)
        {
            printf("%d:%d\n", s1, s2);
            s1 = 0;
            s2 = 0;
        }
    }
    printf("%d:%d\n", s1, s2);
}

int main()
{
    char ch;
    char cnd[100010];
    int idx = 0;
    while ((ch = getchar()) != 'E')
    {
        if (ch == 'W' || ch == 'L')
        {
            cnd[idx] = ch;
            idx++;
        }
    }

    show(cnd, idx, 11);
    printf("\n");
    show(cnd, idx, 21);
}