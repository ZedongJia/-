#include <algorithm>
#include <iostream>
#define N 1000001

bool visited[N];
int primes[N], total = 0;
int l, r;

void mySieve()
{
    std::fill(visited, visited + N, false);
    visited[1] = true;
    for (int i = 2; i <= 50000; i++)
    {
        if (!visited[i])
            primes[total++] = i;
        for (int j = 0; j < total && primes[j] * i <= 50000; j++)
        {
            visited[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    mySieve();
    scanf("%d%d", &l, &r);
    std::fill(visited, visited + N, false);
    for (int i = 0; i < total; i++)
    {
        int prime = primes[i];
        for (long long number = l % prime ? (l / prime + 1) * prime : l; number <= r; number += prime)
        {
            if (number == prime)
                continue;
            visited[number - l] = true;
        }
    }
    int count = l == 1 ? -1 : 0;
    for (int i = 0; i <= r - l; i++)
        if (!visited[i])
            count++;
    printf("%d", count);
}