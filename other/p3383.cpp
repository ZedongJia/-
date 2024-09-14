#include <iostream>
#define N 100000001

bool visited[N];
int primes[N], total = 0;

void sieve()
{
    std::fill(visited, visited + N, false);
    visited[1] = true;
    for (int i = 2; i <= N; i++)
    {
        if (!visited[i])
            primes[total++] = i;
        for (int j = 0; primes[j] * i <= N && j < total; j++)
        {
            visited[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    sieve();
    int n, q;
    scanf("%d%d", &n, &q);
    while (q--)
    {
        int number;
        scanf("%d", &number);
        printf("%d\n", primes[number - 1]);
    }
}