#include <algorithm>
#include <iostream>
#include <string.h>
#define NUM_SIZE 10000
/**

需要高精度！！！
(better)
a
ai,bi -> a / bi < max
aj,bj -> a * ai / bj < max

(order)
a
aj,bj -> a / bj  < a * ai / bj < max
ai,bi -> a * aj / bi ?

(need)
aj * bj < ai * bi
*/
void mul(char *result, char *n1, char *n2)
{
    int arr[NUM_SIZE]{};
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    for (int i = len1 - 1; i >= 0; i--)
    {
        for (int j = len2 - 1; j >= 0; j--)
        {
            int ridx = len1 + len2 - (i + 1) - (j + 1);
            int tmp = (n1[i] - 48) * (n2[j] - 48) + arr[ridx];
            arr[ridx + 1] = int(tmp / 10) + arr[ridx + 1];
            arr[ridx] = tmp % 10;
        }
    }
    int j = 0;
    int i = len1 + len2;
    while (arr[i] == 0)
    {
        i--;
    }
    while (i >= 0)
    {
        result[j] = arr[i] + 48;
        i--;
        j++;
    }
    if (j == 0)
    {
        result[j] = 48;
        j++;
    }
    result[j] = '\0';
}

void div(char *result, char *n1, char *n2)
{
    int arr[NUM_SIZE]{};
    int len1 = strlen(n1);
    long long _div = std::stoll(n2);
    long long rest = 0;
    for (int i = 0; i < len1; i++)
    {
        long long tmp = rest * 10 + n1[i] - 48;
        arr[i] = tmp / _div;
        rest = tmp % _div;
    }
    int i = 0;
    int j = 0;
    while (arr[i] == 0)
    {
        i++;
    }
    while (i < len1)
    {
        result[j] = arr[i] + 48;
        i++;
        j++;
    }
    if (j == 0)
    {
        result[j] = 48;
        j++;
    }
    result[j] = '\0';
}

bool small(const char n1[], const char n2[])
{
    bool stat = false;
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    if (len1 < len2)
    {
        stat = true;
    }
    else if (len1 > len2)
    {
        stat = false;
    }
    else
    {
        stat = (strcmp(n1, n2) < 0);
    }
    return stat;
}
typedef struct P
{
    char l[NUM_SIZE];
    char r[NUM_SIZE];
    char score[NUM_SIZE];
    bool operator<(const P &p) const
    {
        return small(score, p.score);
    }
} P;
P p[10001];
int main()
{
    int n;
    std::cin >> n;
    std::cin >> p[0].l >> p[0].r;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> p[i].l >> p[i].r;
        mul(p[i].score, p[i].l, p[i].r);
    }
    std::sort(p + 1, p + n + 1);
    char rest[NUM_SIZE] = "1";
    char corns[NUM_SIZE] = "\0";
    for (int i = 1; i <= n; i++)
    {
        mul(rest, rest, p[i - 1].l);
        char tmp[NUM_SIZE];
        div(tmp, rest, p[i].r);
        if (!small(tmp, corns))
        {
            strcpy(corns, tmp);
        }
    }
    printf("%s", corns);
}